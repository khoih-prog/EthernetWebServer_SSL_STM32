/****************************************************************************************************************************
  Debug_STM32.h - Dead simple Ethernet web-server.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
       
  Licensed under MIT license
  
  Version: 1.4.2

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries   
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.2.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
  1.3.0   K Hoang      11/04/2021 Add support to LAN8720 using STM32F4 or STM32F7
  1.3.1   K Hoang      04/10/2021 Change option for PIO `lib_compat_mode` from default `soft` to `strict`. Update Packages Patches
  1.4.0   K Hoang      25/12/2021 Reduce usage of Arduino String with std::string. Fix bug
  1.4.1   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.4.2   K Hoang      11/01/2022 Fix libb64 fallthrough compile warning
 *************************************************************************************************************************************/

#pragma once

#ifndef EthernetWebServer_STM32_Debug_H
#define EthernetWebServer_STM32_Debug_H

#include <stdio.h>

#ifdef DEBUG_ETHERNET_WEBSERVER_PORT
#define ET_DEBUG_OUTPUT DEBUG_ETHERNET_WEBSERVER_PORT
#else
#define ET_DEBUG_OUTPUT Serial
#endif

// Change _ETHERNET_WEBSERVER_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ETHERNET_WEBSERVER_LOGLEVEL_
  #define _ETHERNET_WEBSERVER_LOGLEVEL_       1
#endif

///////////////////////////////////////

const char EWS_MARK[]  = "[EWS] ";
const char EWS_SPACE[] = " ";
const char EWS_LINE[]  = "========================================\n";

#define EWS_PRINT_MARK   EWS_PRINT(EWS_MARK)
#define EWS_PRINT_SP     EWS_PRINT(EWS_SPACE)
#define EWS_PRINT_LINE   EWS_PRINT(EWS_LINE)

#define EWS_PRINT        ET_DEBUG_OUTPUT.print
#define EWS_PRINTLN      ET_DEBUG_OUTPUT.println

///////////////////////////////////////

#define ET_LOGERROR(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGERROR_LINE(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGERROR0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT(x); }
#define ET_LOGERROR1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGERROR2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGERROR3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGWARN(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGWARN_LINE(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGWARN0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT(x); }
#define ET_LOGWARN1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGWARN2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGWARN3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGINFO(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGINFO_LINE(x)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGINFO0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT(x); }
#define ET_LOGINFO1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGINFO2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGINFO3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

///////////////////////////////////////

#define ET_LOGDEBUG(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINTLN(x); }
#define ET_LOGDEBUG_LINE(x)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINTLN(x); EWS_PRINT_LINE; }
#define ET_LOGDEBUG0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT(x); }
#define ET_LOGDEBUG1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINTLN(y); }
#define ET_LOGDEBUG2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINTLN(z); }
#define ET_LOGDEBUG3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { EWS_PRINT_MARK; EWS_PRINT(x); EWS_PRINT_SP; EWS_PRINT(y); EWS_PRINT_SP; EWS_PRINT(z); EWS_PRINT_SP; EWS_PRINTLN(w); }

#endif    //EthernetWebServer_STM32_Debug_H
