/****************************************************************************************************************************
  SinricProFanUS.h - Sinric Pro Library for boards

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
 *****************************************************************************************************************************/

#ifndef _SINRIC_PRO_FANUS_H_
#define _SINRIC_PRO_FANUS_H_

#define FAN_US_MIN_RANGE      1
#define FAN_US_MAX_RANGE      3

#include "SinricProDevice.h"

/**
   @class SinricProFanUS
   @brief Device to control a fan with on / off commands and its speed by a range value
*/
class SinricProFanUS :  public SinricProDevice
{
  public:
    SinricProFanUS(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    {
      return SinricProDevice::getProductType() + String("FAN"); 
    }
    //////
    
    // callback

    /**
       @brief Callback definition for onRangeValue function

       Gets called when device receive a `setRangeValue` reuqest \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   rangeValue  Integer 0..3 for range value device has to be set
       @param[out]  rangeValue  Integer 0..3 returning the current range value
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section SetRangeValueCallback Example-Code
       @snippet callbacks.cpp onRangeValue
     **/
    typedef std::function<bool(const String&, int&)> SetRangeValueCallback;

    /**
       @brief Callback definition for onAdjustRangeValue function

       Gets called when device receive a `adjustRangeValue` reuqest \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   rangeValue  Integer -3..3 delta value for range value have to change
       @param[out]  rangeValue  Integer 3..3 returning the absolute range value
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section AdjustRangeValueCallback Example-Code
       @snippet callbacks.cpp onAdjustRangeValue
     **/
    typedef std::function<bool(const String&, int&)> AdjustRangeValueCallback;

    void onRangeValue(SetRangeValueCallback cb);

    void onAdjustRangeValue(AdjustRangeValueCallback cb);

    // event
    bool sendRangeValueEvent(int rangeValue, String cause = "PHYSICAL_INTERACTION");

    // handle
    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
    
  private:
    SetRangeValueCallback setRangeValueCallback;
    AdjustRangeValueCallback adjustRangeValueCallback;
};

SinricProFanUS::SinricProFanUS(const DeviceId &deviceId) : SinricProDevice(deviceId),
  setRangeValueCallback(nullptr) {}

bool SinricProFanUS::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, 
                                   JsonObject &response_value)
{
  if (deviceId != this->deviceId)
    return false;

  if (SinricProDevice::handleRequest(deviceId, action, request_value, response_value))
    return true;

  bool success = false;
  String actionString = String(action);

  if (actionString == "setRangeValue" && setRangeValueCallback)
  {
    int rangeValue = request_value["rangeValue"] | 0;
    success = setRangeValueCallback(deviceId, rangeValue);
    
    // Mod From v2.5.1
    response_value["rangeValue"] = limitValue(rangeValue, FAN_US_MIN_RANGE, FAN_US_MAX_RANGE);
    //////
    
    return success;
  }

  if (actionString == "adjustRangeValue" && adjustRangeValueCallback)
  {
    int rangeValueDelta = request_value["rangeValueDelta"] | 0;
    success = adjustRangeValueCallback(deviceId, rangeValueDelta);
    
    // Mod From v2.5.1
    response_value["rangeValue"] = limitValue(rangeValueDelta, FAN_US_MIN_RANGE, FAN_US_MAX_RANGE);
    //////
    
    return success;
  }

  return success;
}

/**
   @brief Set callback function for `setRangeValue` request

   @param cb Function pointer to a `SetRangeValueCallback` function
   @see SetRangeValueCallback
*/
void SinricProFanUS::onRangeValue(SetRangeValueCallback cb)
{
  setRangeValueCallback = cb;
}

/**
   @brief Set callback function for `adjustRangeValue` request

   @param cb Function pointer to a `AdjustRangeValueCallback` function
   @see AdjustRangeValueCallback
*/
void SinricProFanUS::onAdjustRangeValue(AdjustRangeValueCallback cb)
{
  adjustRangeValueCallback = cb;
}

/**
   @brief Send `rangeValue` event to report curent rangeValue to SinricPro server

   @param   rangeValue  Value between 0..3
   @param   cause       (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return  the success of sending the even
   @retval  true        event has been sent successfully
   @retval  false       event has not been sent, maybe you sent to much events in a short distance of time
*/
bool SinricProFanUS::sendRangeValueEvent(int rangeValue, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setRangeValue", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["rangeValue"] = rangeValue;
  return sendEvent(eventMessage);
}

#endif    //_SINRIC_PRO_FANUS_H_

