/****************************************************************************************************************************
  multiFileProject.h
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _ETHERNET_WEBSERVER_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <EthernetWebServer_SSL_STM32.hpp>      // https://github.com/khoih-prog/EthernetWebServer_SSL_STM32

#include <EthernetHttpClient_SSL_STM32.h>       // https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
