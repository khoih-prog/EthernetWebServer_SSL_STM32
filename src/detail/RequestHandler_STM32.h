/****************************************************************************************************************************
  RequestHandler.h - Dead simple web-server.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
       
  Version: 1.1.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries   
  1.1.1   K Hoang      18/11/2020 Permit sites with "Chain could not be linked to a trust anchor" such as ThingStream
 *****************************************************************************************************************************/

#ifndef RequestHandler_STM32_h
#define RequestHandler_STM32_h

class RequestHandler
{
  public:

    virtual ~RequestHandler() { }

    virtual bool canHandle(HTTPMethod method, String uri)
    {
      return false;
    }

    virtual bool canUpload(String uri)
    {
      return false;
    }

    virtual bool handle(EthernetWebServer& server, HTTPMethod requestMethod, String requestUri)
    {
      return false;
    }

    virtual void upload(EthernetWebServer& server, String requestUri, HTTPUpload& upload) {}

    RequestHandler* next()
    {
      return _next;
    }

    void next(RequestHandler* r)
    {
      _next = r;
    }

  private:

    RequestHandler* _next = nullptr;
};

#endif //RequestHandler_STM32_h
