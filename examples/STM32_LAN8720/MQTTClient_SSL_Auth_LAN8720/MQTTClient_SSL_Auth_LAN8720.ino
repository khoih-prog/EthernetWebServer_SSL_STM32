/****************************************************************************************************************************
  MQTTClient_SSL_Auth_LAN8720.ino - Dead simple SSL MQTT Client for Ethernet shields

  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
 *****************************************************************************************************************************/

/*
  Basic MQTT example (with SSL!) with Authentication
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - providing username and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.
*/

#include "defines.h"

#include "certificates.h"     // This file must be regenerated at https://openslab-osu.github.io/bearssl-certificate-utility/
#include <PubSubClient.h>

const char my_cert[]  = "FIXME";
const char my_key[]   = "FIXME";

SSLClientParameters mTLS = SSLClientParameters::fromPEM(my_cert, sizeof my_cert, my_key, sizeof my_key);

// Update these with values suitable for your network.
//const char* mqttServer = "broker.example"; // Broker address
const char* mqttServer = "broker.emqx.io"; // Broker address
//IPAddress mqttServer(172, 16, 0, 2);

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

PubSubClient      client(mqttServer, 8883, callback, ethClientSSL);

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect
    if (client.connect("arduinoClient", "testuser", "testpass")) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      ethClientSSL.flush();
      // ... and resubscribe
      client.subscribe("inTopic");
      // for loopback testing
      client.subscribe("outTopic");
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      ethClientSSL.flush();
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
  delay(2000);

  Serial.print("\nStart MQTTClient_SSL_Auth_LAN8720 on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_WEBSERVER_SSL_STM32_VERSION);

  // Enable mutual TLS with SSLClient
  ethClientSSL.setMutualAuthParams(mTLS);
   
  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // you're connected now, so print out the data
  Serial.print(F("You're connected to the network, IP = "));
  Serial.println(Ethernet.localIP());
  
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);
}

void loop() 
{
  if (!client.connected()) 
  {
    reconnect();
  }
  
  client.loop();
}
