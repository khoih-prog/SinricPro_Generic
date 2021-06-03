/****************************************************************************************************************************
  SinricProDoorbell.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.8.1

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

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
 *****************************************************************************************************************************/

#ifndef _SINRIC_PRO_DOORBELL_H_
#define _SINRIC_PRO_DOORBELL_H_

#include "SinricProDevice.h"

/**
   @class SinricProDoorbell
   @brief Device to report doorbell events
 *  */
class SinricProDoorbell :  public SinricProDevice 
{
  public:
    SinricProDoorbell(const DeviceId &deviceId);
    
    // From v2.5.1
    virtual String getProductType() 
    { 
      return SinricProDevice::getProductType() + String("DOORBELL"); 
    }
    //////
    
    // event
    bool sendDoorbellEvent(String cause = "PHYSICAL_INTERACTION");
    
  private:
};

SinricProDoorbell::SinricProDoorbell(const DeviceId &deviceId) : SinricProDevice(deviceId) {}

/**
   @brief Send Doorbell event to SinricPro Server indicating someone pressed the doorbell button

   @param   cause         (optional) Reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return  the success of sending the event
   @retval  true          event has been sent successfully
   @retval  false         event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProDoorbell::sendDoorbellEvent(String cause) 
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "DoorbellPress", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["state"] = "pressed";
  return sendEvent(eventMessage);
}

#endif    //_SINRIC_PRO_DOORBELL_H_
