/****************************************************************************************************************************
  base64.cpp - cpp source to a base64 encoding algorithm implementation

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

#include "base64.h"

/* Simple test program
  #include <stdio.h>
  void main()
  {
    char* in = "amcewen";
    char out[22];

    b64_encode(in, 15, out, 22);
    out[21] = '\0';

    printf(out);
  }
*/

int base64_encode(const unsigned char* aInput, int aInputLen, unsigned char* aOutput, int aOutputLen)
{
  // Work out if we've got enough space to encode the input
  // Every 6 bits of input becomes a byte of output
  if (aOutputLen < (aInputLen * 8) / 6)
  {
    // FIXME Should we return an error here, or just the length
    return (aInputLen * 8) / 6;
  }

  // If we get here we've got enough space to do the encoding

  const char* b64_dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  if (aInputLen == 3)
  {
    aOutput[0] = b64_dictionary[aInput[0] >> 2];
    aOutput[1] = b64_dictionary[(aInput[0] & 0x3) << 4 | (aInput[1] >> 4)];
    aOutput[2] = b64_dictionary[(aInput[1] & 0x0F) << 2 | (aInput[2] >> 6)];
    aOutput[3] = b64_dictionary[aInput[2] & 0x3F];
  }
  else if (aInputLen == 2)
  {
    aOutput[0] = b64_dictionary[aInput[0] >> 2];
    aOutput[1] = b64_dictionary[(aInput[0] & 0x3) << 4 | (aInput[1] >> 4)];
    aOutput[2] = b64_dictionary[(aInput[1] & 0x0F) << 2];
    aOutput[3] = '=';
  }
  else if (aInputLen == 1)
  {
    aOutput[0] = b64_dictionary[aInput[0] >> 2];
    aOutput[1] = b64_dictionary[(aInput[0] & 0x3) << 4];
    aOutput[2] = '=';
    aOutput[3] = '=';
  }
  else
  {
    // Break the input into 3-byte chunks and process each of them
    int i;

    for (i = 0; i < aInputLen / 3; i++)
    {
      base64_encode(&aInput[i * 3], 3, &aOutput[i * 4], 4);
    }

    if (aInputLen % 3 > 0)
    {
      // It doesn't fit neatly into a 3-byte chunk, so process what's left
      base64_encode(&aInput[i * 3], aInputLen % 3, &aOutput[i * 4], aOutputLen - (i * 4));
    }
  }

  return ((aInputLen + 2) / 3) * 4;
}

