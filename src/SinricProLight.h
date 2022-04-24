/****************************************************************************************************************************
  SinricProLight.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_LIGHT_H_
#define _SINRIC_PRO_LIGHT_H_

#include "SinricProDevice.h"

#define LIGHT_MIN_BRIGHTNESS_LEVEL      0
#define LIGHT_MAX_BRIGHTNESS_LEVEL      100

/**
   @class SinricProLight
   @brief Device to control a light

   Supporting
 * * On / Off
 * * Brightness (0..100)
 * * Color (RGB)
 * * Color temperature
 **/
class SinricProLight :  public SinricProDevice
{
  public:
    SinricProLight(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    {
      return SinricProDevice::getProductType() + String("LIGHT"); 
    }
    //////
    
    // callback

    /**
       @brief Callback definition for onBrightness function

       Gets called when device receive a `setBrightness` request \n
       @param[in]   deviceId      String which contains the ID of device
       @param[in]   brightness    Absolute integer value the device should set its brightness to
       @param[out]  brightness    Absolute integer value with new brightness the device is set to
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section BrightnessCallback Example-Code
       @snippet callbacks.cpp onBrightness
     **/
    typedef std::function<bool(const String&, int&)> BrightnessCallback;

    /**
       @brief Callback definition for onAdjustBrightness function

       Gets called when device receive a `adjustBrightness` request \n
       @param[in]   deviceId      String which contains the ID of device
       @param[in]   brightness    Relative integer value the device should change the brightness about
       @param[out]  brightness    Absolute integer value with new brightness the device is set to
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section AdjustBrightnessCallback Example-Code
       @snippet callbacks.cpp onAdjustBrightness
     **/
    typedef std::function<bool(const String&, int&)> AdjustBrightnessCallback;

    /**
       @brief Callback definition for onColor function

       Gets called when device receive a `setColor` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   r           Byte value for red
       @param[in]   g           Byte value for green
       @param[in]   b           Byte value for blue
       @param[out]  r           Byte value for red
       @param[out]  g           Byte value for green
       @param[out]  b           Byte value for blue
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section ColorCallback Example-Code
       @snippet callbacks.cpp onColor
     **/
    typedef std::function<bool(const String&, byte&, byte&, byte&)> ColorCallback;

    /**
       @brief Callback definition for onColorTemperature function

       Gets called when device receive a `setColorTemperature` request \n
       @param[in]   deviceId          String which contains the ID of device
       @param[in]   colorTemperature  Integer value with color temperature the device should set to \n `2200` = warm white \n `2700` = soft white \n `4000` = white \n `5500` = daylight white \n `7000` = cool white
       @param[out]  colorTemperature  Integer value with color temperature the device is set to \n `2200` = warm white \n `2700` = soft white \n `4000` = white \n `5500` = daylight white \n `7000` = cool white
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section ColorTemperatureCallback Example-Code
       @snippet callbacks.cpp onColorTemperature
     **/
    typedef std::function<bool(const String&, int&)> ColorTemperatureCallback;

    /**
       @brief Callback definition for onIncreaseColorTemperature function

       Gets called when device receive a `increaseColorTemperature` request \n
       @param[in]   deviceId          String which contains the ID of device
       @param[in]   colorTemperature  Integer value `1` = Device should increase color temperature
       @param[out]  colorTemperature  Integer value return the new color temperarature \n `2200` = warm white \n `2700` = soft white \n `4000` = white \n `5500` = daylight white \n `7000` = cool white
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section IncreaseColorTemperatureCallback Example-Code
       @snippet callbacks.cpp onIncreaseColorTemperature
     **/
    typedef std::function<bool(const String&, int&)> IncreaseColorTemperatureCallback;

    /**
       @brief Callback definition for onDecreaseColorTemperature function

       Gets called when device receive a `decreaseColorTemperature` request \n
       @param[in]   deviceId          String which contains the ID of device
       @param[in]   colorTemperature  Integer value `-1` = Device should decrease color temperature
       @param[out]  colorTemperature  Integer value return the new color temperarature \n `2200` = warm white \n `2700` = soft white \n `4000` = white \n `5500` = daylight white \n `7000` = cool white
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error
       @section DecreaseColorTemperatureCallback Example-Code
       @snippet callbacks.cpp onDecreaseColorTemperature
     **/
    typedef std::function<bool(const String&, int&)> DecreaseColorTemperatureCallback;

    void onBrightness(BrightnessCallback cb);
    void onAdjustBrightness(AdjustBrightnessCallback cb);
    void onColor(ColorCallback cb);
    void onColorTemperature(ColorTemperatureCallback cb);
    void onIncreaseColorTemperature(IncreaseColorTemperatureCallback cb);
    void onDecreaseColorTemperature(DecreaseColorTemperatureCallback cb);

    // event
    bool sendBrightnessEvent(int brightness, String cause = "PHYSICAL_INTERACTION");
    bool sendColorEvent(byte r, byte g, byte b, String cause = "PHYSICAL_INTERACTION");
    bool sendColorTemperatureEvent(int colorTemperature, String cause = "PHYSICAL_INTERACTION");

    // handle
    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
    
  private:
    BrightnessCallback brightnessCallback;
    AdjustBrightnessCallback adjustBrightnessCallback;
    ColorCallback colorCallback;
    ColorTemperatureCallback colorTemperatureCallback;
    IncreaseColorTemperatureCallback increaseColorTemperatureCallback;
    DecreaseColorTemperatureCallback decreaseColorTemperatureCallback;
};

SinricProLight::SinricProLight(const DeviceId &deviceId) : SinricProDevice(deviceId),
  brightnessCallback(nullptr),
  adjustBrightnessCallback(nullptr),
  colorCallback(nullptr),
  colorTemperatureCallback(nullptr),
  increaseColorTemperatureCallback(nullptr),
  decreaseColorTemperatureCallback(nullptr) {}

bool SinricProLight::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, 
                                   JsonObject &response_value)
{
  if (deviceId != this->deviceId)
    return false;

  if (SinricProDevice::handleRequest(deviceId, action, request_value, response_value))
    return true;

  bool success = false;
  String actionString = String(action);

  if (brightnessCallback && actionString == "setBrightness")
  {
    int brightness = request_value["brightness"];
    success = brightnessCallback(deviceId, brightness);
    
    // Mod From v2.5.1
    response_value["brightness"] = limitValue(brightness, LIGHT_MIN_BRIGHTNESS_LEVEL, LIGHT_MAX_BRIGHTNESS_LEVEL);
  }

  if (adjustBrightnessCallback && actionString == "adjustBrightness")
  {
    int brightnessDelta = request_value["brightnessDelta"];
    success = adjustBrightnessCallback(deviceId, brightnessDelta);
    
    // Mod From v2.5.1
    response_value["brightness"] = limitValue(brightnessDelta, LIGHT_MIN_BRIGHTNESS_LEVEL, LIGHT_MAX_BRIGHTNESS_LEVEL);
  }

  if (colorCallback && actionString == "setColor")
  {
    unsigned char r, g, b;
    r = request_value["color"]["r"];
    g = request_value["color"]["g"];
    b = request_value["color"]["b"];
    success = colorCallback(deviceId, r, g, b);
    response_value.createNestedObject("color");
    response_value["color"]["r"] = r;
    response_value["color"]["g"] = g;
    response_value["color"]["b"] = b;
  }

  if (colorTemperatureCallback && actionString == "setColorTemperature")
  {
    int colorTemperature = request_value["colorTemperature"];
    
    success = colorTemperatureCallback(deviceId, colorTemperature);
    response_value["colorTemperature"] = colorTemperature;
  }

  if (increaseColorTemperatureCallback && actionString == "increaseColorTemperature")
  {
    int colorTemperature = 1;
    
    success = increaseColorTemperatureCallback(deviceId, colorTemperature);
    response_value["colorTemperature"] = colorTemperature;
  }

  if (decreaseColorTemperatureCallback && actionString == "decreaseColorTemperature")
  {
    int colorTemperature = -1;
    
    success = decreaseColorTemperatureCallback(deviceId, colorTemperature);
    response_value["colorTemperature"] = colorTemperature;
  }

  return success;
}

