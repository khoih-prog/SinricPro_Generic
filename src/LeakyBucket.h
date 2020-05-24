/****************************************************************************************************************************
  LeakyBucket.h - Sinric Pro Library for boards

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

#ifndef _LEAKY_BUCKET_H_
#define _LEAKY_BUCKET_H_

class LeakyBucket_t
{
  public:
    LeakyBucket_t() : dropsInBucket(0), lastDrop(-DROP_IN_TIME), once(false) {}
    bool addDrop();
  private:
    void leak();
    int dropsInBucket;
    unsigned long lastDrop;
    bool once;
    unsigned long lastWarning;
};

bool LeakyBucket_t::addDrop()
{
  leak();
  unsigned long actualMillis = millis();

  if (dropsInBucket < BUCKET_SIZE && actualMillis - lastDrop > dropsInBucket + DROP_IN_TIME)
  {
    // new drop can be placed into bucket?
    dropsInBucket++;                  // place drop in bucket
    lastDrop = actualMillis;          // store last drop time
    return true;
  }

  if (dropsInBucket >= BUCKET_SIZE)
  {
    if (actualMillis - lastWarning > 1000)
    {
      if (once == false)
      {
        // Print a warning when bucket is full
        // KH
        Serial.println("[SinricPro]: WARNING: YOU SENT TOO MUCH EVENTS IN A SHORT PERIOD OF TIME!\r\n - PLEASE CHECK YOUR CODE AND SEND EVENTS ONLY IF DEVICE STATE HAS CHANGED!");
        once = true;
      }
      // KH
      Serial.print("[SinricPro]: EVENTS ARE BLOCKED FOR SECS");
      Serial.println((DROP_OUT_TIME - (actualMillis - lastDrop)) / 1000);
      lastWarning = actualMillis;
    }
  }
  return false;
}

void LeakyBucket_t::leak()
{
  // leack bucket...
  unsigned long actualMillis = millis();
  int drops_to_leak = (actualMillis - lastDrop) / DROP_OUT_TIME;

  if (drops_to_leak > 0)
  {
    if (dropsInBucket <= drops_to_leak)
    {
      dropsInBucket = 0;
    }
    else
    {
      dropsInBucket -= drops_to_leak;
    }
  }
}

#endif    //_LEAKY_BUCKET_H_
