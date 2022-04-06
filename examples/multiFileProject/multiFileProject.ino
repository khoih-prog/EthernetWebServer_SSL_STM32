/****************************************************************************************************************************
  multiFileProject.ino
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define ETHERNET_WEBSERVER_SSL_STM32_VERSION_MIN_TARGET      "EthernetWebServer_SSL_STM32 v1.5.0"
#define ETHERNET_WEBSERVER_SSL_STM32_VERSION_MIN             1005000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <EthernetWebServer_SSL_STM32.h>      // https://github.com/khoih-prog/EthernetWebServer_SSL_STM32

void setup() 
{
  Serial.begin(115200);
  while (!Serial);

  delay(500);
  
  Serial.println("\nStart multiFileProject");
  Serial.println(ETHERNET_WEBSERVER_SSL_STM32_VERSION);

#if defined(ETHERNET_WEBSERVER_SSL_STM32_VERSION_MIN)
  if (ETHERNET_WEBSERVER_SSL_STM32_VERSION_INT < ETHERNET_WEBSERVER_SSL_STM32_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(ETHERNET_WEBSERVER_SSL_STM32_VERSION_MIN_TARGET);
  }
#endif

  Serial.print("You're OK now");
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
