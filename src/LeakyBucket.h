/*********************************************************************************************************************************
  LeakyBucket.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as SAMD21, SAMD51, Adafruit's nRF52 boards, Teensy, SAM DUE, STM32, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license 

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version: 2.8.5
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
  2.6.1   K Hoang      15/08/2020 Sync with SinricPro v2.6.1: add AirQualitySensor, Camera Class.
  2.7.0   K Hoang      06/10/2020 Sync with SinricPro v2.7.0: Added AppKey, AppSecret and DeviceId classes and RTT function.
  2.7.4   K Hoang      12/11/2020 Sync with SinricPro v2.7.4. Add WIO Terminal support and examples
  2.8.0   K Hoang      10/12/2020 Sync with SinricPro v2.8.0. Add examples. Use std::queue instead of QueueList. SSL Option.
  2.8.1   K Hoang      02/06/2021 Add support to RP2040 using Arduino-mbed or arduino-pico core with WiFiNINA or Ethernet
  2.8.2   K Hoang      20/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720A)
  2.8.3   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  2.8.4   K Hoang      01/12/2021 Auto detect ESP32 core for LittleFS. Fix bug in examples for WT32_ETH01
  2.8.5   K Hoang      23/04/2022 Use Ethernet_Generic library as default. Add support to Portenta_H7, etc.
 **********************************************************************************************************************************/

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
        SRP_LOGERROR("WARNING: You sent too many Events in a short period of time!");
        SRP_LOGERROR("Please check your code and send Events only if device has changed!");
        once = true;
      }
      // KH
      SRP_LOGERROR2("Events are blocked for ", DROP_OUT_TIME - (actualMillis - lastDrop) / 1000, " secs" );
      
      lastWarning = actualMillis;
    }
  }
  return false;
}

void LeakyBucket_t::leak()
{
  // leak bucket...
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
