/****************************************************************************************************************************
  Ethernet_WebSocketClient.h - Dead simple HTTP WebSockets Client.
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

// (c) Copyright Arduino. 2016
// Released under Apache License, version 2.0

#pragma once

#ifndef ETHERNET_WEBSOCKET_CLIENT_H
#define ETHERNET_WEBSOCKET_CLIENT_H

#include <Arduino.h>

#include "detail/Debug_STM32.h"

#include "Ethernet_HTTPClient/Ethernet_HttpClient.h"

static const int TYPE_CONTINUATION     = 0x0;
static const int TYPE_TEXT             = 0x1;
static const int TYPE_BINARY           = 0x2;
static const int TYPE_CONNECTION_CLOSE = 0x8;
static const int TYPE_PING             = 0x9;
static const int TYPE_PONG             = 0xa;

class EthernetWebSocketClient : public EthernetHttpClient
{
  public:
    EthernetWebSocketClient(Client& aClient, const char* aServerName, uint16_t aServerPort = EthernetHttpClient::kHttpPort);
    EthernetWebSocketClient(Client& aClient, const String& aServerName,
                            uint16_t aServerPort = EthernetHttpClient::kHttpPort);
    EthernetWebSocketClient(Client& aClient, const IPAddress& aServerAddress,
                            uint16_t aServerPort = EthernetHttpClient::kHttpPort);

    /** Start the Web Socket connection to the specified path
      @param aURLPath     Path to use in request (optional, "/" is used by default)
      @return 0 if successful, else error
    */
    int begin(const char* aPath = "/");
    int begin(const String& aPath);

    /** Begin to send a message of type (TYPE_TEXT or TYPE_BINARY)
        Use the write or Stream API's to set message content, followed by endMessage
        to complete the message.
      @param aURLPath     Path to use in request
      @return 0 if successful, else error
    */
    int beginMessage(int aType);

    /** Completes sending of a message started by beginMessage
      @return 0 if successful, else error
    */
    int endMessage();

    /** Try to parse an incoming messages
      @return 0 if no message available, else size of parsed message
    */
    int parseMessage();

    /** Returns type of current parsed message
      @return type of current parsedMessage (TYPE_TEXT or TYPE_BINARY)
    */
    int messageType();

    /** Returns if the current message is the final chunk of a split
        message
      @return true for final message, false otherwise
    */
    bool isFinal();

    /** Read the current messages as a string
      @return current message as a string
    */
    String readString();

    /** Send a ping
      @return 0 if successful, else error
    */
    int ping();

    // Inherited from Print
    virtual size_t write(uint8_t aByte);
    virtual size_t write(const uint8_t *aBuffer, size_t aSize);

    // Inherited from Stream
    virtual int   available();
    /** Read the next byte from the server.
      @return Byte read or -1 if there are no bytes available.
    */
    virtual int read();
    virtual int read(uint8_t *buf, size_t size);
    virtual int peek();

  private:
    void flushRx();

  private:
    bool      iTxStarted;
    uint8_t   iTxMessageType;
    uint8_t   iTxBuffer[128];
    uint64_t  iTxSize;

    uint8_t   iRxOpCode;
    uint64_t  iRxSize;
    bool      iRxMasked;
    int       iRxMaskIndex;
    uint8_t   iRxMaskKey[4];
};

#endif  // ETHERNET_WEBSOCKET_CLIENT_H
