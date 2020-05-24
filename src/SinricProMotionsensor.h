/****************************************************************************************************************************
  SinricProMotionSensor.h - Sinric Pro Library for boards

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

#ifndef _SINRICMOTIONSENSOR_H_
#define _SINRICMOTIONSENSOR_H_

#include "SinricProDevice.h"

/**
   @class SinricProMotionsensor
   @brief Device to report motion detection events
*/
class SinricProMotionsensor :  public SinricProDevice
{
  public:
    SinricProMotionsensor(const char* deviceId, unsigned long eventWaitTime = 100);

    // event
    bool sendMotionEvent(bool detected, String cause = "PHYSICAL_INTERACTION");
  private:
};

SinricProMotionsensor::SinricProMotionsensor(const char* deviceId, unsigned long eventWaitTime) : SinricProDevice(deviceId, eventWaitTime) {}

/**
   @brief Sending motion detection state to SinricPro server

   @param   state         `true` if motion has been detected \n 'false' if no motion has been detected
   @param   cause         (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return  the success of sending the event
   @retval  true          event has been sent successfully
   @retval  false         event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProMotionsensor::sendMotionEvent(bool state, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "motion", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["state"] = state ? "detected" : "notDetected";
  return sendEvent(eventMessage);
}

#endif    //_SINRICMOTIONSENSOR_H_

