/*********************************************************************************************************************************
  SinricProBlinds.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_BLINDS_H_
#define _SINRIC_PRO_BLINDS_H_

#include "SinricProDevice.h"

#define BLINDS_MIN_RANGE      0
#define BLINDS_MAX_RANGE      100

/**
   @class SinricProBlinds
   @brief Device to control interior blinds

   Supporting
 * * On / Off
 * * Position (0..100)
 * * open / close
 **/
class SinricProBlinds :  public SinricProDevice
{
  public:
    SinricProBlinds(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    { 
      return SinricProDevice::getProductType() + String("BLIND"); 
    }
    //////

    /**
       @brief Callback definition for onSetPosition function

       Gets called when device receive a `setPosition` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   position    Absolute integer value with desired blinds position
       @param[out]  position    Absolute integer value with actual blinds position
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section SetPositionCallback Example-Code
       @snippet callbacks.cpp onSetPosition
     **/
    typedef std::function<bool(const String&, int&)> SetPositionCallback;

    /**
       @brief Callback definition for onAdjustPosition function

       Gets called when device receive a `setPowerState` request \n
       @param[in]   deviceId        String which contains the ID of device
       @param[in]   positionDelta   Relative integer value the device should change the position of the blinds about (-100..+100)
       @param[out]  positionDelta   Absolute integer value with the new blinds position (0..100)
       @return      the success of the request
       @retval      true            request handled properly
       @retval      false           request was not handled properly because of some error

       @section AdjustPositionCallback Example-Code
       @snippet callbacks.cpp onAdjustPosition
     **/
    typedef std::function<bool(const String&, int&)> AdjustPositionCallback;

    void onSetPosition(SetPositionCallback cb);
    void onAdjustPosition(AdjustPositionCallback cb);

    bool sendPositionEvent(int position, String cause = "PHYSICAL_INTERACTION");

    // handle
    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
    
  private:
    SetPositionCallback setPositionCallback;
    AdjustPositionCallback adjustPositionCallback;
};

SinricProBlinds::SinricProBlinds(const DeviceId &deviceId) : SinricProDevice(deviceId),
  setPositionCallback(nullptr),
  adjustPositionCallback(nullptr)
{
}

bool SinricProBlinds::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value)
{
  if (deviceId != this->deviceId)
    return false;

  if (SinricProDevice::handleRequest(deviceId, action, request_value, response_value))
    return true;

  bool success = false;
  String actionString = String(action);

  if (actionString == "setRangeValue" && setPositionCallback)
  {
    int position = request_value["rangeValue"] | 0;
    success = setPositionCallback(deviceId, position);
    // Mod From v2.5.1
    response_value["rangeValue"] = limitValue(position, BLINDS_MIN_RANGE, BLINDS_MAX_RANGE);
    return success;
  }

  if (actionString == "adjustRangeValue" && adjustPositionCallback)
  {
    int positionDelta = request_value["rangeValueDelta"] | 0;
    success = adjustPositionCallback(deviceId, positionDelta);
    // Mod From v2.5.1
    response_value["rangeValue"] = limitValue(positionDelta, BLINDS_MIN_RANGE, BLINDS_MAX_RANGE);
    return success;
  }

  return success;
}

/**
   @brief Set callback function for `setPosition` request

   @param cb Function pointer to a `SetPositionCallback` function
   @return void
   @see SetPositionCallback
 **/
void SinricProBlinds::onSetPosition(SetPositionCallback cb)
{
  setPositionCallback = cb;
}

/**
   @brief Set callback function for `adjustPosition` request

   @param cb Function pointer to a `AdjustPositionCallback` function
   @return void
   @see AdjustPositionCallback
 **/
void SinricProBlinds::onAdjustPosition(AdjustPositionCallback cb)
{
  adjustPositionCallback = cb;
}

/**
   @brief Send `setPosition` event to update actual position on SinricPro Server

   @param position `0` = blinds are closed \n `100` = blinds are open
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval 0..100 actual blinds position
 **/
bool SinricProBlinds::sendPositionEvent(int position, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setRangeValue", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["rangeValue"] = position;
  return sendEvent(eventMessage);
}

#endif    //_SINRIC_PRO_BLINDS_H_

