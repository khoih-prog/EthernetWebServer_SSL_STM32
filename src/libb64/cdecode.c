/****************************************************************************************************************************
  cdecoder.c - c source to a base64 decoding algorithm implementation

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

#include "cdecode.h"

int base64_decode_value(int value_in)
{
  static const char decoding[] =
  {
    62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1, -1, 0, 1, 2,
    3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1,
    -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
    47, 48, 49, 50, 51
  };

  static const char decoding_size = sizeof(decoding);
  value_in -= 43;

  if (value_in < 0 || value_in > decoding_size)
    return -1;

  return decoding[(int)value_in];
}

void base64_init_decodestate(base64_decodestate* state_in)
{
  state_in->step = step_a;
  state_in->plainchar = 0;
}

int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state_in)
{
  const char* codechar = code_in;
  char* plainchar = plaintext_out;
  int fragment;

  *plainchar = state_in->plainchar;

  switch (state_in->step)
  {
      while (1)
      {
      case step_a:
        do
        {
          if (codechar == code_in + length_in)
          {
            state_in->step = step_a;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }

          fragment = base64_decode_value(*codechar++);
        } while (fragment < 0);

        *plainchar    = (fragment & 0x03f) << 2;

      // fall through

      case step_b:
        do
        {
          if (codechar == code_in + length_in)
          {
            state_in->step = step_b;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }

          fragment = base64_decode_value(*codechar++);
        } while (fragment < 0);

        *plainchar++ |= (fragment & 0x030) >> 4;
        *plainchar    = (fragment & 0x00f) << 4;

      // fall through

      case step_c:
        do
        {
          if (codechar == code_in + length_in)
          {
            state_in->step = step_c;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }

          fragment = base64_decode_value(*codechar++);
        } while (fragment < 0);

        *plainchar++ |= (fragment & 0x03c) >> 2;
        *plainchar    = (fragment & 0x003) << 6;

      // fall through

      case step_d:
        do
        {
          if (codechar == code_in + length_in)
          {
            state_in->step = step_d;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }

          fragment = base64_decode_value(*codechar++);
        } while (fragment < 0);

        *plainchar++   |= (fragment & 0x03f);

        // fall through
      }
  }

  /* control should not reach here */
  return plainchar - plaintext_out;
}

int base64_decode_chars(const char* code_in, const int length_in, char* plaintext_out)
{

  base64_decodestate _state;
  base64_init_decodestate(&_state);
  int len = base64_decode_block(code_in, length_in, plaintext_out, &_state);

  if (len > 0)
    plaintext_out[len] = 0;

  return len;
}
