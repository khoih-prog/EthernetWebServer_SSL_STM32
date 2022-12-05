## EthernetWebServer_SSL_STM32 Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer_SSL_STM32.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer_SSL_STM32.svg)](http://github.com/khoih-prog/EthernetWebServer_SSL_STM32/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.6.0](#releases-v160)
  * [Releases v1.5.1](#releases-v151)
  * [Releases v1.5.0](#releases-v150)
  * [Releases v1.4.5](#releases-v145)
  * [Releases v1.4.4](#releases-v144)
  * [Releases v1.4.3](#releases-v143)
  * [Releases v1.4.2](#releases-v142)
  * [Releases v1.4.1](#releases-v141)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Releases v1.3.1](#releases-v131)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.1](#releases-v121)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Releases v1.1.2](#releases-v112)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)

---
---

## Changelog

### Releases v1.6.0

1. Add support to any custom hardware / software `SPI` for W5x00 using [Ethernet_Generic Library](https://github.com/khoih-prog/Ethernet_Generic)
2. Add support to STM32L5 boards, such as `Nucleo-L552ZE-Q`

### Releases v1.5.1

1. Change from `arduino.cc` to `arduino.tips` in HTTP examples
2. Add `lib_ldf_mode = chain+` in `platformio.ini`

### Releases v1.5.0

1. Use new [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
2. Rewrite all the examples to support new features
3. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project

### Releases v1.4.5

1. Sync with [SSLClient v1.6.11](https://github.com/OPEnSLab-OSU/SSLClient/releases/tag/v1.6.11). Check [Pull in OPEnSLab-OSU's SSLClient v1.6.11 #17](https://github.com/khoih-prog/EthernetWebServer_SSL/issues/17)
2. Add example [AWS_IoT](examples/AWS_IoT)


### Releases v1.4.4

1. Change license from `MIT` to `GPLv3`. Check [Licensing of SSLClient #16](https://github.com/khoih-prog/EthernetWebServer_SSL/issues/16)

### Releases v1.4.3

1. Fix decoding error bug when using special `&` in data fields. Check [Decoding Error. two times called urlDecode in Parsing-impl.h. #17](https://github.com/khoih-prog/WiFiWebServer/issues/17)

### Releases v1.4.2

1. Fix libb64 `fallthrough` compile warnings

### Releases v1.4.1

1. Fix wrong http status header bug. Check [fix for wrong http status header #42](https://github.com/khoih-prog/EthernetWebServer/pull/42)
2. Fix authenticate issue caused by libb64


### Major Releases v1.4.0

1. Reduce usage of Arduino String with std::string
2. Optimize library code and examples by using **reference-passing instead of value-passing**.
3. Fix bug related to String in library and examples
4. Update `Packages' Patches`

### Releases v1.3.1

1. Change option for **PIO** `lib_compat_mode` from default `soft` to `strict` to minimize compile error in cross-platform
2. Update `Packages' Patches`

### Releases v1.3.0

1. Add support to **LAN8720** Ethernet for many **STM32F4** (F407xx, NUCLEO_F429ZI) and **STM32F7** (DISCO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG) boards.
2. Add LAN8720 examples
3. Add Packages' Patches for STM32 to use LAN8720 with STM32Ethernet and LwIP libraries

### Releases v1.2.1

1. Clean-up all compiler warnings possible.
2. Add Table of Contents

### Major Releases v1.2.0

1. Add high-level **HTTP and WebSockets Client** by merging [ArduinoHttpClient Library](https://github.com/arduino-libraries/ArduinoHttpClient)
2. Add many more examples for HTTP and WebSockets Client.
3. Add Version String.

### Releases v1.1.2

1. Add SSL debug feature.
2. Enhance examples.

### Releases v1.1.1

1. Permit sites with "Chain could not be linked to a trust anchor" such as mqtt.thingstream.io.
2. Add example MQTTS_ThingStream to demonstrate new feature

### Releases v1.1.0

1. Initial coding for **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running LAN8742A, W5x00 or ENC28J60 shields** using SSL.
2. Supporting Built-in LAN8742A using STM32Ethernet library.
3. Supporting W5x00 using Ethernet, EthernetLarge, Ethernet2 and Ethernet3 libraries
4. Supporting ENC28J60 using EthernetENC and UIPEthernet libraries


