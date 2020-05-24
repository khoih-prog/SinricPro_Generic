/****************************************************************************************************************************
  SinricProMessageID.h - Sinric Pro Library for boards

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

#ifndef __MESSAGEID_H__
#define __MESSAGEID_H__

class MessageID
{
  public:
    MessageID();
    const String& getID()
    {
      return _id;
    }
  private:
    String _id;
};

MessageID::MessageID()
{
  _id = "";

  for (byte i = 0; i < 16; i++)
  {
    byte rnd = random(255);

    if (i == 4)
      _id += "-";

    if (i == 6)
    {
      _id += "-";  // 0100xxxx to set version 4
      rnd = 0x40 | (0x0F & rnd);
    }

    if (i == 8)
    {
      _id += "-";  // 10xxxxxx to set reserved bits
      rnd = 0x80 | (0x3F & rnd);
    }

    if (i == 10)
      _id += "-";

    byte high_nibble = rnd >> 4;
    byte low_nibble = rnd & 0x0f;
    _id += "0123456789abcdef"[high_nibble];
    _id += "0123456789abcdef"[low_nibble];
  }
}

#endif // __MESSAGEID_H__
