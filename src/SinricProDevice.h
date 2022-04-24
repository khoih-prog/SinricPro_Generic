/*********************************************************************************************************************************
  SinricProDevice.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_DEVICE_H_
#define _SINRIC_PRO_DEVICE_H_

#include "SinricProDeviceInterface.h"
#include "LeakyBucket.h"
#include "SinricProId.h"

#include <map>

/**
   @class SinricProDevice
   @brief Base class for all device types

   Supporting base functions which needed by all device types to work with SinricProClass \n
   Implements basic on/off functions like onPowerState and sendPowerStateEvent
 **/
class SinricProDevice : public SinricProDeviceInterface
{
  public:
    SinricProDevice(const DeviceId &deviceId);
    virtual ~SinricProDevice();
    virtual DeviceId getDeviceId();
    // From v2.5.1
    virtual String getProductType();
    //////
    virtual void begin(SinricProInterface* eventSender);

    // callback definitions
    /**
       @brief Callback definition for onPowerState function

       Gets called when device receive a `setPowerState` reuqest \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   state       `true` = device is requested to turn on \n `false` = device is requested to turn off
       @param[out]  state       `true` = device has been turned on \n `false` = device has been turned off
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section PowerStateCallback Example-Code
       @snippet callbacks.cpp onPowerState
     **/
    typedef std::function<bool(const String&, bool&)> PowerStateCallback;

    // standard request handler
    virtual bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value);

    // standard Callbacks
    virtual void onPowerState(PowerStateCallback cb);

    // standard events
    bool sendPowerStateEvent(bool state, String cause = "PHYSICAL_INTERACTION");

  protected:
    virtual bool sendEvent(JsonDocument& event);
    virtual DynamicJsonDocument prepareEvent(const DeviceId &deviceId, const char* action, const char* cause);
    unsigned long getTimestamp();
    DeviceId deviceId;
    PowerStateCallback powerStateCallback;
    // From v2.5.1
    template <typename T> T limitValue(T value, T minValue, T maxValue);
    //////
    
  private:
    SinricProInterface* eventSender;
    std::map<String, LeakyBucket_t> eventFilter;
};

SinricProDevice::SinricProDevice(const DeviceId &deviceId) : 
  deviceId(deviceId),
  powerStateCallback(nullptr),
  eventSender(nullptr)
{}

SinricProDevice::~SinricProDevice()
{}

void SinricProDevice::begin(SinricProInterface* eventSender)
{
  this->eventSender = eventSender;
}

DeviceId SinricProDevice::getDeviceId()
{
  return deviceId;
}

bool SinricProDevice::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, 
                                    JsonObject &response_value)
{
  if (deviceId != this->deviceId)
    return false;

  SRP_LOGDEBUG("SinricProDevice::handleRequest()");
  bool success = false;
  String actionString = String(action);

  if (actionString == "setPowerState" && powerStateCallback)
  {
    bool powerState = request_value["state"] == "On" ? true : false;
    success = powerStateCallback(deviceId, powerState);
    response_value["state"] = powerState ? "On" : "Off";
    return success;
  }
  
  return success;
}

DynamicJsonDocument SinricProDevice::prepareEvent(const DeviceId &deviceId, const char* action, const char* cause)
{
  if (eventSender)
    return eventSender->prepareEvent(deviceId, action, cause);

  SRP_LOGDEBUG3("SinricProDevice:prepareEvent(): Not configured correctly Device =", deviceId.toString(), ". Ignored event =", action);
  
  return DynamicJsonDocument(1024);
}


bool SinricProDevice::sendEvent(JsonDocument& event)
{
  if (!eventSender) 
    return false;
    
  if (!eventSender->isConnected()) 
  {
    SRP_LOGDEBUG("SinricProDevice:sendEvent: Can't send Event. No connection to SinricPro server.");
    return false;
  }
  
  String eventName = event["payload"]["action"] | ""; // get event name

  LeakyBucket_t bucket; // leaky bucket algorithm is used to prevent flooding the server

  // get leaky bucket for event from eventFilter
  if (eventFilter.find(eventName) == eventFilter.end()) 
  {  
    // if there is no bucket ...
    eventFilter[eventName] = bucket;                       // ...add a new bucket
  }
  else
  {
    bucket = eventFilter[eventName];                       // else get bucket
  }

  if (bucket.addDrop())
  {
    // if we can add a new drop
    eventSender->sendMessage(event);                       // send event
    eventFilter[eventName] = bucket;                       // update bucket on eventFilter
    return true;
  }

  eventFilter[eventName] = bucket;                         // update bucket on eventFilter
  return false;
}

unsigned long SinricProDevice::getTimestamp()
{
  if (eventSender) return eventSender->getTimestamp();
  return 0;
}

template <typename T> T SinricProDevice::limitValue(T value, T minValue, T maxValue)
{
  T newValue = value;
  
  if (value > maxValue) 
    newValue = maxValue;
    
  if (value < minValue) 
    newValue = minValue;
    
  return newValue;
}

/**
   @brief Set callback function for `powerState` request

   @param cb Function pointer to a `PowerStateCallback` function
   @return void
   @see PowerStateCallback
 **/
void SinricProDevice::onPowerState(PowerStateCallback cb)
{
  powerStateCallback = cb;
}

/**
   @brief Send `setPowerState` event to SinricPro Server indicating actual power state

   @param state   `true` = device turned on \n `false` = device turned off
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProDevice::sendPowerStateEvent(bool state, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setPowerState", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["state"] = state ? "On" : "Off";
  return sendEvent(eventMessage);
}

// From v2.5.1
String SinricProDevice::getProductType()  
{
  return String("sinric.device.type."); 
}
//////

#endif    //_SINRIC_PRO_DEVICE_H_
