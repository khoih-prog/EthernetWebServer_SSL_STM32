/****************************************************************************************************************************
  MQTTClient_SSL.ino - Dead simple SSL MQTT Client for Ethernet shields

  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
 *****************************************************************************************************************************/

/*
  Basic MQTT example (with SSL!)
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - publishes {Hello from MQTTClient_SSL on NUCLEO_F767ZI} to the topic [STM32_Pub]
  - subscribes to the topic [STM32_Sub], printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.

  You will need to populate "certificates.h" with your trust anchors
  (see https://github.com/OPEnSLab-OSU/SSLClient/blob/master/TrustAnchors.md)
  and my_cert/my_key with your certificate/private key pair
  (see https://github.com/OPEnSLab-OSU/SSLClient#mtls).
*/

#include "defines.h"

#include "certificates.h"     // This file must be regenerated at https://openslab-osu.github.io/bearssl-certificate-utility/
#include <PubSubClient.h>

const char my_cert[]  = "FIXME";
const char my_key[]   = "FIXME";

SSLClientParameters mTLS = SSLClientParameters::fromPEM(my_cert, sizeof my_cert, my_key, sizeof my_key);

const char* mqttServer = "broker.emqx.io";        // Broker address

const char *ID        = "MQTTClient_SSL-Client";  // Name of our device, must be unique
const char *TOPIC     = "STM32_Pub";              // Topic to subcribe to
const char *subTopic  = "STM32_Sub";              // Topic to subcribe to

unsigned long lastMsg = 0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (unsigned int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

EthernetClient    ethClient;
EthernetSSLClient ethClientSSL(ethClient, TAs, (size_t)TAs_NUM);

PubSubClient client(mqttServer, 8883, callback, ethClientSSL);

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqttServer);

    // Attempt to connect
    if (client.connect(ID))
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      String data = "Hello from MQTTClient_SSL on " + String(BOARD_NAME);

      client.publish(TOPIC, data.c_str());

      Serial.println("Published connection message successfully!");
      Serial.print("Subcribed to: ");
      Serial.println(subTopic);
      
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      //ethClientSSL.flush();
      // ... and resubscribe
      client.subscribe(subTopic);
      // for loopback testing
      client.subscribe(TOPIC);
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      //ethClientSSL.flush();
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart MQTTClient_SSL on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_SSL_STM32_VERSION);

  // Enable mutual TLS with SSLClient
  ethClientSSL.setMutualAuthParams(mTLS);

  ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

  #if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
    // For other boards, to change if necessary
    #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
      // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
      Ethernet.init (USE_THIS_SS_PIN);
    
    #elif USE_ETHERNET3
      // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
      #ifndef ETHERNET3_MAX_SOCK_NUM
        #define ETHERNET3_MAX_SOCK_NUM      4
      #endif
    
      Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
    #elif USE_CUSTOM_ETHERNET
      // You have to add initialization for your Custom Ethernet here
      // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
      //Ethernet.init(USE_THIS_SS_PIN);
      
    #endif  //( ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
  #endif
  
  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // you're connected now, so print out the data
  Serial.print(F("You're connected to the network, IP = "));
  Serial.println(Ethernet.localIP());
}

#define MQTT_PUBLISH_INTERVAL_MS       5000L

String data         = "Hello from MQTTClient_SSL on " + String(BOARD_NAME);
const char *pubData = data.c_str();

void loop() 
{
  static unsigned long now;
  
  if (!client.connected()) 
  {
    reconnect();
  }

  // Sending Data
  now = millis();
  
  if (now - lastMsg > MQTT_PUBLISH_INTERVAL_MS)
  {
    lastMsg = now;

    if (!client.publish(TOPIC, pubData))
    {
      Serial.println("Message failed to send.");
    }

    Serial.print("Message Send : " + String(TOPIC) + " => ");
    Serial.println(data);
  }
  
  client.loop();
}
