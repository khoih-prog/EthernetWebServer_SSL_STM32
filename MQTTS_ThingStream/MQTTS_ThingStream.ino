/****************************************************************************************************************************
  MQTTS_ThingStream.ino - Dead simple SSL MQTT Client for Ethernet shields

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
  - publishes {Hello from MQTTS_ThingStream on NUCLEO_F767ZI} to the topic [STM32_Pub]
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

#include <PubSubClient.h>

const char my_cert[]  = "FIXME";
const char my_key[]   = "FIXME";

#define USING_THINGSTREAM_IO      true

#if USING_THINGSTREAM_IO

const char *MQTT_PREFIX_TOPIC   = "esp32-sniffer/";
const char *MQTT_ANNOUNCE_TOPIC = "/status";
const char *MQTT_CONTROL_TOPIC  = "/control";
const char *MQTT_BLE_TOPIC      = "/ble";


// GOT FROM ThingsStream!
const char *MQTT_SERVER     = "mqtt.thingstream.io";
const char *MQTT_USER       = "MQTT_USER";
const char *MQTT_PASS       = "MQTT_PASS";
const char *MQTT_CLIENT_ID  = "MQTT_CLIENT_ID";

String topic    = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;
String subTopic = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;

#else

const char* MQTT_SERVER = "broker.emqx.io";        // Broker address

const char*  ID         = "MQTTClient_SSL-Client";  // Name of our device, must be unique
String      topic       = "STM32_Pub";              // Topic to subcribe to
String      subTopic    = "STM32_Sub";              // Topic to subcribe to

#endif

void mqtt_receive_callback(char* topic, byte* payload, unsigned int length);

const int   MQTT_PORT           = 1883; //if you use SSL //1883 no SSL

String data         = "Hello from MQTT_ThingStream on " + String(BOARD_NAME) + " with " + String(SHIELD_TYPE);
const char *pubData = data.c_str();

unsigned long lastMsg = 0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors


EthernetClient    ethClient;

PubSubClient client(MQTT_SERVER, MQTT_PORT, mqtt_receive_callback, ethClient);

/*
   Called whenever a payload is received from a subscribed MQTT topic
*/
void mqtt_receive_callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("MQTT Message receive [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (unsigned int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.println(MQTT_SERVER);

    // Attempt to connect

#if USING_THINGSTREAM_IO
    int connect_status = client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS, topic.c_str(), 2, false, "");
#else
    int connect_status = client.connect(ID);
#endif

    if (connect_status)                                
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      client.publish(topic.c_str(), data.c_str());

      Serial.println("Published connection message successfully!");
     
      Serial.print("Subcribed to: ");
      Serial.println(subTopic);
      
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      //ethClientSSL.flush();
      // ... and resubscribe
      client.subscribe(subTopic.c_str());
      // for loopback testing
      client.subscribe(topic.c_str());
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

  Serial.print("\nStart MQTT_ThingStream on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_SSL_STM32_VERSION);

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

  // Note - the default maximum packet size is 256 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  //client.setBufferSize(256);
  
  Serial.println("***************************************");
  Serial.println(topic);
  Serial.println("***************************************");
}

#define MQTT_PUBLISH_INTERVAL_MS      5000L

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

    if (!client.publish(topic.c_str(), pubData))
    {
      Serial.println("Message failed to send.");
    }

    Serial.print("MQTT Message Send : " + topic + " => ");
    Serial.println(data);
  }
  
  client.loop();
}
