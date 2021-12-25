/****************************************************************************************************************************
  mimetable.h - Dead simple web-server.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
       
  Licensed under MIT license
  
  Version: 1.4.0

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
 *************************************************************************************************************************************/
 
#ifndef __MIMETABLE_H__
#define __MIMETABLE_H__

namespace mime
{

enum type
{
  html,
  htm,
  css,
  txt,
  js,
  json,
  png,
  gif,
  jpg,
  ico,
  svg,
  ttf,
  otf,
  woff,
  woff2,
  eot,
  sfnt,
  xml,
  pdf,
  zip,
  gz,
  appcache,
  none,
  maxType
};

struct Entry
{
  const char endsWith[16]; 
  const char mimeType[32];
};

// Table of extension->MIME strings stored in PROGMEM, needs to be global due to GCC section typing rules
const Entry mimeTable[maxType] = 
{
    { ".html",      "text/html" },
    { ".htm",       "text/html" },
    { ".css",       "text/css" },
    { ".txt",       "text/plain" },
    { ".js",        "application/javascript" },
    { ".json",      "application/json" },
    { ".png",       "image/png" },
    { ".gif",       "image/gif" },
    { ".jpg",       "image/jpeg" },
    { ".ico",       "image/x-icon" },
    { ".svg",       "image/svg+xml" },
    { ".ttf",       "application/x-font-ttf" },
    { ".otf",       "application/x-font-opentype" },
    { ".woff",      "application/font-woff" },
    { ".woff2",     "application/font-woff2" },
    { ".eot",       "application/vnd.ms-fontobject" },
    { ".sfnt",      "application/font-sfnt" },
    { ".xml",       "text/xml" },
    { ".pdf",       "application/pdf" },
    { ".zip",       "application/zip" },
    { ".gz",        "application/x-gzip" },
    { ".appcache",  "text/cache-manifest" },
    { "",           "application/octet-stream" } 
};
//extern const Entry mimeTable[maxType];
}


#endif