/**
   @brief Set callback function for `setBrightness` request

   @param cb Function pointer to a `BrightnessCallback` function
   @return void
   @see BrightnessCallback
 **/
void SinricProLight::onBrightness(BrightnessCallback cb)
{
  brightnessCallback = cb;
}

/**
   @brief Set callback function for `adjustBrightness` request

   @param cb Function pointer to a `AdjustBrightnessCallback` function
   @return void
   @see AdjustBrightnessCallback
 **/
void SinricProLight::onAdjustBrightness(AdjustBrightnessCallback cb)
{
  adjustBrightnessCallback = cb;
}

/**
   @brief Set callback function for `setColor` request

   @param cb Function pointer to a `ColorCallback` function
   @return void
   @see ColorCallback
 **/
void SinricProLight::onColor(ColorCallback cb)
{
  colorCallback = cb;
}

/**
   @brief Set callback function for `setColorTemperature` request

   @param cb Function pointer to a `ColorTemperatureCallback` function
   @return void
   @see ColorTemperatureCallback
 **/
void SinricProLight::onColorTemperature(ColorTemperatureCallback cb)
{
  colorTemperatureCallback = cb;
}

/**
   @brief Set callback function for `increaseColorTemperature` request

   @param cb Function pointer to a `IncreaseColorTemperatureCallback` function
   @return void
   @see IncreaseColorTemperatureCallback
 **/
void SinricProLight::onIncreaseColorTemperature(IncreaseColorTemperatureCallback cb)
{
  increaseColorTemperatureCallback = cb;
}

/**
   @brief Set callback function for `decreaseColorTemperature` request

   @param cb Function pointer to a `DecreaseColorTemperatureCallback` function
   @return void
   @see DecreaseColorTemperatureCallback
 **/
void SinricProLight::onDecreaseColorTemperature(DecreaseColorTemperatureCallback cb)
{
  decreaseColorTemperatureCallback = cb;
}

/**
   @brief Send `setBrightness` event to SinricPro Server indicating actual brightness

   @param brightness    Integer value with actual brightness the device is set to
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProLight::sendBrightnessEvent(int brightness, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setBrightness", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["brightness"] = brightness;
  return sendEvent(eventMessage);
}

/**
   @brief Send `setColor` event to SinricPro Server indicating actual color

   @param r       Byte value for red
   @param g       Byte value for green
   @param b       Byte value for blue
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProLight::sendColorEvent(byte r, byte g, byte b, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setColor", cause.c_str());
  JsonObject event_color = eventMessage["payload"]["value"].createNestedObject("color");
  event_color["r"] = r;
  event_color["g"] = g;
  event_color["b"] = b;
  return sendEvent(eventMessage);
}

/**
   @brief Send `setColorTemperature` event to SinricPro Server indicating actual color temperature

   @param colorTemperature Integer with new color temperature the device is set to \n `2200` = warm white \n `2700` = soft white \n `4000` = white \n `5500` = daylight white \n `7000` = cool white
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProLight::sendColorTemperatureEvent(int colorTemperature, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setColorTemperature", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["colorTemperature"] = colorTemperature;
  return sendEvent(eventMessage);
}


#endif    //_SINRIC_PRO_LIGHT_H_

