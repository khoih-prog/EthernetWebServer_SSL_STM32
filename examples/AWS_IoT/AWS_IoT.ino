/****************************************************************************************************************************
  AWS IoT.ino - Dead simple SSL MQTT Client for Ethernet shields

  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module

  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
 *****************************************************************************************************************************/

/*
  Connect to AWS IOT using SSLClient and Wiz850io Ethernet Mdoule
   AWS_Root_CA.h is the trust anchor created using the Root CA from:
   https://www.amazontrust.com/repository/AmazonRootCA1.pem
   You can re-create it again using the python file present
   in SSLClient/tools/pycert_bearssl/pycert_bearssl.py
   python pycert_bearssl.py convert --no-search <certificate PEM file>
   refer: https://github.com/OPEnSLab-OSU/SSLClient/issues/17#issuecomment-700143405

  created 10 October 2020
  by Ram Rohit Gannavarapu
*/

#include "defines.h"

#include <PubSubClient.h>

#include "AWS_Root_CA.h" // This file is created using AmazonRootCA1.pem from https://www.amazontrust.com/repository/AmazonRootCA1.pem

#define THING_NAME          "<Thing_Name>"
#define MQTT_PACKET_SIZE    1024

void MQTTPublish(const char *topic, char *payload);
void updateThing();

const char my_cert[] =
  "-----BEGIN CERTIFICATE-----\n" \
  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" \
  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" \
  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" \
  "-----END CERTIFICATE-----\n";

const char my_key[] =
  "-----BEGIN RSA PRIVATE KEY-----\n" \
  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" \
  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" \
  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" \
  "-----END RSA PRIVATE KEY-----\n";

SSLClientParameters mTLS = SSLClientParameters::fromPEM(my_cert, sizeof my_cert, my_key, sizeof my_key);

const char* mqttServer = "xxxxxxxxxxxx-ats.iot.us-east-1.amazonaws.com";
const char publishShadowUpdate[] = "$aws/things/" THING_NAME "/shadow/update";
char publishPayload[MQTT_PACKET_SIZE];

const char *subscribeTopic[5] =
{
  String("$aws/things/" THING_NAME "/shadow/update/accepted").c_str(),
  String("$aws/things/" THING_NAME "/shadow/update/rejected").c_str(),
  String("$aws/things/" THING_NAME "/shadow/update/delta").c_str(),
  String("$aws/things/" THING_NAME "/shadow/get/accepted").c_str(),
  String("$aws/things/" THING_NAME "/shadow/get/rejected").c_str()
};

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for ( uint16_t i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}


EthernetClient ethClient;
EthernetSSLClient ethClientSSL(ethClient, TAs, (size_t)TAs_NUM, 1);
PubSubClient mqtt(mqttServer, 8883, callback, ethClientSSL);

void reconnect()
{
  while (!mqtt.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (mqtt.connect("arduinoClient"))
    {
      Serial.println("connected");

      for (int i = 0; i < 5; i++)
      {
        //Serial.println(subscribeTopic[i]);
        mqtt.subscribe(subscribeTopic[i]);
      }

      Serial.println("Started updateThing ");
      updateThing();
      Serial.println("Done updateThing ");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void updateThing()
{
  strcpy(publishPayload, "{\"state\": {\"reported\": {\"powerState\":\"ON\"}}}");
  MQTTPublish(publishShadowUpdate, publishPayload);
}

void MQTTPublish(const char *topic, char *payload)
{
  mqtt.publish(topic, payload);
  Serial.print("Published [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(payload);
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print("\nStart AWS_IoT on ");
  Serial.print(BOARD_NAME);
  Serial.print(" with ");
  Serial.println(SHIELD_TYPE);

#if USE_ETHERNET_GENERIC
  Serial.println(ETHERNET_GENERIC_VERSION);
#endif

  Serial.println(ETHERNET_WEBSERVER_SSL_STM32_VERSION);

  // Enable mutual TLS with SSLClient
  ethClientSSL.setMutualAuthParams(mTLS);

#if !(USE_BUILTIN_ETHERNET)
#if (USING_SPI2)
#if defined(CUR_PIN_MISO)
  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
  ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
  ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
  ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
  ET_LOGWARN(F("========================="));
#endif
#else
  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));
#endif
#endif

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // For other boards, to change if necessary
#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_CUSTOM_ETHERNET
  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  //Ethernet.init(USE_THIS_SS_PIN);

#endif  //( ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
#endif

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
}

void loop()
{
  if (!mqtt.connected())
  {
    reconnect();
  }

  mqtt.loop();
}
