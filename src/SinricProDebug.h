/*********************************************************************************************************************************
  SinricProDebug.h - Sinric Pro Library for boards
  
  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.5.1

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
 **********************************************************************************************************************************/

#ifndef __SINRICPRODEBUG_H__
#define __SINRICPRODEBUG_H__

// KH add from v2.5.1
#include <stdio.h>

#ifdef SRP_DEBUG_PORT
#define SRP_DEBUG_OUTPUT SRP_DEBUG_PORT
#else
#define SRP_DEBUG_OUTPUT Serial
#endif

// Change _SRP_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _SRP_LOGLEVEL_
#define _SRP_LOGLEVEL_       0
#endif

//////

#define SRP_LOGERROR(x)        if(_SRP_LOGLEVEL_>0) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.println(x); }
#define SRP_LOGERROR1(x,y)     if(_SRP_LOGLEVEL_>0) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(y); }
#define SRP_LOGERROR2(x,y,z)   if(_SRP_LOGLEVEL_>0) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(z); }
#define SRP_LOGERROR3(x,y,z,w) if(_SRP_LOGLEVEL_>0) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(z); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(w); }

//////

#define SRP_LOGWARN(x)         if(_SRP_LOGLEVEL_>1) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.println(x); }
#define SRP_LOGWARN1(x,y)      if(_SRP_LOGLEVEL_>1) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(y); }
#define SRP_LOGWARN2(x,y,z)    if(_SRP_LOGLEVEL_>1) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(z); }
#define SRP_LOGWARN3(x,y,z,w)    if(_SRP_LOGLEVEL_>1) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(z); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(w); }

//////

#define SRP_LOGINFO(x)         if(_SRP_LOGLEVEL_>2) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.println(x); }
#define SRP_LOGINFO1(x,y)      if(_SRP_LOGLEVEL_>2) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(y); }
#define SRP_LOGINFO2(x,y,z)    if(_SRP_LOGLEVEL_>2) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(z); }
#define SRP_LOGINFO3(x,y,z,w)  if(_SRP_LOGLEVEL_>2) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(z); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(w); }

//////

#define SRP_LOGDEBUG(x)        if(_SRP_LOGLEVEL_>3) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.println(x); }
#define SRP_LOGDEBUG0(x)       if(_SRP_LOGLEVEL_>3) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); }
#define SRP_LOGDEBUG1(x,y)     if(_SRP_LOGLEVEL_>3) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(y); }
#define SRP_LOGDEBUG2(x,y,z)   if(_SRP_LOGLEVEL_>3) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(z); }
#define SRP_LOGDEBUG3(x,y,z,w) if(_SRP_LOGLEVEL_>3) { SRP_DEBUG_OUTPUT.print("[SRP] "); SRP_DEBUG_OUTPUT.print(x); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(y); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.print(z); SRP_DEBUG_OUTPUT.print(" "); SRP_DEBUG_OUTPUT.println(w); }

//////

#ifndef NODEBUG_SINRIC
#ifdef SRP_DEBUG_OUTPUT
#define DEBUG_SINRIC(...) SRP_DEBUG_OUTPUT.printf( __VA_ARGS__ )
#else
//#define DEBUG_WEBSOCKETS(...) os_printf( __VA_ARGS__ )
#endif
#endif


#ifndef DEBUG_SINRIC
#define DEBUG_SINRIC(...)
#define NODEBUG_SINRIC
#endif


#endif    // __SINRICPRODEBUG_H__
