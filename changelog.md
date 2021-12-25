## EthernetWebServer_SSL_STM32

[![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_SSL_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_SSL_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/EthernetWebServer_SSL_STM32.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/EthernetWebServer_SSL_STM32/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/EthernetWebServer_SSL_STM32.svg)](http://github.com/khoih-prog/EthernetWebServer_SSL_STM32/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
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


