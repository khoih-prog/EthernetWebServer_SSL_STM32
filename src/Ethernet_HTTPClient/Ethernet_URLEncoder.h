/****************************************************************************************************************************
  Ethernet_URLEncoder.h - Dead simple HTTP WebClient.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module

  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32

  Version: 1.6.0

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
  1.6.0   K Hoang      03/05/2022 Add support to STM32L5 and to custom SPI, such as SPI2, SPI3, SPI_New, etc.
 ****************************************************************************************************************************/

// Library to simplify HTTP fetching on Arduino
// (c) Copyright Arduino. 2019
// Released under Apache License, version 2.0

#pragma once

#ifndef ETHERNET_URL_ENCODER_H
#define ETHERNET_URL_ENCODER_H

#include <Arduino.h>

#include "detail/Debug_STM32.h"


class EthernetURLEncoderClass
{
  public:
    EthernetURLEncoderClass();
    virtual ~EthernetURLEncoderClass();

    static String encode(const char* str);
    static String encode(const String& str);

  private:
    static String encode(const char* str, int length);
};

extern EthernetURLEncoderClass EthernetURLEncoder;

#endif  // ETHERNET_URL_ENCODER_H
