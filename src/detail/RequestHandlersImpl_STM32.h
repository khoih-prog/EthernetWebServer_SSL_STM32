/****************************************************************************************************************************
  RequestHandlerImpl.h - Dead simple web-server.
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

#ifndef RequestHandlerImpl_STM32_h
#define RequestHandlerImpl_STM32_h

#include "RequestHandler_STM32.h"
#include "mimetable.h"

class FunctionRequestHandler : public RequestHandler
{
  public:

    FunctionRequestHandler(EthernetWebServer::THandlerFunction fn, EthernetWebServer::THandlerFunction ufn, const String &uri, HTTPMethod method)
      : _fn(fn)
      , _ufn(ufn)
      , _uri(uri)
      , _method(method)
    {
    }

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (_method != HTTP_ANY && _method != requestMethod)
        return false;

      if (requestUri == _uri)
        return true;

      if (_uri.endsWith("/*"))
      {
        String _uristart = _uri;
        _uristart.replace("/*", "");

        if (requestUri.startsWith(_uristart))
          return true;
      }

      return false;
    }

    bool canUpload(const String& requestUri) override
    {
      if (!_ufn || !canHandle(HTTP_POST, requestUri))
        return false;

      return true;
    }

    bool handle(EthernetWebServer& server, const HTTPMethod& requestMethod, const String& requestUri) override
    {
      ETW_UNUSED(server);
      
      if (!canHandle(requestMethod, requestUri))
        return false;

      _fn();
      return true;
    }

    void upload(EthernetWebServer& server, const String& requestUri, const HTTPUpload& upload) override
    {
      ETW_UNUSED(server);
      ETW_UNUSED(upload);
      
      if (canUpload(requestUri))
        _ufn();
    }

  protected:
    EthernetWebServer::THandlerFunction _fn;
    EthernetWebServer::THandlerFunction _ufn;
    String _uri;
    HTTPMethod _method;
};

class StaticRequestHandler : public RequestHandler
{
  public:

    bool canHandle(const HTTPMethod& requestMethod, const String& requestUri) override
    {
      if (requestMethod != HTTP_GET)
        return false;

      if ((_isFile && requestUri != _uri) || !requestUri.startsWith(_uri))
        return false;

      return true;
    }

#if USE_NEW_WEBSERVER_VERSION

    static String getContentType(const String& path)
    {
      using namespace mime;
      char buff[sizeof(mimeTable[0].mimeType)];

      // Check all entries but last one for match, return if found
      for (size_t i = 0; i < sizeof(mimeTable) / sizeof(mimeTable[0]) - 1; i++)
      {
        strcpy(buff, mimeTable[i].endsWith);

        if (path.endsWith(buff))
        {
          strcpy(buff, mimeTable[i].mimeType);
          return String(buff);
        }
      }

      // Fall-through and just return default type
      strcpy(buff, mimeTable[sizeof(mimeTable) / sizeof(mimeTable[0]) - 1].mimeType);
      return String(buff);
    }

#else

    static String getContentType(const String& path)
    {
      if (path.endsWith(".html"))           return "text/html";
      else if (path.endsWith(".htm"))       return "text/html";
      else if (path.endsWith(".css"))       return "text/css";
      else if (path.endsWith(".txt"))       return "text/plain";
      else if (path.endsWith(".js"))        return "application/javascript";
      else if (path.endsWith(".png"))       return "image/png";
      else if (path.endsWith(".gif"))       return "image/gif";
      else if (path.endsWith(".jpg"))       return "image/jpeg";
      else if (path.endsWith(".ico"))       return "image/x-icon";
      else if (path.endsWith(".svg"))       return "image/svg+xml";
      else if (path.endsWith(".ttf"))       return "application/x-font-ttf";
      else if (path.endsWith(".otf"))       return "application/x-font-opentype";
      else if (path.endsWith(".woff"))      return "application/font-woff";
      else if (path.endsWith(".woff2"))     return "application/font-woff2";
      else if (path.endsWith(".eot"))       return "application/vnd.ms-fontobject";
      else if (path.endsWith(".sfnt"))      return "application/font-sfnt";
      else if (path.endsWith(".xml"))       return "text/xml";
      else if (path.endsWith(".pdf"))       return "application/pdf";
      else if (path.endsWith(".zip"))       return "application/zip";
      else if (path.endsWith(".gz"))        return "application/x-gzip";
      else if (path.endsWith(".appcache"))  return "text/cache-manifest";

      return "application/octet-stream";
    }

#endif

  protected:

    String _uri;
    String _path;
    String _cache_header;
    bool _isFile;
    size_t _baseUriLength;
};



#endif //RequestHandlerImpl_STM32_h
