/****************************************************************************************************************************
  EthernetWebServer_SSL_STM32.h - Dead simple web-server.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_STM32
  
  Version: 1.5.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries   
  ...
  1.4.0   K Hoang      25/12/2021 Reduce usage of Arduino String with std::string. Fix bug
  1.4.1   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.4.2   K Hoang      11/01/2022 Fix libb64 fallthrough compile warning
  1.4.3   K Hoang      02/03/2022 Fix decoding error bug
  1.4.4   K Hoang      19/03/2022 Change licence from `MIT` to `GPLv3`
  1.4.5   K Hoang      29/03/2022 Sync with `SSLClient` v1.6.11
  1.5.0   K Hoang      05/04/2022 Use Ethernet_Generic library as default
  1.5.1   K Hoang      27/04/2022 Change from `arduino.cc` to `arduino.tips` in examples
 ****************************************************************************************************************************/

#pragma once

#ifndef ETHERNET_WEBSERVER_SSL_STM32_H
#define ETHERNET_WEBSERVER_SSL_STM32_H

#if ( USE_BUILTIN_ETHERNET && USING_LAN8720 )

  #if !( defined(ARDUINO_BLACK_F407VE)     || defined(ARDUINO_BLACK_F407VG)     || defined(ARDUINO_BLACK_F407ZE)     || defined(ARDUINO_BLACK_F407ZG)       || \
         defined(ARDUINO_BLUE_F407VE_Mini) || defined(ARDUINO_DIYMORE_F407VGT)  || defined(ARDUINO_FK407M1)          || defined(ARDUINO_VCCGND_F407ZG_MINI) || \
         defined(ARDUINO_GENERIC_F407VETX) || defined(ARDUINO_GENERIC_F407VGTX) || defined(ARDUINO_GENERIC_F407ZETX) || defined(ARDUINO_GENERIC_F407ZGTX)   || \
         defined(ARDUINO_GENERIC_F417VETX) || defined(ARDUINO_GENERIC_F417VGTX) || defined(ARDUINO_GENERIC_F417ZETX) || defined(ARDUINO_GENERIC_F417ZGTX)   || \
         defined(ARDUINO_GENERIC_F427ZGTX) || defined(ARDUINO_GENERIC_F427ZITX) || defined(ARDUINO_GENERIC_F429ZETX) || defined(ARDUINO_GENERIC_F429ZGTX)   || \
         defined(ARDUINO_GENERIC_F429ZGYX) || defined(ARDUINO_GENERIC_F429ZITX) || defined(ARDUINO_GENERIC_F429ZIYX) || defined(ARDUINO_GENERIC_F437ZGTX)   || \
         defined(ARDUINO_GENERIC_F437ZITX) || defined(ARDUINO_GENERIC_F439ZGTX) || defined(ARDUINO_GENERIC_F439ZITX) || defined(ARDUINO_GENERIC_F439ZGYX)   || \
         defined(ARDUINO_GENERIC_F439ZIYX) || defined(ARDUINO_DISCO_F746NG)     || defined(ARDUINO_NUCLEO_F746ZG)    || defined(ARDUINO_NUCLEO_F756ZG)      || \
         defined(ARDUINO_NUCLEO_H743ZI) )
    #error This code is designed to run on some STM32F4X7XX, STM32F4X9XX NUCLEO-F429ZI, STM32F74X, STM32F756, STM32F76X and STM32F77X platforms! Please check your Tools->Board setting.
  #endif

#elif ( USE_BUILTIN_ETHERNET )

  #if !( defined(STM32F0) || defined(STM32F1)  || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
         defined(STM32L0) || defined(STM32L1)  || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
         defined(STM32WB) || defined(STM32MP1) || defined(STM32L5) )
   #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
  #endif
  
#endif

#define ETHERNET_WEBSERVER_SSL_STM32_VERSION      "EthernetWebServer_SSL_STM32 v1.5.1"

#define ETHERNET_WEBSERVER_SSL_STM32_VERSION_MAJOR    1
#define ETHERNET_WEBSERVER_SSL_STM32_VERSION_MINOR    5
#define ETHERNET_WEBSERVER_SSL_STM32_VERSION_PATCH    1

#define ETHERNET_WEBSERVER_SSL_STM32_VERSION_INT      1005001

/////////////////////////////////////////////////////////////////////////

#if USE_BUILTIN_ETHERNET
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #if USING_LAN8720
      #warning Using built-in LAN8720 Ethernet with STM32Ethernet library from EthernetWebServer_SSL_STM32
    #else
      #warning Using built-in LAN8742A Ethernet with STM32Ethernet library from EthernetWebServer_SSL_STM32
    #endif
  #endif
#elif USE_UIP_ETHERNET
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using ENC28J60 Ethernet shield with UIPEthernet library from EthernetWebServer_SSL_STM32
  #endif
#elif USE_CUSTOM_ETHERNET
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
	  #warning Using Custom Ethernet library from EthernetWebServer_STM32. You must include a library or error
	#endif
#elif !( USE_ETHERNET_GENERIC || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC )  
  #include <Ethernet_Generic.h>
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using Ethernet_Generic library from EthernetWebServer_SSL_STM32
  #endif
#endif

#include "EthernetWebServer_SSL_STM32.hpp"
#include "EthernetWebServer_SSL_STM32-impl.h"
#include "Parsing_SSL_STM32-impl.h"

/////////////////////////////////////////////////////////////////////////

#endif  // ETHERNET_WEBSERVER_SSL_STM32_H
