/****************************************************************************************************************************
  EthernetHttpClient_SSL_STM32.h - Dead simple HTTP WebClient.
  For STM32 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module

  EthernetWebServer_STM32 is a library for the STM32 running Ethernet WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_STM32
  Licensed under MIT license
  
  Version: 1.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries   
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.2.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
  1.3.0   K Hoang      11/04/2021 Add support to LAN8720 using STM32F4 or STM32F7
 *****************************************************************************************************************************/

// Library to simplify HTTP fetching on Arduino
// (c) Copyright Arduino. 2016
// Released under Apache License, version 2.0

#pragma once

#include <Arduino.h>

#include "detail/Debug_STM32.h"
#include "Ethernet_HTTPClient/Ethernet_HttpClient.h"
#include "Ethernet_HTTPClient/Ethernet_WebSocketClient.h"
#include "Ethernet_HTTPClient/Ethernet_URLEncoder.h"

