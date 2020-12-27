/****************************************************************************************************************************
  Debug_STM32.h - Dead simple Ethernet web-server.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
       
  Version: 1.2.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries   
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
  1.1.2   K Hoang      19/11/2020 Add SSL debug feature. Enhance examples.
  1.2.0   K Hoang      20/11/2020 Add basic HTTP and WebSockets Client by merging ArduinoHttpClient
  1.2.1   K Hoang      26/12/2020 Suppress all possible compiler warnings
 *****************************************************************************************************************************/

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

#define ET_LOGERROR(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.println(x); }
#define ET_LOGERROR0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { ET_DEBUG_OUTPUT.print(x); }
#define ET_LOGERROR1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(y); }
#define ET_LOGERROR2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(z); }
#define ET_LOGERROR3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>0) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(z); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(w); }

///////////////////////////////////////

#define ET_LOGWARN(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.println(x); }
#define ET_LOGWARN0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { ET_DEBUG_OUTPUT.print(x); }
#define ET_LOGWARN1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(y); }
#define ET_LOGWARN2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(z); }
#define ET_LOGWARN3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>1) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(z); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(w); }

///////////////////////////////////////

#define ET_LOGINFO(x)          if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.println(x); }
#define ET_LOGINFO0(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { ET_DEBUG_OUTPUT.print(x); }
#define ET_LOGINFO1(x,y)       if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(y); }
#define ET_LOGINFO2(x,y,z)     if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(z); }
#define ET_LOGINFO3(x,y,z,w)   if(_ETHERNET_WEBSERVER_LOGLEVEL_>2) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(z); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(w); }

///////////////////////////////////////

#define ET_LOGDEBUG(x)         if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.println(x); }
#define ET_LOGDEBUG0(x)        if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { ET_DEBUG_OUTPUT.print(x); }
#define ET_LOGDEBUG1(x,y)      if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(y); }
#define ET_LOGDEBUG2(x,y,z)    if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(z); }
#define ET_LOGDEBUG3(x,y,z,w)  if(_ETHERNET_WEBSERVER_LOGLEVEL_>3) { ET_DEBUG_OUTPUT.print("[ETHERNET_WEBSERVER] "); ET_DEBUG_OUTPUT.print(x); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(y); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.print(z); ET_DEBUG_OUTPUT.print(" "); ET_DEBUG_OUTPUT.println(w); }

#endif    //EthernetWebServer_STM32_Debug_H
