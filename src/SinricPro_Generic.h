/****************************************************************************************************************************
  SinricPro_Generic.h - Sinric Pro Library for boards
  
  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 
  Version Modified By   Date      Comments
 ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
 *****************************************************************************************************************************/

#ifndef SINRIC_PRO_GENERIC_H_
#define SINRIC_PRO_GENERIC_H_

#if 1   //!defined(ARDUINO_SAMD_NANO_33_IOT)

  #ifdef min
    #warning undef min
    #undef min
    #define min(a,b) ((a) < (b) ? (a) : (b))
  #endif

  #ifdef max
    #warning undef max
    #undef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
  #endif
  
#endif

#include <vector>

void __throw_bad_alloc()
{
  Serial.println("Unable to allocate memory");
}

void __throw_length_error( char const*e )
{
  Serial.print("Length Error :");
  Serial.println(e);
}

// KH, Don't need for Teensy from v1.5.3
#if 0 //defined(TEENSYDUINO)
namespace std
{
  //To avoid Teensy linker issue wth STL library
  unsigned __exidx_start;
  unsigned __exidx_end;

  // This is defined so that calling a std::function<void()> can compile when
  // size optimization is enabled.
  __attribute__((weak))
  void __throw_bad_function_call()
  {
   Serial.println("Library Exception");
   while (true) yield();
  }
}
#endif

#include <WebSockets_Generic.h>

#include <ArduinoJson.h>
#include "SinricPro.h"


#endif    //SINRIC_PRO_GENERIC_H_
