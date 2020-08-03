/****************************************************************************************************************************
  SinricProQueue.h - Sinric Pro Library for boards

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
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera.
 *****************************************************************************************************************************/

#ifndef __SINRICPRO_QUEUE_H__
#define __SINRICPRO_QUEUE_H__

#include "extralib/QueueList/QueueList.h"


typedef enum
{
  IF_UNKNOWN    = 0,
  IF_WEBSOCKET  = 1,
  IF_UDP        = 2
} interface_t;

// KH
class SinricProMessage
{
  public:
    SinricProMessage(interface_t interface, const char* message) : _interface(interface)
    {
      _message = String(message);
    };

    ~SinricProMessage()
    {
    };

    const char* getMessage()
    {
      return _message.c_str();
    };

    interface_t getInterface()
    {
      return _interface;
    };

  private:
    interface_t _interface;
    String _message;
};

typedef QueueList<SinricProMessage*> SinricProQueue_t;

#endif    //__SINRICPRO_QUEUE_H__
