## EthernetWebServer_SSL_STM32

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer_SSL_STM32.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer_SSL_STM32.svg)](http://github.com/khoih-prog/EthernetWebServer_SSL_STM32/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Important Note for STM32F boards using built-in LAN8742A Ethernet](#important-note-for-stm32f-boards-using-built-in-lan8742a-ethernet)
  * [Currently Supported Boards by AsyncWebServer_STM32](#currently-supported-boards-by-asyncwebserver_stm32)
* [Why do we need the new Async AsyncWebServer_STM32 library](#why-do-we-need-the-new-async-asyncwebserver_stm32-library)
* [Why do we need this EthernetWebServer_SSL_STM32 library](#why-do-we-need-this-ethernetwebserver_ssl_stm32-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
  * [Not supported boards](#not-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For STM32 boards to use LAN8720](#1-for-stm32-boards-to-use-lan8720)
  * [2. For STM32 boards to use Serial1](#2-for-stm32-boards-to-use-serial1)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. Optional UIPthernet patch](#7-optional-uipthernet-patch) 
* [Configuration Notes](#configuration-notes)
  * [1. How to select which built-in Ethernet or shield to use](#1-how-to-select-which-built-in-ethernet-or-shield-to-use)
    * [Select **one and only one** Ethernet library to use as follows:](#select-one-and-only-one-ethernet-library-to-use-as-follows)
    * [To use built-in LAN8742A](#to-use-built-in-lan8742a)
    * [To use LAN8720](#to-use-lan8720)
    * [To use W5x00 Ethernet, for example using EthernetLarge library](#to-use-w5x00-ethernet-for-example-using-ethernetlarge-library)
    * [To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)](#to-use-enc28j60-ethernet-using-ethernetenc-library-new-and-better)
    * [To use ENC28J60 Ethernet, using UIPEthernet library](#to-use-enc28j60-ethernet-using-uipethernet-library)
  * [2. How to select which SPI to use](#2-How-to-select-which-SPI-to-use)
  * [Important](#important)
  * [3. How to connect or select another CS/SS pin to use](#3-how-to-connect-or-select-another-csss-pin-to-use)
  * [4. How to increase W5x00 TX/RX buffer](#4-how-to-increase-w5x00-txrx-buffer)
  * [5. How to adjust sendContent_P() and send_P() buffer size](#5-how-to-adjust-sendcontent_p-and-send_p-buffer-size)
* [WebServer and non TLS/SSL WebClient Usage](#webserver-and-non-tlsssl-webclient-usage)
  * [Init the CS/SS pin if use EthernetWrapper](#init-the-csss-pin-if-use-ethernetwrapper) 
  * [Class Constructor](#class-constructor)
  * [Basic Operation](#basic-operations)
  * [Advanced Options](#advanced-options)
  * [Other Function Calls](#other-function-calls)
* [TLS/SSL WebClient Usage](#tlsssl-webclient-usage)
  * [Overview](#overview) 
    * [1. Board and Network Peripheral Requirements](#1-board-and-network-peripheral-requirements)
    * [2. How to use Trust Anchors TA](#2-how-to-use-trust-anchors-ta)
    * [3. Note](#3-note)
* [How It Works](#how-it-works)
* [Other Features](#other-features)
  * [Logging](#logging) 
  * [Errors](#errors)
  * [Write Buffering](#write-buffering)
  * [Session Caching](#session-caching)
  * [mTLS](#mtls)
* [Implementation Notes](#implementation-notes)
  * [Seeding Random Data](#seeding-random-data) 
  * [Certificate Verification](#certificate-verification)
  * [Resources](#resources)
  * [Read Buffer Overflow](#read-buffer-overflow)
  * [Cipher Support](#cipher-support)
  * [Known Issues](#known-issues)
* [HOWTO use STM32F4 with LAN8720](#howto-use-stm32f4-with-lan8720)
  * [1. Wiring](#1-wiring)
  * [2. HOWTO program using STLink V-2 or V-3](#2-howto-program-using-stlink-v-2-or-v-3)
  * [3. HOWTO use Serial Port for Debugging](#3-howto-use-serial-port-for-debugging)
* [Examples](#examples)
  * [WebServer, TLS/SSL Client Examples](#webserver-tlsssl-client-examples)
    * [ 1. AdvancedWebServer](examples/AdvancedWebServer)
    * [ 2. HelloServer](examples/HelloServer)
    * [ 3. HelloServer2](examples/HelloServer2)
    * [ 4. HttpBasicAuth](examples/HttpBasicAuth)
    * [ 5. MQTTClient_Auth](examples/MQTTClient_Auth)
    * [ 6. MQTTClient_Basic](examples/MQTTClient_Basic)
    * [ 7. MQTTClient_SSL](examples/MQTTClient_SSL)
    * [ 8. MQTTClient_SSL_Auth](examples/MQTTClient_SSL_Auth)
    * [ 9. MQTTClient_SSL_Complex](examples/MQTTClient_SSL_Complex)
    * [10. PostServer](examples/PostServer)
    * [11. SimpleAuthentication](examples/SimpleAuthentication)
    * [12. UdpNTPClient](examples/UdpNTPClient)
    * [13. UdpSendReceive](examples/UdpSendReceive)
    * [14. WebClient](examples/WebClient)
    * [15. WebClientMulti_SSL](examples/WebClientMulti_SSL)
    * [16. WebClientRepeating](examples/WebClientRepeating)
    * [17. WebClient_SSL](examples/WebClient_SSL)
    * [18. WebServer](examples/WebServer)
    * [19. **MQTTS_ThingStream**](examples/MQTTS_ThingStream)
    * [20. **MQTT_ThingStream**](examples/MQTT_ThingStream)
    * [21. **AWS_IoT**](examples/AWS_IoT) **New**
    * [22. multiFileProject](examples/multiFileProject) **New**
  * [HTTP and WebSocket Client New Examples](#http-and-websocket-client-new-examples)
    * [ 1. BasicAuthGet](examples/HTTPClient/BasicAuthGet)
    * [ 2. CustomHeader](examples/HTTPClient/CustomHeader)
    * [ 3. DweetGet](examples/HTTPClient/DweetGet)
    * [ 4. DweetPost](examples/HTTPClient/DweetPost)
    * [ 5. HueBlink](examples/HTTPClient/HueBlink)
    * [ 6. node_test_server](examples/HTTPClient/node_test_server)
    * [ 7. PostWithHeaders](examples/HTTPClient/PostWithHeaders)
    * [ 8. SimpleDelete](examples/HTTPClient/SimpleDelete)
    * [ 9. SimpleGet](examples/HTTPClient/SimpleGet)
    * [10. SimpleHTTPExample](examples/HTTPClient/SimpleHTTPExample)
    * [11. SimplePost](examples/HTTPClient/SimplePost)
    * [12. SimplePut](examples/HTTPClient/SimplePut)
    * [13. SimpleWebSocket](examples/HTTPClient/SimpleWebSocket)
  * [LAN8720 Examples](#lan8720-examples)
    * [ 1. MQTTClient_SSL_LAN8720](examples/STM32_LAN8720/MQTTClient_SSL_LAN8720)
    * [ 2. MQTTClient_SSL_Auth_LAN8720](examples/STM32_LAN8720/MQTTClient_SSL_Auth_LAN8720)
    * [ 3. MQTTClient_SSL_Complex_LAN8720](examples/STM32_LAN8720/MQTTClient_SSL_Complex_LAN8720)
    * [ 4. WebClient_SSL_LAN8720](examples/STM32_LAN8720/WebClient_SSL_LAN8720)
    * [ 5. WebClientMulti_SSL_LAN8720](examples/STM32_LAN8720/WebClientMulti_SSL_LAN8720)
    * [ 6. **MQTTS_ThingStream_LAN8720**](examples/STM32_LAN8720/MQTTS_ThingStream_LAN8720)
* [Example AdvancedWebServer](#example-advancedwebserver)
  * [1. File AdvancedWebServer.ino](#1-file-advancedwebserverino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. AdvancedWebServer on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library](#1-advancedwebserver-on-nucleo_f767zi-using-built-in-lan8742a-ethernet-and-stm32ethernet-library)
  * [2. WebClientRepeating on NUCLEO_F767ZI using ENC28J60 and new EthernetENC Library](#2-webclientrepeating-on-nucleo_f767zi-using-enc28j60-and-new-ethernetenc-library)
  * [3. UdpNTPClient on NUCLEO_F767ZI using W5500 and Ethernet_Generic Library](#3-udpntpclient-on-nucleo_f767zi-using-w5500-and-Ethernet_Generic-library)
  * [4. WebClient_SSL on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library](#4-webclient_ssl-on-nucleo_f767zi-using-built-in-lan8742a-ethernet-and-stm32ethernet-library)
  * [5. WebClient_SSL on NUCLEO_F767ZI using W5x00 and Ethernet_Generic Library](#5-webclient_ssl-on-nucleo_f767zi-using-w5x00-and-Ethernet_Generic-library)
  * [6. WebClientMulti_SSL on NUCLEO_F767ZI using ENC28J60 and EthernetENC Library](#6-webclientmulti_ssl-on-nucleo_f767zi-using-enc28j60-and-ethernetenc-library)
  * [7. MQTTClient_SSL_Complex on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library](#7-mqttclient_ssl_complex-on-nucleo_f767zi-using-built-in-lan8742a-ethernet-and-stm32ethernet-library)
  * [8. MQTTClient_SSL_Complex on NUCLEO_F767ZI using W5x00 and Ethernet_Generic Library](#8-mqttclient_ssl_complex-on-nucleo_f767zi-using-w5x00-and-Ethernet_Generic-library)
  * [9. MQTTS_ThingStream on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library](#9-mqtts_thingstream-on-nucleo_f767zi-using-built-in-lan8742a-ethernet-and-stm32ethernet-library)
  * [10. MQTTS_ThingStream on NUCLEO_F767ZI using ENC28J60 and EthernetENC Library](#10-mqtts_thingstream-on-nucleo_f767zi-using-enc28j60-and-ethernetenc-library)
  * [11. MQTTS_ThingStream on NUCLEO_F767ZI using W5x00 and Ethernet_Generic Library](#11-mqtts_thingstream-on-nucleo_f767zi-using-w5x00-and-Ethernet_Generic-library)
  * [12. MQTTS_ThingStream_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library](#12-mqtts_thingstream_lan8720-on-black_f407ve-with-lan8720-ethernet-and-stm32ethernet-library)
  * [13. WebClient_SSL_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library](#13-webclient_ssl_lan8720-on-black_f407ve-with-lan8720-ethernet-and-stm32ethernet-library)
  * [14. MQTTClient_SSL_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library](#14-mqttclient_ssl_lan8720-on-black_f407ve-with-lan8720-ethernet-and-stm32ethernet-library)
  * [15. MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library](#15-mqttclient_ssl_complex_lan8720-on-black_f407ve-with-lan8720-ethernet-and-stm32ethernet-library)
  * [16. AdvancedWebServer on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library and custom SPI](#16-AdvancedWebServer-on-NUCLEO_L552ZE_Q-with-W5x00-using-Ethernet_Generic-Library-and-custom-SPI)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Note for STM32F boards using built-in LAN8742A Ethernet

This [**EthernetWebServer_SSL_STM32 Library**](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32), by design, is working synchronously. The Client requests must be handled by continuously checking in loop() using :

```cpp
void loop()
{
  server.handleClient();
}
```

The new [**AsyncWebServer_STM32 Library**](https://github.com/khoih-prog/AsyncWebServer_STM32), in contrast, is designed to work asynchronously. The Client requests are handled on demand, without continuously checking in loop(). The loop() now can be as simple as :

```cpp
void loop()
{
}
```

#### Currently Supported Boards by [**AsyncWebServer_STM32**](https://github.com/khoih-prog/AsyncWebServer_STM32)

1. Nucleo-144 (F429ZI, F746ZG, F756ZG, F767ZI)
2. Discovery STM32F746G-DISCOVERY
3. Any STM32 boards with enough flash/memory and already configured to run LAN8742A Ethernet.

---

### Why do we need the new Async [AsyncWebServer_STM32 library](https://github.com/khoih-prog/AsyncWebServer_STM32)

- Using asynchronous network means that you can handle **more than one connection at the same time**
- **You are called once the request is ready and parsed**
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- **Easy to use API, HTTP Basic and Digest MD5 Authentication (default), ChunkedResponse**
- Easily extensible to handle **any type of content**
- Supports Continue 100
- **Async WebSocket plugin offering different locations without extra servers or ports**
- Async EventSource (Server-Sent Events) plugin to send events to the browser
- URL Rewrite plugin for conditional and permanent url rewrites
- ServeStatic plugin that supports cache, Last-Modified, default index and more
- Simple template processing engine to handle templates

---
---

### Why do we need this [EthernetWebServer_SSL_STM32 library](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32)

#### Features

This [EthernetWebServer_SSL_STM32 library](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32) is a simple yet complete TLS/SSL WebClient and non-TLS/SSL WebServer library for **STM32F/L/H/G/WB/MP1** boards using Ethernet shields. The functions are similar and compatible to those of [`ESP32 WebServer`](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) and [`ESP8266WebServer`](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) libraries to make life much easier to port sketches from ESP8266/ESP32.

This [EthernetWebServer_SSL_STM32 library](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32) adds [TLS 1.2](https://www.websecurity.digicert.com/security-topics/what-is-ssl-tls-https) functionality to EthernetClient, using BearSSL as an underlying TLS engine.

This [**EthernetWebServer_SSL_STM32 library**](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32), from v1.2.0, also provides high-level **HTTP and WebSocket Client** with the functions are similar and compatible to those of [**ArduinoHttpClient Library**](https://github.com/arduino-libraries/ArduinoHttpClient)

The [**EthernetWebServer_SSL_STM32 library**](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32) supports:

1. TCP Server and Client
2. UDP Server and Client
3. HTTP Server and HTTP/HTTPS Client
4. HTTPS GET and POST requests, provides argument parsing, handles one client at a time.
5. **High-level HTTP (GET, POST, PUT, PATCH, DELETE) and WebSocket Client**. From v1.2.0.

Library is based on and modified from:

1. [Ivan Grokhotkov's ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
2. [Ivan Grokhotkov's ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
3. [OPEnSLab-OSU's SSLClient v1.6.9](https://github.com/OPEnSLab-OSU/SSLClient)
4. [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient)

The EthernetWebServer class, found in `EthernetWebServer.h` header, is a simple WebServer class, knowing how to handle HTTP requests such as GET and POST and can only support one one client at a time.

The EthernetSSLClient class, found in `SSLClient.h` header, is a simple WebClient class, knowing how to handle HTTP/HTTPS requests such as GET and POST and can only support one client at a time.

Check [`EthernetWebServer Library Issue: Support for STM32F Series`](https://github.com/khoih-prog/EthernetWebServer/issues/1) for reason to create this separate library from [`EthernetWebServer_SSL library`](https://github.com/khoih-prog/EthernetWebServer_SSL)

---

#### Currently supported Boards

1. **STM32 boards with built-in Ethernet LAN8742A** such as :

  - **Nucleo-144 (F429ZI, F767ZI)**
  - **Discovery (STM32F746G-DISCOVERY)**
  - **All STM32 boards (STM32F/L/H/G/WB/MP1) with 32K+ Flash, with Built-in Ethernet**
  - See [EthernetWebServer_STM32 Support and Test Results](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
  
2. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running W5x00 or ENC28J60 shields)**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4, STM32L5
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

3. **STM32 boards using Ethernet LAN8720** such as :

  - **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
  - **Discovery (DISCO_F746NG)**
  - **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

#### Currently supported Ethernet shields/modules

1. W5x00 using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library

2. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library

3. ENC28J60 using new [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library

4. LAN8720 using new [`STM32Ethernet`](https://github.com/stm32duino/STM32Ethernet) and [`LwIP`](https://github.com/stm32duino/LwIP) libraries.


#### Not supported boards

These boards are not supported:

- Some Nucleo-32 (small Flash/memory)
- Eval (no Serial, just need to redefine in sketch, library and UIPEthernet)
- Generic STM32F0 (small Flash/memory)
- Generic STM32F1 (with 64-K Flash): C6
- Generic STM32F3 : no HardwareSPI.h
- Electronics Speed Controllers (small Flash/memory)

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino Core for STM32 v2.3.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 3.  [`Functional-Vlpp library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
 4. For built-in LAN8742A or LAN8720 Ethernet:
   - [`STM32Ethernet library v1.3.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
   - [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
 5. For W5x00 Ethernet:
   - [`Ethernet_Generic library v2.7.1+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
 6. For ENC28J60 Ethernet:
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
   
---

## Installation

### Use Arduino Library Manager

The best way is to use `Arduino Library Manager`. Search for **`EthernetWebServer_SSL_STM32`**, then select / install the latest version. 
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL_STM32) for more detailed instructions.

### Manual Install

1. Navigate to [**EthernetWebServer_SSL_STM32**](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32) page.
2. Download the latest release `EthernetWebServer_SSL_STM32-main.zip`.
3. Extract the zip file to `EthernetWebServer_SSL_STM32-main` directory 
4. Copy whole 
  - `EthernetWebServer_SSL_STM32-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**EthernetWebServer_SSL_STM32** library](https://registry.platformio.org/libraries/khoih-prog/EthernetWebServer_SSL_STM32) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/EthernetWebServer_SSL_STM32/installation). Search for **EthernetWebServer_SSL_STM32** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h`


#### 2. For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. Optional UIPthernet patch

Check if you need to install the UIPthernet patch [new STM32 core F3/F4 compatibility](https://github.com/UIPEthernet/UIPEthernet/commit/c6d6519a260166b722b9cee5dd1f0fb2682e6782) to avoid errors `#include HardwareSPI.h` on some STM32 boards (Nucleo-32 F303K8, etc.)


---
---

## Configuration Notes

### 1. How to select which built-in Ethernet or shield to use

#### Select **one and only one** Ethernet library to use as follows:

- Standard W5x00 Ethernet_Generic library 

Standard W5x00 is using `Ethernet_Generic` library by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  true
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use built-in LAN8742A

```cpp
#define USE_BUILTIN_ETHERNET    true
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use LAN8720

```cpp
#define USING_LAN8720           true
#define USE_BUILTIN_ETHERNET    true
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use W5x00 Ethernet, for example using Ethernet_Generic library

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  true
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      true
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use ENC28J60 Ethernet, using UIPEthernet library

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        true

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

- To use another Ethernet library
For example, EthernetLarge library

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET_GENERIC  false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   true
#endif

....

#elif USE_CUSTOM_ETHERNET
  //#include "Ethernet_XYZ.h"
  #include "EthernetLarge.h"
  #warning Using Custom Ethernet library. You must include a library and initialize.
  #define SHIELD_TYPE           "Custom Ethernet & Ethernet_XYZ Library"
#else
  #define USE_ETHERNET_GENERIC   true
  #include "Ethernet_Generic.h"
  #warning Using default Ethernet_Generic lib
  #define SHIELD_TYPE           "W5x00 using default Ethernet_Generic Library"
#endif  
...


#include <EthernetWebServer_SSL_STM32.h>
```

#### 2. How to select which SPI to use


To use standard SPI, check if 

```cpp
#define USING_CUSTOM_SPI        false
#define USING_SPI2              false
```


To use SPI2 or any custom SPI


```cpp
// Be sure to use true only if necessary for your board, or compile error
#define USING_CUSTOM_SPI            true

#if ( USING_CUSTOM_SPI )
  // Currently test OK for F767ZI and L552ZE_Q
  #define USING_SPI2                  true

  #if (USING_SPI2)
    //#include <SPI.h>
    // For L552ZE-Q, F767ZI, but you can change the pins for any other boards
    // SCK: 23,  MOSI: 22, MISO: 25, SS/CS: 24 for SPI1
    #define CUR_PIN_MISO              25
    #define CUR_PIN_MOSI              22
    #define CUR_PIN_SCK               23
    #define CUR_PIN_SS                24

    #define SPI_NEW_INITIALIZED       true

    // Don't create the instance with CUR_PIN_SS, or Ethernet not working
    // To change for other boards' SPI libraries
    SPIClass SPI_New(CUR_PIN_MOSI, CUR_PIN_MISO, CUR_PIN_SCK);
    
    //#warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 24

    #if defined(USE_THIS_SS_PIN)
      #undef USE_THIS_SS_PIN
    #endif   
    #define USE_THIS_SS_PIN       CUR_PIN_SS    //24
    
  #endif
  
#endif
```


---

### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---

### 3. How to connect or select another CS/SS pin to use

**The default CS/SS pin is 10 for all boards, and is configurable in code.**

If the default pin is not correct, select another CS/SS pin (e.e. D22) to use as follows:

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
// You can define here or customize for each board at same place with BOARD_TYPE
#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
// Default pin 10 to SS/CS. To change according to your board, if necessary
//#define USE_THIS_SS_PIN       10
```

The current SPI pin usage can be displayed by turn on the debug option. For example:

Increase debug level to 2 in `defines.h` of any example:

```cpp
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2
```

The Debug Terminal will then show that the current SPI pin usage of **NUCLEO_F767ZI ==> SS/CS: D10, MOSI: D11, MISO: D12 and SCK: D13** when using W5x00

```cpp
Start AdvancedWebServer on NUCLEO_F767ZI, using W5x00 using Ethernet_Generic Library
Ethernet_Generic v2.7.1
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
Connected! IP address: 192.168.2.89
```

Connect the wires according to the displayed information.


### 4. How to increase W5x00 TX/RX buffer

- For **Ethernet_Generic** library only,  simply use as follows to have large buffer similar to EthernetLarge library
```cpp
#define ETHERNET_LARGE_BUFFERS
```

- For **Ethernet3** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```


### 5. How to adjust sendContent_P() and send_P() buffer size

sendContent_P() and send_P() buffer size is set default at 4 Kbytes, and minimum is 512 bytes. If you need to change, just add a definition, e.g.:

```cpp
#define SENDCONTENT_P_BUFFER_SZ     2048
```

Note that the buffer size must be larger than 512 bytes. See [Sending GZIP HTML ~ 120kb+ (suggested enhancement)](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/3).



---
---

### WebServer and non TLS/SSL WebClient Usage

#### Class Constructor

```cpp
  EthernetWebServer server(80);
```

Creates the EthernetWebServer class object.

*Parameters:* 
 
host port number: ``int port`` (default is the standard HTTP port 80)

#### Basic Operations

**Starting the server**

```cpp
  void begin();
```

**Handling incoming client requests**

```cpp
  void handleClient();
```

**Disabling the server**

```cpp
  void close();
  void stop();
```

Both methods function the same

**Client request handlers**

```cpp
  void on();
  void addHandler();
  void onNotFound();
  void onFileUpload();	
```

Example:

```cpp
  server.on("/", handlerFunction);
  server.onNotFound(handlerFunction);   // called when handler is not assigned
  server.onFileUpload(handlerFunction); // handle file uploads
```

**Sending responses to the client**

```cpp
  void send();
  void send_P();
  void sendContent_P();
```

`Parameters:`

`code` - HTTP response code, can be `200` or `404`, etc.

`content_type` - HTTP content type, like `"text/plain"` or `"image/png"`, etc.

`content` - actual content body

#### Advanced Options

**Getting information about request arguments**

```cpp
  const String & arg();
  const String & argName();
  int args();
  bool hasArg();
```

`Function usage:`

`arg` - get request argument value, use `arg("plain")` to get POST body
	
`argName` - get request argument name
	
`args` - get arguments count
	
`hasArg` - check if argument exist

**Getting information about request headers**

```cpp
  const String & header();
  const String & headerName();
  const String & hostHeader();
  int headers();
  bool hasHeader();
``` 
`Function usage:`

`header` - get request header value

`headerName` - get request header name

`hostHeader` - get request host header if available, else empty string
  
`headers` - get header count
	
`hasHeader` - check if header exist

**Authentication**

```cpp
  bool authenticate();
  void requestAuthentication();
```

`Function usage:`

`authenticate` - server authentication, returns true if client is authenticated else false

`requestAuthentication` - sends authentication failure response to the client

`Example Usage:`

```cpp

  if(!server.authenticate(username, password))
  {
    server.requestAuthentication();
  }
```

#### Other Function Calls

```cpp
  const String & uri(); // get the current uri
  HTTPMethod  method(); // get the current method 
  WiFiClient client(); // get the current client
  HTTPUpload & upload(); // get the current upload
  void setContentLength(); // set content length
  void sendHeader(); // send HTTP header
  void sendContent(); // send content
  void sendContent_P();  // send content in PROGMEM
  void collectHeaders(); // set the request headers to collect
  void serveStatic();
  size_t streamFile();
```

---

### TLS/SSL WebClient Usage

Have a look at marvellous documentation in [SSLClient](https://openslab-osu.github.io/SSLClient/index.html) for more information about the underlying EthernetSSLClient.

The following info is taken and modified from [SSLClient README](https://github.com/OPEnSLab-OSU/SSLClient/blob/master/README.md)

#### Overview

Using EthernetSSLClient is similar to using any other Arduino-based Client class. There are a few extra things, however, that you will need to get started:

##### 1. Board and Network Peripheral Requirements

Your board should have a lot of resources (>110kb flash and >7kb RAM), and your network peripheral should have a large internal buffer (>7kb).

##### 2. How to use Trust Anchors TA

You will need a header containing array of trust anchors ([trust_anchors](examples/WebClient_SSL/trust_anchors.h)), which are used to verify the SSL connection later on. **This file must generated for every project if connecting to different TLS/SSL WebServers.** Check out [TrustAnchors.md](./TrustAnchors.md#generating-trust-anchors) on how to generate this file for your project, and for more information about what a trust anchor is.


Once all those are ready, you can create an SSLClient object like this:

```C++
// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM)
```

Where:
* `EthernetClient` - The type of `client`
* `client` - An instance of the EthernetClient class you are using for EthernetSSLClient. It is important that this instance be stored *outside* the `EthernetSSLClient` declaration. 

For instance: 

```cpp
EthernetSSLClient(EthernetClient() ...)
```

wouldn't work.

* TAs - The name of the trust anchor array created in step 2. If you generated a header using the tutorial this will probably be `TAs`.
* TAs_NUM -  The number of trust anchors in TAs. If you generated a header using the tutorial this will probably be `TAs_NUM`.


Given this client, simply use `EthernetSSLClient` as you would the base client class:

```C++
if (sslClient.connect(www.arduino.cc, 443))
{
  // Make a HTTP request:
  sslClient.println(GET /asciilogo.txt HTTP/1.1);
  sslClient.println("User-Agent: SSLClientOverEthernet");
  sslClient.print("Host: ");
  sslClient.println(server);
  sslClient.println("Connection: close");
  sslClient.println();
  sslClient.flush();
}
else
{
  // if you didn't get a connection to the server:
  Serial.println("connection failed");
}
```

##### 3. Note

`sslClient.connect("www.arduino.cc", 443)` can take 5-15 seconds to finish. This an unavoidable consequence of the SSL protocol, and is detailed in [Implementation Notes](#resources).

For more information on `EthernetSSLClient`, check out the [examples](./examples), [API documentation](https://openslab-osu.github.io/SSLClient/index.html), or the rest of this README.

---

## How It Works

`EthernetSSLClient` was created to integrate SSL seamlessly with the Arduino infrastructure, and so it does just that: implementing the brilliant [BearSSL](https://bearssl.org/) as a proxy in front of any Arduino socket library. `BearSSL` is designed with low flash footprint in mind, and as a result does little verification of improper programming, relying on the developer to ensure the code is correct. Since `EthernetSSLClient` is built specifically for the Arduino ecosystem, most of `EthernetSSLClient`'s code adds those programming checks back in, making debugging a fast and simple process.

## Other Features

### Logging

`EthernetSSLClient` also allows for changing the debugging level by adding an additional parameter to the constructor:

```C++
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM, 1, SSLClient::SSL_INFO);)
```

Logging is always outputted through the [Arduino Serial interface](https://www.arduino.cc/reference/en/language/functions/communication/serial/), so you'll need to setup Serial before you can view the SSL logs. Log levels are enumerated in ::DebugLevel. The log level is set to `SSL_WARN` by default.

### Errors

When `EthernetSSLClient` encounters an error, it will attempt to terminate the SSL session gracefully if possible, and then close the socket. Simple error information can be found from EthernetSSLClient::getWriteError(), which will return a value from the ::Error enum. For more detailed diagnostics, you can look at the serial logs, which will be displayed if the log level is at `SSL_ERROR` or lower.

### Write Buffering

As you may have noticed in the documentation for EthernetSSLClient::write, calling this function does not actually write to the network. Instead, you must call EthernetSSLClient::available or EthernetSSLClient::flush, which will detect that the buffer is ready and write to the network (see EthernetSSLClient::write for details).

This was implemented as a buffered function because examples in Arduino libraries will often write to the network like so:

```C++
EthernetClient client;
// ...
// connect to ardiuino.cc over ssl (port 443 for websites)
client.connect("www.arduino.cc", 443);
// ...
// write an http request to the network
client.write("GET /asciilogo.txt HTTP/1.1\r\n");
client.write("Host: arduino.cc\r\n");
client.write("Connection: close\r\n");
// wait for response
while (!client.available()) { /* ... */ }
// ...
```

Notice that every single write() call immediately writes to the network, which is fine with most network clients. With SSL, however, if we are encrypting and writing to the network every write() call, this will result in a lot of small encryption tasks. Encryption takes a lot of time and code, so to reduce the overhead of an SSL connection, SSLClient::write implicitly buffers until the developer states that they are waiting for data to be received with EthernetSSLClient::available. A simple example can be found below:

```C++
// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM)

// ...
// connect to arduino.cc over ssl (port 443 for websites)
sslClient.connect("www.arduino.cc", 443);
// ...
// add http request to the buffer
sslClient.write("GET /asciilogo.txt HTTP/1.1\r\n");
sslClient.write("Host: arduino.cc\r\n");
sslClient.write("Connection: close\r\n");

// write the bytes to the network, then wait for response
while (!sslClient.available());
// ...
```

If you would like to trigger a network write manually without using the EthernetSSLClient::available, you can also call EthernetSSLClient::flush, which will write all data and return when finished.

### Session Caching

As detailed in the [Resources section](#resources), `SSL` handshakes take an extended period (1-4sec) to negotiate. To remedy this problem, BearSSL is able to keep a [SSL session cache](https://bearssl.org/api1.html#session-cache) of the clients it has connected to. If `BearSSL` successfully resumes an `SSL` session, it can reduce connection time to 100-500ms.

In order to use `SSL` session resumption:

 * The website you are connecting to must support it. Support is widespread, but you can verify easily using the [SSLLabs tool](https://www.ssllabs.com/ssltest/).
 *  You must reuse the same `EthernetSSLClient` object (`SSL` Sessions are stored in the object itself).
 *  You must reconnect to the exact same server.

`EthernetSSLClient` automatically stores an IP address and hostname in each session, ensuring that if you call `connect("www.google.com")`, `EthernetSSLClient` will use the `SSL` session with that hostname. However, because some websites have multiple servers on a single IP address (github.com being an example), you may find that even if you are connecting to the same host the connection does not resume. This is a flaw in the SSL session protocol — though it has been resolved in `TLS 1.3`, the lack of widespread adoption of the new protocol prevents it from being used here. SSL sessions can also expire based on server criteria, which will result in a standard 4-10 second connection.

`SSL` sessions take a lot of memory to store, so by default `EthernetSSLClient` will only store one at a time. You can change this behavior by adding the following to your `EthernetSSLClient` declaration:

```C++
// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM, SomeNumber);
```

Where `SomeNumber` is the number of sessions you would like to store. For example this declaration can store 3 sessions:

```C++
EthernetClient    client;
EthernetSSLClient sslClient(client, TAs, (size_t)TAs_NUM, 3);
```

Sessions are managed internally using the `SSLSession::getSession` function. This function will cycle through sessions in a rotating order, allowing the session cache to continually overwrite old sessions. In general, it is a good idea to use a SessionCache size equal to the number of domains you plan on connecting to.

If you need to clear a session, you can do so using the `SSLSession::removeSession` function.

### mTLS

As of `v1.6.0`, `EthernetSSLClient` supports [mutual TLS authentication](https://developers.cloudflare.com/access/service-auth/mtls/). mTLS is a variant of TLS that verifies both the server and device identities before a connection, and is commonly used in IoT protocols as a secure layer (MQTT over TLS, HTTPS over TLS, etc.).

To use `mTLS with SSLClient` you will need to a client certificate and client private key associated with the server you are attempting to connect to.

Depending on your use case, you will either generate these yourself (ex. [Mosquito MQTT setup](http://www.steves-internet-guide.com/creating-and-using-client-certificates-with-mqtt-and-mosquitto/)), or have them generated for you (ex. [AWS IoT Certificate Generation](https://docs.aws.amazon.com/iot/latest/developerguide/create-device-certificate.html)). Given this cryptographic information, you can modify the standard `EthernetSSLClient` connection sketch to enable `mTLS authentication`:

```C++
...
/* Somewhere above setup() */

// The client certificate, can be PEM or DER format
// DER format will be an array of raw bytes, and PEM format will be a string
// PEM format is shown below
const char my_cert[] = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDpDCCAowCCQC7mCk5Iu3YmDANBgkqhkiG9w0BAQUFADCBkzELMAkGA1UEBhMC\n"
...
"-----END CERTIFICATE-----\n";

// The client private key, must be the same format as the client certificate
// Both RSA and ECC are supported, ECC is shown below
const char my_key[] = 
"-----BEGIN EC PRIVATE KEY-----\n"
...
"-----END EC PRIVATE KEY-----\n";

// This line will parse and store the above information so SSLClient can use it later
// Replace `fromPEM` with `fromDER` if you are using DER formatted certificates.
SSLClientParameters mTLS = SSLClientParameters::fromPEM(my_cert, sizeof(cert), my_key, sizeof(key));
EthernetSSLClient my_client(...);
...
void setup() {
    ...
    /* Before SSLClient connects */

    my_client.setMutualAuthParams(mTLS);
    ...
}
...
```

The client certificate must be formatted correctly (according to [BearSSL's specification](https://bearssl.org/apidoc/bearssl__pem_8h.html)) in order for mTLS to work. If the certificate is improperly formatted, SSLClient will attempt to make a regular TLS connection instead of an mTLS one, and fail to connect as a result. Because of this, if you are seeing errors similar to `"peer did not send certificate chain"` on your server, check that your certificate and key are formatted correctly (see [MQTT SSL possible?](https://github.com/OPEnSLab-OSU/SSLClient/issues/7#issuecomment-593704969)). For more information on SSLClient's mTLS functionality, please see the [SSLClientParameters documentation](https://openslab-osu.github.io/SSLClient/class_s_s_l_client_parameters.html).

Note that both the above client certificate information *as well as* the correct trust anchors associated with the server are needed for the connection to succeed. Trust anchors will typically be generated from the CA used to generate the server certificate. More information on generating trust anchors can be found in [TrustAnchors.md](./TrustAnchors.md). 

---
---

## Implementation Notes

Some ideas that didn't quite fit in the API documentation.

### Seeding Random Data

The SSL protocol requires that `EthernetSSLClient` generate some random bits before connecting with a server. `BearSSL` provides a random number generator but requires a [some entropy for a seed](https://bearssl.org/apidoc/bearssl__ssl_8h.html#a7d8e8de2afd49d6794eae02f56f81152). Normally this seed is generated by taking the microsecond time using the internal clock, however since most microcontrollers are not build with this feature another source must be found.

### Certificate Verification

`EthernetSSLClient` uses `BearSSL's` [minimal x509 verification engine](https://bearssl.org/x509.html#the-minimal-engine) to verify the certificate of an `SSL` connection. This engine requires the developer create a trust anchor array using values stored in trusted root certificates. Check out [TrustAnchors document](./TrustAnchors.md) for more details on this component of `EthernetSSLClient`.

`BearSSL` also features a [known certificate validation engine](https://bearssl.org/x509.html#the-known-key-engine), which only allows for a single domain in exchange for a significantly reduced resource usage (flash and CPU time). This functionality is planned to be implemented in the future.

### Resources

The `SSL` protocol recommends a device support many different encryption algorithms, as well as protocols for `SSL` itself. The complexity of both of those components results in many medium sized components forming an extremely large whole. Additionally, most embedded processors lack the sophisticated math hardware commonly found in a modern CPU, and as a result require more instructions to create the encryption algorithms SSL requires. This not only increases size but makes the algorithms slow and memory intensive.

If flash footprint is becoming a problem, there are numerous debugging strings (~3kb estimated) that can be removed from `SSLClient.h` and `SSLClient.cpp`.

### Read Buffer Overflow

`SSL` is a buffered protocol, and since most microcontrollers have limited resources (see [Resources](#resources)), `EthernetSSLClient` is limited in the size of its buffers. A common problem encountered with `SSL` connections is buffer overflow, caused by the server sending too much data at once. This problem is caused by the microcontroller being unable to copy and decrypt data faster than it is being received, forcing some data to be discarded. This usually puts `BearSSL` in an unrecoverable state, forcing `EthernetSSLClient` to close the connection with a write error. If you are experiencing frequent timeout problems, this could be the reason why. 

In order to remedy this problem, the device must be able to read the data faster than it is being received, or alternatively have a cache large enough to store the entire payload. Since `SSL's` encryption forces the device to read slowly, this means we must increase the cache size. Depending on your platform, there are a number of ways this can be done:

* Sometimes your communication shield will have an internal buffer, which can be expanded through the driver code. This is the case with the Arduino Ethernet library (in the form of the `MAX_SOCK_NUM` and `ETHERNET_LARGE_BUFFERS` macros), however the library must be modified for the change to take effect.
* `EthernetSSLClient` has an internal buffer EthernetSSLClient::m_iobuf, which can be expanded. `BearSSL` limits the amount of data that can be processed based on the stage in the SSL handshake, and so this will change will have limited usefulness. 
* In some cases, a website will send so much data that even with the above solutions, `EthernetSSLClient` will be unable to keep up (a website with a lot of HTML is an example). In these cases you will have to find another method of retrieving the data you need.
* If none of the above are viable, it is possible to implement your own Client class which has an internal buffer much larger than both the driver and `BearSSL`. This would require in-depth knowledge of programming and the communication shield you are working with, as well as a microcontroller with a significant amount of RAM.

### Cipher Support

By default, `EthernetSSLClient` supports only TLS1.2 and the ciphers listed in [TLS12_only_profile.c](./src/SSLClient/TLS12_only_profile.c) under `suites[]`, and the list is relatively small to keep the connection secure and the flash footprint down. These ciphers should work for most applications, however if for some reason you would like to use an older version of TLS or a different cipher, you can change the BearSSL profile being used by SSLClient to an [alternate one with support for older protocols](./src/SSLClient/bearssl/src/ssl/ssl_client_full.c). To do this, edit `EthernetSSLClient::EthernetSSLClient` to change these lines:

```C++
br_client_init_TLS12_only(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
// comment the above line and uncomment the line below if you're having trouble connecting over SSL
// br_ssl_client_init_full(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
```
to this:

```C++
// br_client_init_TLS12_only(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
// comment the above line and uncomment the line below if you're having trouble connecting over SSL
br_ssl_client_init_full(&m_sslctx, &m_x509ctx, m_trust_anchors, m_trust_anchors_num);
```
If for some unfortunate reason you need SSL 3.0 or SSL 2.0, you will need to modify the BearSSL profile to enable support. Check out the [BearSSL profiles documentation](https://bearssl.org/api1.html#profiles) and I wish you the best of luck.

### Known Issues

 * In some drivers (Ethernet), calls to `Client::flush` will hang if internet is available but there is no route to the destination. Unfortunately SSLClient cannot correct for this without modifying the driver itself, and as a result the recommended solution is ensuring you choose a driver with built-in timeouts to prevent freezing. Check [Calls to stop before connected cause lockups.](https://github.com/OPEnSLab-OSU/SSLClient/issues/13#issuecomment-643855923).
 
 * When using PubSubClient on the ESP32, a stack overflow will occur if the user does not flush the buffer immediately after writing. The cause of this issue is under active investigation. More information in issue [PubSubClient on ESP32 overflows the stack](https://github.com/OPEnSLab-OSU/SSLClient/issues/9).
 
---
---

### HOWTO use STM32F4 with LAN8720

#### 1. Wiring

This is the Wiring for STM32F4 (BLACK_F407VE, etc.) using LAN8720


|LAN8720 PHY|<--->|STM32F4|
|:-:|:-:|:-:|
|TX1|<--->|PB_13|
|TX_EN|<--->|PB_11|
|TX0|<--->|PB_12|
|RX0|<--->|PC_4|
|RX1|<--->|PC_5|
|nINT/RETCLK|<--->|PA_1|
|CRS|<--->|PA_7|
|MDIO|<--->|PA_2|
|MDC|<--->|PC_1|
|GND|<--->|GND|
|VCC|<--->|+3.3V|

---

#### 2. HOWTO program using STLink V-2 or V-3

Connect as follows. To program, use **STM32CubeProgrammer** or Arduino IDE with 

- **U(S)ART Support: "Enabled (generic Serial)"**
- **Upload Method : "STM32CubeProgrammer (SWD)"**


|STLink|<--->|STM32F4|
|:-:|:-:|:-:|
|SWCLK|<--->|SWCLK|
|SWDIO|<--->|SWDIO|
|RST|<--->|NRST|
|GND|<--->|GND|
|5v|<--->|5V|


<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/raw/main/pics/STM32F407VET6.png">
</p>

---

#### 3. HOWTO use Serial Port for Debugging

Connect FDTI (USB to Serial) as follows:

|FDTI|<--->|STM32F4|
|:-:|:-:|:-:|
|RX|<--->|TX=PA_9|
|TX|<--->|RX=PA_10|
|GND|<--->|GND|


---
---

### Examples:

#### WebServer, TLS/SSL Client Examples

 1. [AdvancedWebServer](examples/AdvancedWebServer)
 2. [HelloServer](examples/HelloServer)
 3. [HelloServer2](examples/HelloServer2)
 4. [HttpBasicAuth](examples/HttpBasicAuth)
 5. [MQTTClient_Auth](examples/MQTTClient_Auth)
 6. [MQTTClient_Basic](examples/MQTTClient_Basic)
 7. [MQTTClient_SSL](examples/MQTTClient_SSL)
 8. [MQTTClient_SSL_Auth](examples/MQTTClient_SSL_Auth)
 9. [MQTTClient_SSL_Complex](examples/MQTTClient_SSL_Complex)
10. [PostServer](examples/PostServer)
11. [SimpleAuthentication](examples/SimpleAuthentication)
12. [UdpNTPClient](examples/UdpNTPClient)
13. [UdpSendReceive](examples/UdpSendReceive)
14. [WebClient](examples/WebClient)
15. [WebClientMulti_SSL](examples/WebClientMulti_SSL)
16. [WebClientRepeating](examples/WebClientRepeating)
17. [WebClient_SSL](examples/WebClient_SSL)
18. [WebServer](examples/WebServer)
19. [**MQTTS_ThingStream**](examples/MQTTS_ThingStream)
20. [**MQTT_ThingStream**](examples/MQTT_ThingStream)
21. [**AWS_IoT**](examples/AWS_IoT) **New**
22. [multiFileProject](examples/multiFileProject) **New**

#### HTTP and WebSocket Client New Examples

 1. [BasicAuthGet](examples/HTTPClient/BasicAuthGet)
 2. [CustomHeader](examples/HTTPClient/CustomHeader)
 3. [DweetGet](examples/HTTPClient/DweetGet)
 4. [DweetPost](examples/HTTPClient/DweetPost)
 5. [HueBlink](examples/HTTPClient/HueBlink)
 6. [node_test_server](examples/HTTPClient/node_test_server)
 7. [PostWithHeaders](examples/HTTPClient/PostWithHeaders)
 8. [SimpleDelete](examples/HTTPClient/SimpleDelete)
 9. [SimpleGet](examples/HTTPClient/SimpleGet)
10. [SimpleHTTPExample](examples/HTTPClient/SimpleHTTPExample)
11. [SimplePost](examples/HTTPClient/SimplePost)
12. [SimplePut](examples/HTTPClient/SimplePut)
13. [SimpleWebSocket](examples/HTTPClient/SimpleWebSocket)


#### LAN8720 Examples

 1. [MQTTClient_SSL_LAN8720](examples/STM32_LAN8720/MQTTClient_SSL_LAN8720)
 2. [MQTTClient_SSL_Auth_LAN8720](examples/STM32_LAN8720/MQTTClient_SSL_Auth_LAN8720)
 3. [MQTTClient_SSL_Complex_LAN8720](examples/STM32_LAN8720/MQTTClient_SSL_Complex_LAN8720)
 4. [WebClient_SSL_LAN8720](examples/STM32_LAN8720/WebClient_SSL_LAN8720)
 5. [WebClientMulti_SSL_LAN8720](examples/STM32_LAN8720/WebClientMulti_SSL_LAN8720)
 6. [**MQTTS_ThingStream_LAN8720**](examples/STM32_LAN8720/MQTTS_ThingStream_LAN8720)


---
---

### Example [AdvancedWebServer](examples/AdvancedWebServer)

#### 1. File [AdvancedWebServer.ino](examples/AdvancedWebServer/AdvancedWebServer.ino)

https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/blob/3990bade0f461e3cc47b9f7b3c4de9810d24f726/examples/AdvancedWebServer/AdvancedWebServer.ino#L40-L270


#### 2. File [defines.h](examples/AdvancedWebServer/defines.h)

https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/blob/3990bade0f461e3cc47b9f7b3c4de9810d24f726/examples/AdvancedWebServer/defines.h#L13-L224


---
---

### Debug Terminal Output Samples

#### 1. AdvancedWebServer on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library

Following is debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on STM32F7 Nucleo-144 NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/raw/main/pics/AdvancedWebServer.png">
</p>

```cpp
Start AdvancedWebServer on NUCLEO_F767ZI, using LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
HTTP EthernetWebServer is @ IP : 192.168.2.117
.[EWS] String Len = 0, extend to 2048
EthernetWebServer::handleClient: New Client
method:  GET
url:  /
search:
headerName: Host
headerValue: 192.168.2.150
headerName: Connection
headerValue: keep-alive
headerName: Cache-Control
headerValue: max-age=0
headerName: DNT
headerValue: 1
headerName: Upgrade-Insecure-Requests
headerValue: 1
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: Accept
headerValue: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
args:
args count:  0
args:
args count:  0
Request: /
Arguments: 
Final list of key/value pairs:
EthernetWebServer::_handleRequest handle
EthernetWebServer::send1: len =  341
content =  <html><head><meta http-equiv='refresh' content='5'/><title>AdvancedWebServer NUCLEO_F767ZI</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hi from EthernetWebServer!</h2><h3>on NUCLEO_F767ZI</h3><p>Uptime: 0 d 00:00:31</p><img src="/test.svg" /></body></html>
EthernetWebServer::_prepareHeader sendHeader Conn close
EthernetWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 341
Connection: close

EthernetWebServer::sendContent: Client.write content:  <html><head><meta http-equiv='refresh' content='5'/><title>AdvancedWebServer NUCLEO_F767ZI</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h2>Hi from EthernetWebServer!</h2><h3>on NUCLEO_F767ZI</h3><p>Uptime: 0 d 00:00:31</p><img src="/test.svg" /></body></html>
EthernetWebServer::_handleRequest OK
EthernetWebServer::handleClient: Don't keepCurrentClient
EthernetWebServer::handleClient: Client disconnected
EthernetWebServer::handleClient: New Client
method:  GET
url:  /test.svg
search:
headerName: Host
headerValue: 192.168.2.150
headerName: Connection
headerValue: keep-alive
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: DNT
headerValue: 1
headerName: Accept
headerValue: image/webp,image/apng,image/*,*/*;q=0.8
headerName: Referer
headerValue: http://192.168.2.150/
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
args:
args count:  0
args:
args count:  0
Request: /test.svg
Arguments: 
Final list of key/value pairs:
EthernetWebServer::_handleRequest handle
EthernetWebServer::send1: len =  1949
content =  <svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="310" height="150">
<rect width="310" height="150" fill="rgb(250, 230, 210)" stroke-width="1" stroke="rgb(0, 0, 0)" />
<g stroke="black">
<line x1="10" y1="90" x2="20" y2="22" stroke-width="1" />
<line x1="20" y1="22" x2="30" y2="98" stroke-width="1" />
<line x1="30" y1="98" x2="40" y2="64" stroke-width="1" />
<line x1="40" y1="64" x2="50" y2="104" stroke-width="1" />
<line x1="50" y1="104" x2="60" y2="31" stroke-width="1" />
<line x1="60" y1="31" x2="70" y2="59" stroke-width="1" />
<line x1="70" y1="59" x2="80" y2="139" stroke-width="1" />
<line x1="80" y1="139" x2="90" y2="117" stroke-width="1" />
<line x1="90" y1="117" x2="100" y2="75" stroke-width="1" />
<line x1="100" y1="75" x2="110" y2="72" stroke-width="1" />
<line x1="110" y1="72" x2="120" y2="137" stroke-width="1" />
<line x1="120" y1="137" x2="130" y2="20" stroke-width="1" />
<line x1="130" y1="20" x2="140" y2="94" stroke-width="1" />
<line x1="140" y1="94" x2="150" y2="81" stroke-width="1" />
<line x1="150" y1="81" x2="160" y2="38" stroke-width="1" />
<line x1="160" y1="38" x2="170" y2="33" stroke-width="1" />
<line x1="170" y1="33" x2="180" y2="53" stroke-width="1" />
<line x1="180" y1="53" x2="190" y2="88" stroke-width="1" />
<line x1="190" y1="88" x2="200" y2="32" stroke-width="1" />
<line x1="200" y1="32" x2="210" y2="110" stroke-width="1" />
<line x1="210" y1="110" x2="220" y2="87" stroke-width="1" />
<line x1="220" y1="87" x2="230" y2="11" stroke-width="1" />
<line x1="230" y1="11" x2="240" y2="98" stroke-width="1" />
<line x1="240" y1="98" x2="250" y2="76" stroke-width="1" />
<line x1="250" y1="76" x2="260" y2="121" stroke-width="1" />
<line x1="260" y1="121" x2="270" y2="139" stroke-width="1" />
<line x1="270" y1="139" x2="280" y2="103" stroke-width="1" />
<line x1="280" y1="103" x2="290" y2="60" stroke-width="1" />
<line x1="290" y1="60" x2="300" y2="36" stroke-width="1" />
</g>
</svg>

EthernetWebServer::_prepareHeader sendHeader Conn close
EthernetWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: image/svg+xml
Content-Length: 1949
Connection: close

```

---

#### 2. WebClientRepeating on NUCLEO_F767ZI using ENC28J60 and new EthernetENC Library

The following is debug terminal output when running example [WebClientRepeating](examples/WebClientRepeating) on STM32F7 Nucleo-144 NUCLEO_F767ZI using **ENC28J60 and new EthernetENC Library**

```cpp
Start WebClientRepeating on NUCLEO_F767ZI, using ENC28J60 & EthernetENC Library
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.123
Connecting...
HTTP/1.1 200 OK
Date: Wed, 27 Apr 2022 17:12:43 GMT
Content-Type: text/plain
Content-Length: 2263
Connection: close
x-amz-id-2: Y0KDwqmE5CUvFMSLnxWUV4XoqEDCUL1h9GN+vWHRz7vpjDK77h8fqAbuEqBXVEZRm3Ybv7bCZtE=
x-amz-request-id: EFJSRB21CQFZQDRX
Last-Modified: Wed, 23 Feb 2022 14:56:42 GMT
ETag: "667cf48afcc12c38c8c1637947a04224"
CF-Cache-Status: DYNAMIC
Report-To: {"endpoints":[{"url":"https:\/\/a.nel.cloudflare.com\/report\/v3?s=T2F7koaxDm8y3draFWHzKSKtqF3brIseyVbvIpy%2FDp4RGAh7d6Lc%2F7rw%2B96w7hYckhvRgN1l9sMJJuNuQCxG8JZeCIelNLNXDBKH5BJajxjC7kMiQ3PwdUm8jFr%2B0aA%3D"}],"group":"cf-nel","max_age":604800}
NEL: {"success_fraction":0,"report_to":"cf-nel","max_age":604800}
Server: cloudflare
CF-RAY: 70292f44ceb3a253-YYZ
alt-svc: h3=":443"; ma=86400, h3-29=":443"; ma=86400


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   
```

---

#### 3. UdpNTPClient on NUCLEO_F767ZI using W5500 and Ethernet_Generic Library

3. The following is debug terminal output when running example [UdpNTPClient](examples/UdpNTPClient) on STM32F7 Nucleo-144 NUCLEO_F767ZI using **W5500 and Ethernet_Generic Library**

```cpp
Start UdpNTPClient on NUCLEO_F767ZI, using W5x00 & Ethernet_Generic Library
Ethernet_Generic v2.7.1
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.123
UDP Packet received, size 48
From 132.163.97.1, port 123
Seconds since Jan 1 1900 = 3809283621
Unix time = 1600294821
The UTC time is 22:20:21
```

---

#### 4. WebClient_SSL on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library

4. The terminal output of **NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library** running [WebClient_SSL example](examples/WebClient_SSL)

```cpp
Start WebClient_SSL on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] =========================
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
Using mac index = 10
Connected! IP address: 192.168.2.139
Connecting to : www.arduino.cc, port : 443
Connected to www.arduino.cc
Took: 480
Using micros()
2A 5C A7 84 DC 48 AB 3E C6 80 4E E D8 88 4C FE 
Using analogRead()
3E 76 9B B8 CD E9 F4 FE 8 D 12 14 C 1B 20 1D 
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 08:33:53 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=de77338a7e6c914c4dd309cecf5dcdb3b1604997233; expires=Thu, 10-Dec-20 08:33:53 GMT; path=/; domain=.arduino.cc; HttpOnly; SameSite=Lax
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Access-Control-Allow-Origin: https://www.arduino.cc
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Accept,Authorization,Cache-Control,Content-Type,DNT,If-Modified-Since,Keep-Alive,Origin,User-Agent,X-Mx-ReqToken,X-Requested-With
Strict-Transport-Security: max-age=500; includeSubDomains
X-Frame-Options: SAMEORIGIN
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
cf-request-id: 0652e352a40000b683be849000000001
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 5efe6e643ecfb683-YWG

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3324 bytes in 0.5398 s, rate = 6.16 kbytes/second
```

---

#### 5. WebClient_SSL on NUCLEO_F767ZI using W5x00 and Ethernet_Generic Library

The terminal output of **NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library** running [WebClient_SSL example](examples/WebClient_SSL)

```cpp
Start WebClient_SSL on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
Ethernet_Generic v2.7.1
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
SPI_CS:10
=========================
Using mac index = 10
Connected! IP address: 192.168.2.139
Connecting to : www.arduino.cc, port : 443
Connected to www.arduino.cc
Took: 421
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 08:42:12 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=dc0d46f4fc488c76630a1c7327c64d5861604997732; expires=Thu, 10-Dec-20 08:42:12 GMT; path=/; domain=.arduino.cc; HttpOnly; SameSite=Lax
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Access-Control-Allow-Origin: https://www.arduino.cc
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Accept,Authorization,Cache-Control,Content-Type,DNT,If-Modified-Since,Keep-Alive,Origin,User-Agent,X-Mx-ReqToken,X-Requested-With
Strict-Transport-Security: max-age=500; includeSubDomains
X-Frame-Options: SAMEORIGIN
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
cf-request-id: 0652eaf1aa0000cabc368f8000000001
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 5efe7a95dacecabc-YYZ
alt-svc: h3-27=":443"; ma=86400, h3-28=":443"; ma=86400, h3-29=":443"; ma=86400

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3405 bytes in 0.4360 s, rate = 7.81 kbytes/second
```
---

#### 6. WebClientMulti_SSL on NUCLEO_F767ZI using ENC28J60 and EthernetENC Library

The terminal output of **NUCLEO_F767ZI with ENC28J60 & EthernetENC Library** running [WebClientMulti_SSL example](examples/WebClientMulti_SSL)

```cpp
Start WebClientMulti_SSL on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] =========================
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:11
MISO:12
SCK:13
SS:10
=========================
Using mac index = 10
Connected! IP address: 192.168.2.139
Connecting to www.arduino.cc...
Took: 2261
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 09:24:02 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=d588a3b3b35b8e56eb1b7031f46c283b91605000242; expires=Thu, 10-Dec-20 09:24:02 GMT; path=/; domain=.arduino.cc; HttpOnly; SameSite=Lax
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Access-Control-Allow-Origin: https://www.arduino.cc
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Accept,Authorization,Cache-Control,Content-Type,DNT,If-Modified-Since,Keep-Alive,Origin,User-Agent,X-Mx-ReqToken,X-Requested-With
Strict-Transport-Security: max-age=500; includeSubDomains
X-Frame-Options: SAMEORIGIN
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
cf-request-id: 0653113b580000b65f28017000000001
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 5efeb7d88c03b65f-YWG

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3324 bytes in 0.3587 s, rate = 9.27 kbytes/second
Connecting to www.cloudflare.com...
Took: 1683
HTTP/1.1 200 OK
Date: Tue, 10 Nov 2020 09:24:09 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=d14958859d5dad28f89ca90056c3547b91605000249; expires=Thu, 10-Dec-20 09:24:09 GMT; path=/; domain=.www.cloudflare.com; HttpOnly; SameSite=Lax; Secure
Access-Control-Allow-Origin: *
Server: cloudflare
CF-RAY: 5efeb8061b0eb65f-YWG
X-Frame-Options: SAMEORIGIN
Expires: Thu, 01 Jan 1970 00:00:01 GMT
Cache-Control: no-cache

bb
fl=168f4
h=www.cloudflare.com
ip=76.10.180.220
ts=1605000249.298
visit_scheme=https
uag=SSLClientOverEthernet
colo=YWG
http=http/1.1
loc=CA
tls=TLSv1.2
sni=plaintext
warp=off
gateway=off

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3998 bytes in 0.0656 s, rate = 60.98 kbytes/second
```

---

#### 7. MQTTClient_SSL_Complex on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library

The terminal output of **NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library** running [MQTTClient_SSL_Complex example](examples/MQTTClient_SSL_Complex)

```cpp
Start MQTTClient_SSL_Complex on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.96
Attempting MQTT connection to broker.emqx.io...connected
Published connection message successfully!
Subscribed to: STM32_Sub
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 6990
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 6990
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 11992
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 11992
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 16998
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 16998
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 22004
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 22004
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 27010
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 27010
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 32016
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 32016
```

---

#### 8. MQTTClient_SSL_Complex on NUCLEO_F767ZI using W5x00 and Ethernet_Generic Library

The terminal output of **NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library** running [MQTTClient_SSL_Complex example](examples/MQTTClient_SSL_Complex)

```cpp
Start MQTTClient_SSL_Complex on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
Ethernet_Generic v2.7.1
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.107
Attempting MQTT connection to broker.emqx.io...connected
Published connection message successfully!
Subscribed to: STM32_Sub
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 5001
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 5001
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 10007
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 10007
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 15013
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 15013
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 20019
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 20019
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 25025
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex on NUCLEO_F767ZI, millis = 25025
```

---

#### 9. MQTTS_ThingStream on NUCLEO_F767ZI using Built-in LAN8742A Ethernet and STM32Ethernet Library

The terminal output of **NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library** running [MQTTS_ThingStream example](examples/MQTTS_ThingStream)

```cpp
Start MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.97
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subscribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
```

---

#### 10. MQTTS_ThingStream on NUCLEO_F767ZI using ENC28J60 and EthernetENC Library

The terminal output of **NUCLEO_F767ZI with ENC28J60 & EthernetENC Library** running [MQTTS_ThingStream example](examples/MQTTS_ThingStream)

```cpp
Start MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.97
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subscribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with ENC28J60 & EthernetENC Library
```

---

#### 11. MQTTS_ThingStream on NUCLEO_F767ZI using W5x00 and Ethernet_Generic Library

The terminal output of **NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library** running [MQTTS_ThingStream example](examples/MQTTS_ThingStream)

```cpp
Start MQTTS_ThingStream_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
Ethernet_Generic v2.7.1
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
You're connected to the network, IP = 192.168.2.107
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subscribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
```

---

#### 12. MQTTS_ThingStream_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library

The terminal output of **BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library** running [MQTTS_ThingStream_LAN8720 example](examples/STM32_LAN8720/MQTTS_ThingStream_LAN8720)

```cpp
Start MQTTS_ThingStream_ThingStream on on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
You're connected to the network, IP = 192.168.2.107
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subscribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
```

---

#### 13. WebClient_SSL_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library

The terminal output of **BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library** running [WebClient_SSL_LAN8720 example](examples/STM32_LAN8720/WebClient_SSL_LAN8720)

```cpp
Start WebClient_SSL_LAN8720 on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
Using mac index = 6
Connected! IP address: 192.168.2.138
Connecting to : www.arduino.cc, port : 443
Connected to www.arduino.cc
Took: 776
HTTP/1.1 200 OK
Date: Sun, 11 Apr 2021 18:32:19 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Set-Cookie: __cfduid=d3798c650bbc319e17e80cc276988dd3c1618165939; expires=Tue, 11-May-21 18:32:19 GMT; path=/; domain=.arduino.cc; HttpOnly; SameSite=Lax
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Strict-Transport-Security: max-age=500; includeSubDomains
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
cf-request-id: 0963cdd4ce0000f97deeac8000000001
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 63e64c014c93f97d-YYZ
alt-svc: h3-27=":443"; ma=86400, h3-28=":443"; ma=86400, h3-29=":443"; ma=86400

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

(EthernetSSLClient)(SSL_WARN)(connected): Socket was dropped unexpectedly (this can be an alternative to closing the connection)

Disconnecting.
Received 3059 bytes in 0.4299 s, rate = 7.12 kbytes/second
```

---

#### 14. MQTTClient_SSL_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library

The terminal output of **BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library** running [MQTTClient_SSL_LAN8720 example](examples/STM32_LAN8720/MQTTClient_SSL_LAN8720)

```cpp
Start MQTTClient_SSL_LAN8720 on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
You're connected to the network, IP = 192.168.2.138
Attempting MQTT connection to broker.emqx.io...connected
Published connection message successfully!
Subscribed to: STM32_Sub
Message Send : STM32_Pub => Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message Send : STM32_Pub => Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message Send : STM32_Pub => Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message Send : STM32_Pub => Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_LAN8720 on BLACK_F407VE

```

---

#### 15. MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library

The terminal output of **BLACK_F407VE with LAN8720 Ethernet and STM32Ethernet Library** running [MQTTClient_SSL_Complex_LAN8720 example](examples/STM32_LAN8720/MQTTClient_SSL_Complex_LAN8720)

```cpp
Start MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE with LAN8720 Ethernet & STM32Ethernet Library
EthernetWebServer_SSL_STM32 v1.6.0
You're connected to the network, IP = 192.168.2.142
Attempting MQTT connection to broker.emqx.io...connected
Published connection message successfully!
Subscribed to: STM32_Sub
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 6546
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 6546
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 11549
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 11549
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 16557
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 16557
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 21565
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 21565
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 26573
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 26573
Message Send : STM32_Pub => Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 31581
Message arrived [STM32_Pub] Hello from MQTTClient_SSL_Complex_LAN8720 on BLACK_F407VE, millis = 31581
```

---

#### 16. AdvancedWebServer on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library and custom SPI

Following is debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on NUCLEO_L552ZE_Q, using W5500 Ethernet with Ethernet_Generic Library and custom SPI

<p align="center">
    <img src="https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/raw/main/pics/AdvancedWebServer_NUCLEO_L552ZE_Q.png">
</p>


```cpp
Start AdvancedWebServer on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library and custom SPI
Ethernet_Generic v2.7.1
EthernetWebServer_SSL_STM32 v1.6.0
[EWS] Default SPI pinout:
[EWS] MOSI: 22
[EWS] MISO: 25
[EWS] SCK: 23
[EWS] SS: 24
[EWS] =========================
Connected! IP address: 192.168.2.116
HTTP EthernetWebServer is @ IP : 192.168.2.116
.[EWS] String Len = 0, extend to 2048
......... .....
```


---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _ETHERNET_WEBSERVER_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial
// Use this to disable all output debug msgs
// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
```



---
---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.


---
---

### Issues ###

Submit issues to: [EthernetWebServer_SSL_STM32 issues](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/issues)

---

### TO DO

1. Bug Searching and Killing
2. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia
3. Add mDNS features.


### DONE

 1. Add support to **STM32F1,2,3,4,7 boards** with 64K+ Flash.
 2. Add support to **built-in Ethernet LAN8742A** using [STM32Ethernet library](https://github.com/stm32duino/STM32Ethernet), for boards such as Nucleo-144 NUCLEO_F767ZI.
 3. Add support to **Ethernet W5x00**, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`Ethernet2`](https://github.com/khoih-prog/Ethernet2), [`Ethernet3`](https://github.com/sstaub/Ethernet3) or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
 4. Add support to Ethernet **ENC28J60**, using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library 
 5. Add support to all STM32 boards (**STM32F/L/H/G/WB/MP1**) with 32K+ Flash.
 6. Add support to PROGMEM-related commands, such as sendContent_P() and send_P()
 7. Add TLS/SSL Client support to all STM32 boards (**STM32F/L/H/G/WB/MP1**) with 32K+ Flash.
 8. Add **High-level HTTP (GET, POST, PUT, PATCH, DELETE) and WebSocket Client**
 9. Add support to **Ethernet LAN8720** using [STM32Ethernet library](https://github.com/stm32duino/STM32Ethernet), for boards such as **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG), Discovery (DISCO_F746NG)** and **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**
10. Reduce usage of Arduino String with std::string
11. Optimize library code and examples by using **reference-passing instead of value-passing**.
12. Fix authenticate issue and compiler warnings caused by libb64
13. Change licence from `MIT` to `GPLv3`
14. Sync with [SSLClient v1.6.11](https://github.com/OPEnSLab-OSU/SSLClient/releases/tag/v1.6.11)
15. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
16. Rewrite library and add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project to fix `multiple-definitions` linker error
17. Change from `arduino.cc` to `arduino.tips` in examples
18. Add `lib_ldf_mode = chain+` in `platformio.ini`
19. Add support to any custom hardware / software `SPI` for W5x00 using [Ethernet_Generic Library](https://github.com/khoih-prog/Ethernet_Generic)
20. Add support to STM32L5 boards, such as `Nucleo-L552ZE-Q`


---
---


### Contributions and Thanks

1. Based on and modified from [Ivan Grokhotkov's ESP8266WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)
2. [OPEnSLab-OSU](https://github.com/PEnSLab-OSU) for [OPEnSLab-OSU's SSLClient](https://github.com/OPEnSLab-OSU/SSLClient)
3. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) to help debug and test.
4. [Adrian McEwen](https://github.com/amcewen) for [HttpClient Library](https://github.com/amcewen/HttpClient) on which the [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient) and this [EthernetWebServer library](https://github.com/khoih-prog/EthernetWebServer) are relied.
5. Thanks to [Marcel Stör](https://github.com/marcelstoer) to report issue [Pull in OPEnSLab-OSU's SSLClient v1.6.11 #17](https://github.com/khoih-prog/EthernetWebServer_SSL/issues/17) which was fixed in v1.4.5

---

<table>
  <tr>
    <td align="center"><a href="https://github.com/igrr"><img src="https://github.com/igrr.png" width="100px;" alt="igrr"/><br /><sub><b>⭐️ Ivan Grokhotkov</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/OPEnSLab-OSU"><img src="https://github.com/OPEnSLab-OSU.png" width="100px;" alt="OPEnSLab-OSU"/><br /><sub><b>⭐️ OPEnSLab-OSU</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/amcewen"><img src="https://github.com/amcewen.png" width="100px;" alt="amcewen"/><br /><sub><b>⭐️ Adrian McEwen</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/marcelstoer"><img src="https://github.com/marcelstoer.png" width="100px;" alt="marcelstoer"/><br /><sub><b>Marcel Stör</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---
---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/blob/main/LICENSE)

---

## Copyright

Copyright (c) 2020- Khoi Hoang


