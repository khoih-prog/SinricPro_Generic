/****************************************************************************************************************************
  SinricProGarageDoor.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_GARAGEDOOR_H_
#define _SINRIC_PRO_GARAGEDOOR_H_

#include "SinricProDevice.h"

/**
   @class SinricProGarageDoor
   @brief Device to control a garage door

   Supporting
 * * open / close
 **/
class SinricProGarageDoor :  public SinricProDevice
{
  public:
    SinricProGarageDoor(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    {
      return SinricProDevice::getProductType() + String("GARAGE_DOOR"); 
    }
    //////

    /**
       @brief Callback definition for onDoorState function

       Gets called when device receive a `open` or `close` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   doorState   `false` = open, device is requested to open the garage door \n`true` = close, device is requested to close the garage door
       @param[out]  doorState   bool with actual state `false` = open, `true` = closed
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section DoorStateCallback Example-Code
       @snippet callbacks.cpp onDoorState
     **/
    typedef std::function<bool(const String&, bool&)> DoorStateCallback;

    void onDoorState(DoorStateCallback cb);
    void onPowerState() = delete;  // SinricProGarageDoor has no powerState

    // event
    bool sendDoorStateEvent(bool mode, String cause = "PHYSICAL_INTERACTION");
    bool sendPowerStateEvent() = delete; // SinricProGarageDoor has no powerState

    // handle
    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
    
  private:
    DoorStateCallback doorStateCallback;
};

SinricProGarageDoor::SinricProGarageDoor(const DeviceId &deviceId) : SinricProDevice(deviceId),
  doorStateCallback(nullptr)
{
}

bool SinricProGarageDoor::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, 
                                        JsonObject &response_value)
{
  if (deviceId != this->deviceId)
    return false;

  if (SinricProDevice::handleRequest(deviceId, action, request_value, response_value))
    return true;

  bool success = false;
  String actionString = String(action);

  if (actionString == "setMode" && doorStateCallback)
  {
    String modeStr = request_value["mode"] | "";
    bool mode;

    if (modeStr == "Open")
      mode = false;

    if (modeStr == "Close")
      mode = true;

    success = doorStateCallback(deviceId, mode);

    if (mode == false)
      modeStr = "Open";

    if (mode == true)
      modeStr = "Close";

    response_value["mode"] = modeStr;
    return success;
  }
  return success;
}

/**
   @brief Set callback function for `onDoorState` request

   @param cb Function pointer to a `onDoorState` function
   @return void
   @see DoorStateCallback
 **/
void SinricProGarageDoor::onDoorState(DoorStateCallback cb)
{
  doorStateCallback = cb;
}

/**
   @brief Send `DoorState` event to update actual door state on SinricPro Server

   @param state   bool `true` = close \n `false` = open
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProGarageDoor::sendDoorStateEvent(bool state, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setMode", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  state ? event_value["mode"] = "Close" : event_value["mode"] = "Open";
  return sendEvent(eventMessage);
}

#endif    //_SINRIC_PRO_GARAGEDOOR_H_

