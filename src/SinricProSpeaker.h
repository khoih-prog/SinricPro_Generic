/****************************************************************************************************************************
  SinricProSpeeaker.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_SPEAKER_H_
#define _SINRIC_PRO_SPEAKER_H_

#include "SinricProDevice.h"

#define SPEAKER_MIN_VOLUME_LEVEL      0
#define SPEAKER_MAX_VOLUME_LEVEL      100

#define SPEAKER_MIN_BANDS_LEVEL       0
#define SPEAKER_MAX_BANDS_LEVEL       100


/**
   @class SinricProSpeaker
   @brief Device to control a smart speaker

   Supporting:
 * * setVolume / adjustVolume
 * * set / adjust / reset bands (BASS, MIDRANGE, TREBBLE)
 * * mute / unmute
 * * media controls:
 *   * FastForward
 *   * Next
 *   * Pause
 *   * Play
 *   * Previous
 *   * Rewind
 *   * StartOver
 *   * Stop
 * * set mode (TV, MOVIE, ...)
*/
class SinricProSpeaker :  public SinricProDevice
{
  public:
    SinricProSpeaker(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    {
      return SinricProDevice::getProductType() + String("SPEAKER"); 
    }
    //////
    
    // callbacks

    /**
       @brief Callback definition for onSetVolume function

       Gets called when device receive a `setVolume` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   volume      Integer with volume device should set to
       @param[out]  volume      Integer with volume device has been set to
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section SetVolumeCallback Example-Code
       @snippet callbacks.cpp onSetVolume
     **/
    typedef std::function<bool(const String&, int&)> SetVolumeCallback;

    /**
     * @brief Callback definition for onAdjustVolume function
     * 
     * Gets called when device receive a `adjustVolume` request \n
     * @param[in]   deviceId    String which contains the ID of device
     * @param[in]   volumeDelta Integer with relative volume the device should change about (-100..100)
     * @param[out]  volumeDelta Integer with absolute volume device has been set to
     * @param[in]   volumeDefault Bool `false` if the user specified the amount by which to change the volume; otherwise `true`
     * @return      the success of the request
     * @retval      true        request handled properly
     * @retval      false       request was not handled properly because of some error
     * 
     * @section AdjustVolumeCallback Example-Code
     * @snippet callbacks.cpp onAdjustVolume
     **/  
    typedef std::function<bool(const String&, int&, bool)> AdjustVolumeCallback;

    /**
       @brief Callback definition for onMute function

       Gets called when device receive a `setMute` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   mute        `true` mute device \n `false` unmute device
       @param[out]  mute        `true` device is muted \n `false` device is unmuted
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section MuteCallback Example-Code
       @snippet callbacks.cpp onMute
     **/
    typedef std::function<bool(const String&, bool&)> MuteCallback;

    /**
       @brief Callback definition for onMediaControl function

       Gets called when device receive a `mediaControl` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   control     String with requested control \n `FastForward`, `Next`, `Pause`, `Play`, `Previous`, `Rewind`, `StartOver`, `Stop`
       @param[out]  control     String with control \n `FastForward`, `Next`, `Pause`, `Play`, `Previous`, `Rewind`, `StartOver`, `Stop`
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section MediaControlCallback Example-Code
       @snippet callbacks.cpp onMediaControl
     **/
    typedef std::function<bool(const String&, String&)> MediaControlCallback;
    
    // From v2.5.1
    /**
     * @brief Callback definition for onSelectInput function
     * 
     * Gets called when device receive a `selectInput` request \n
     * @param[in]   deviceId    String which contains the ID of device
     * @param[in]   input       String with input name device is requested to switch to \n `AUX 1`..`AUX 7`, `BLURAY`, `CABLE`, `CD`, `COAX 1`,`COAX 2`, `COMPOSITE 1`, `DVD`, `GAME`, `HD RADIO`, `HDMI 1`.. `HDMI 10`, `HDMI ARC`, `INPUT 1`..`INPUT 10`, `IPOD`, `LINE 1`..`LINE 7`, `MEDIA PLAYER`, `OPTICAL 1`, `OPTICAL 2`, `PHONO`, `PLAYSTATION`, `PLAYSTATION 3`, `PLAYSTATION 4`, `SATELLITE`, `SMARTCAST`, `TUNER`, `TV`, `USB DAC`, `VIDEO 1`..`VIDEO 3`, `XBOX`
     * @param[out]  input       String with input name device has switchted to \n `AUX 1`..`AUX 7`, `BLURAY`, `CABLE`, `CD`, `COAX 1`,`COAX 2`, `COMPOSITE 1`, `DVD`, `GAME`, `HD RADIO`, `HDMI 1`.. `HDMI 10`, `HDMI ARC`, `INPUT 1`..`INPUT 10`, `IPOD`, `LINE 1`..`LINE 7`, `MEDIA PLAYER`, `OPTICAL 1`, `OPTICAL 2`, `PHONO`, `PLAYSTATION`, `PLAYSTATION 3`, `PLAYSTATION 4`, `SATELLITE`, `SMARTCAST`, `TUNER`, `TV`, `USB DAC`, `VIDEO 1`..`VIDEO 3`, `XBOX`
     * @return      the success of the request
     * @retval      true        request handled properly
     * @retval      false       request was not handled properly because of some error
     * 
     * @section SelectInput Example-Code
     * @snippet callbacks.cpp onSelectInput
     **/
    typedef std::function<bool(const String&, String&)> SelectInputCallback;
    //////

    /**
       @brief Callback definition for onSetBands function

       Gets called when device receive a `setBands` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   bands       String with requested bands to change \n `BASS`, `MIDRANGE`, `TREBBLE`
       @param[in]   level       Integer value with level bands should set to
       @param[out]  bands       String with changed bands \n `BASS`, `MIDRANGE`, `TREBBLE`
       @param[out]  level       Integer value with level bands changed to
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section SetBandsCallback Example-Code
       @snippet callbacks.cpp onSetBands
     **/
    typedef std::function<bool(const String&, const String&, int&)> SetBandsCallback;

    /**
       @brief Callback definition for onAdjustBands function

       Gets called when device receive a `adjustBands` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   bands       String with requested bands to change \n `BASS`, `MIDRANGE`, `TREBBLE`
       @param[in]   levelDelta  Integer with relative level value device should change bands about
       @param[out]  bands       String with changed bands \n `BASS`, `MIDRANGE`, `TREBBLE`
       @param[out]  levelDelta  Integer value with level bands changed to
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section AdjustBandsCallback Example-Code
       @snippet callbacks.cpp onAdjustBands
     **/
    typedef std::function<bool(const String&, const String&, int&)> AdjustBandsCallback;

    /**
       @brief Callback definition for onResetBands function

       Gets called when device receive a `onResetBands` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   bands       String with requested bands to reset \n `BASS`, `MIDRANGE`, `TREBBLE`
       @param[out]  bands       String with changed bands \n `BASS`, `MIDRANGE`, `TREBBLE`
       @param[out]  level       Integer value with level bands changed to
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section ResetBandsCallback Example-Code
       @snippet callbacks.cpp onResetBands
     **/
    typedef std::function<bool(const String&, const String&, int&)> ResetBandsCallback;

    /**
       @brief Callback definition for onSetMode function

       Gets called when device receive a `setBands` request \n
       @param[in]   deviceId    String which contains the ID of device
       @param[in]   mode        String device mode should set to \n `MOVIE`, `MUSIC`, `NIGHT`, `SPORT`, `TV`
       @param[out]  mode        String devices mode is set to \n `MOVIE`, `MUSIC`, `NIGHT`, `SPORT`, `TV`
       @return      the success of the request
       @retval      true        request handled properly
       @retval      false       request was not handled properly because of some error

       @section ModeCallback Example-Code
       @snippet callbacks.cpp onSetMode
     **/    typedef std::function<bool(const String&, String&)> ModeCallback;

    void onSetVolume(SetVolumeCallback cb);
    void onAdjustVolume(AdjustVolumeCallback cb);
    void onMute(MuteCallback cb);
    void onMediaControl(MediaControlCallback cb);
    // From v2.5.1
    void onSelectInput(SelectInputCallback cb);
    //////
    void onSetBands(SetBandsCallback cb);
    void onAdjustBands(AdjustBandsCallback cb);
    void onResetBands(ResetBandsCallback cb);
    void onSetMode(ModeCallback cb);

    // event
    bool sendVolumeEvent(int volume, String cause = "PHYSICAL_INTERACTION");
    bool sendMuteEvent(bool mute, String cause = "PHYSICAL_INTERACTION");
    bool sendMediaControlEvent(String mediaControl, String cause = "PHYSICAL_INTERACTION");
    
    // From v2.5.1
    bool sendSelectInputEvent(String intput, String cause = "PHYSICAL_INTERACTION");
    //////
    
    bool sendBandsEvent(String bands, int level, String cause = "PHYSICAL_INTERACTION");
    bool sendModeEvent(String mode, String cause = "PHYSICAL_INTERACTION");
    
    // handle
    bool handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, JsonObject &response_value) override;
    
  private:
    SetVolumeCallback volumeCallback;
    AdjustVolumeCallback adjustVolumeCallback;
    MuteCallback muteCallback;
    MediaControlCallback mediaControlCallback;
    
    // From v2.5.1
    SelectInputCallback selectInputCallback;
    //////
    
    SetBandsCallback setBandsCallback;
    AdjustBandsCallback adjustBandsCallback;
    ResetBandsCallback resetBandsCallback;
    ModeCallback setModeCallback;
};


SinricProSpeaker::SinricProSpeaker(const DeviceId &deviceId) : SinricProDevice(deviceId),
  volumeCallback(nullptr),
  adjustVolumeCallback(nullptr),
  muteCallback(nullptr),
  mediaControlCallback(nullptr),
  setBandsCallback(nullptr),
  adjustBandsCallback(nullptr),
  resetBandsCallback(nullptr),
  setModeCallback(nullptr)
{
}

bool SinricProSpeaker::handleRequest(const DeviceId &deviceId, const char* action, JsonObject &request_value, 
                                     JsonObject &response_value)
{
  if (deviceId != this->deviceId)
    return false;

  if (SinricProDevice::handleRequest(deviceId, action, request_value, response_value))
    return true;

  bool success = false;
  String actionString = String(action);

  if (volumeCallback && actionString == "setVolume")
  {
    int volume = request_value["volume"];
    success = volumeCallback(deviceId, volume);
    
    // From v2.5.1
    response_value["volume"] = limitValue(volume, SPEAKER_MIN_VOLUME_LEVEL, SPEAKER_MAX_VOLUME_LEVEL);
    //////
    
    return success;
  }

  if (adjustVolumeCallback && actionString == "adjustVolume")
  {
    int volume = request_value["volume"];
    
    // From v2.7.4
    bool volumeDefault = request_value["volumeDefault"] | false;
    success = adjustVolumeCallback(deviceId, volume, volumeDefault);
    //////
    
    // From v2.5.1
    response_value["volume"] = limitValue(volume, SPEAKER_MIN_VOLUME_LEVEL, SPEAKER_MAX_VOLUME_LEVEL);
    //////
    
    return success;
  }

  if (muteCallback && actionString == "setMute")
  {
    bool mute = request_value["mute"];
    success = muteCallback(deviceId, mute);
    response_value["mute"] = mute;
    
    return success;
  }

  if (setModeCallback && actionString == "setMode")
  {
    String mode = request_value["mode"] | "";
    success = setModeCallback(deviceId, mode);
    response_value["mode"] = mode;
    
    return success;
  }

  if (mediaControlCallback && actionString == "mediaControl")
  {
    String mediaControl = request_value["control"];
    success = mediaControlCallback(deviceId, mediaControl);
    response_value["control"] = mediaControl;
    
    return success;
  }
  
  // From v2.5.1
  if (selectInputCallback && actionString == "selectInput") 
  {
    String input = request_value["input"];
    success = selectInputCallback(deviceId, input);
    response_value["input"] = input;
    
    return success;
  }
  //////

  if (setBandsCallback && actionString == "setBands")
  {
    JsonArray bands_array = request_value["bands"];
    JsonArray response_value_bands = response_value.createNestedArray("bands");

    for (size_t i = 0; i < bands_array.size(); i++)
    {
      int level = bands_array[i]["level"] | 0;
      String bandsName = bands_array[i]["name"] | "";
      success = setBandsCallback(deviceId, bandsName, level);
      JsonObject response_value_bands_i = response_value_bands.createNestedObject();
      response_value_bands_i["name"] = bandsName;
      // From v2.5.1
      response_value_bands_i["level"] = limitValue(level, SPEAKER_MIN_BANDS_LEVEL, SPEAKER_MAX_BANDS_LEVEL);
      //////
    }

    return success;
  }

  if (setBandsCallback && actionString == "adjustBands")
  {
    JsonArray bands_array = request_value["bands"];
    JsonArray response_value_bands = response_value.createNestedArray("bands");

    for (size_t i = 0; i < bands_array.size(); i++)
    {
      int levelDelta = bands_array[i]["levelDelta"] | 1;
      String direction = bands_array[i]["levelDirection"];

      if (direction == "DOWN")
        levelDelta *= -1;

      String bandsName = bands_array[i]["name"] | "";
      success = adjustBandsCallback(deviceId, bandsName, levelDelta);
      JsonObject response_value_bands_i = response_value_bands.createNestedObject();
      response_value_bands_i["name"] = bandsName;
      // From v2.5.1
      response_value_bands_i["level"] = limitValue(levelDelta, SPEAKER_MIN_BANDS_LEVEL, SPEAKER_MAX_BANDS_LEVEL);
      //////
    }
    return success;
  }

  if (resetBandsCallback && actionString == "resetBands")
  {
    JsonArray bands_array = request_value["bands"];
    JsonArray response_value_bands = response_value.createNestedArray("bands");

    for (size_t i = 0; i < bands_array.size(); i++)
    {
      int level = 0;
      String bandsName = bands_array[i]["name"] | "";
      success = adjustBandsCallback(deviceId, bandsName, level);
      JsonObject response_value_bands_i = response_value_bands.createNestedObject();
      response_value_bands_i["name"] = bandsName;
      // From v2.5.1
      response_value_bands_i["level"] = limitValue(level, 0, 100);
      //////
    }
    return success;
  }

  return success;
}

/**
   @brief Set callback function for `setVolume` request

   @param cb Function pointer to a `SetVolumeCallback` function
   @return void
   @see SetVolumeCallback
 **/
void SinricProSpeaker::onSetVolume(SetVolumeCallback cb)
{
  volumeCallback = cb;
}

/**
   @brief Set callback function for `adjustVolume` request

   @param cb Function pointer to a `AdjustVolumeCallback` function
   @return void
   @see AdjustVolumeCallback
 **/
void SinricProSpeaker::onAdjustVolume(AdjustVolumeCallback cb)
{
  adjustVolumeCallback = cb;
}

/**
   @brief Set callback function for `setMute` request

   @param cb Function pointer to a `MuteCallback` function
   @return void
   @see MuteCallback
 **/
void SinricProSpeaker::onMute(MuteCallback cb)
{
  muteCallback = cb;
}

/**
   @brief Set callback function for `mediaControl` request

   @param cb Function pointer to a `MediaControlCallback` function
   @return void
   @see MediaControlCallback
 **/
void SinricProSpeaker::onMediaControl(MediaControlCallback cb)
{
  mediaControlCallback = cb;
}

// From v2.5.1
/**
 * @brief Set callback function for `selectInput` request
 * 
 * @param cb Function pointer to a `SelectInputCallback` function
 * @return void
 * @see SelectInputCallback
 **/
void SinricProSpeaker::onSelectInput(SelectInputCallback cb) 
{ 
  selectInputCallback = cb; 
}
//////

/**
   @brief Set callback function for `setBands` request

   @param cb Function pointer to a `SetBandsCallback` function
   @return void
   @see SetBandsCallback
 **/
void SinricProSpeaker::onSetBands(SetBandsCallback cb)
{
  setBandsCallback = cb;
}

/**
   @brief Set callback function for `adjustBands` request

   @param cb Function pointer to a `AdjustBandsCallback` function
   @return void
   @see AdjustBandsCallback
 **/
void SinricProSpeaker::onAdjustBands(AdjustBandsCallback cb)
{
  adjustBandsCallback = cb;
}

/**
   @brief Set callback function for `resetBands` request

   @param cb Function pointer to a `ResetBandsCallback` function
   @return void
   @see ResetBandsCallback
 **/
void SinricProSpeaker::onResetBands(ResetBandsCallback cb)
{
  resetBandsCallback = cb;
}

/**
   @brief Set callback function for `setMode` request

   @param cb Function pointer to a `ModeCallback` function
   @return void
   @see ModeCallback
 **/
void SinricProSpeaker::onSetMode(ModeCallback cb)
{
  setModeCallback = cb;
}

/**
   @brief Send `setVolume` event to SinricPro Server indicating actual volume has changed

   @param   volume        Integer reporting the volume that the device have been set to
   @param   cause         (optional) Reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return  the success of sending the event
   @retval  true          event has been sent successfully
   @retval  false         event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProSpeaker::sendVolumeEvent(int volume, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setVolume", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["volume"] = volume;
  return sendEvent(eventMessage);
}

/**
   @brief Send `setMute` event to SinricPro Server indicating actual mute state

   @param mute    `true` = device is muted on \n `false` = device is unmuted
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProSpeaker::sendMuteEvent(bool mute, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setMute", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["mute"] = mute;
  return sendEvent(eventMessage);
}

/**
   @brief Send `mediaControl` event to SinricPro Server indicating devices media control state

   @param mediaControl    String with actual media control \n `FastForward`, `Next`, `Pause`, `Play`, `Previous`, `Rewind`, `StartOver`, `Stop`
   @param cause           (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProSpeaker::sendMediaControlEvent(String mediaControl, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "mediaControl", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["control"] = mediaControl;
  return sendEvent(eventMessage);
}

/**
   @brief Send `setMode` event to SinricPro Server indicating the mode has changed

   @param mode    String with actual mode device is set to \n `MOVIE`, `MUSIC`, `NIGHT`, `SPORT`, `TV`
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProSpeaker::sendModeEvent(String mode, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setMode", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["mode"] = mode;
  return sendEvent(eventMessage);
}

/**
   @brief Send `setBands` event to SinricPro Server indicating bands level has changed

   @param bands   String which bands has changed \n `BASS`, `MIDRANGE`, `TREBBLE`
   @param level   Integer with changed bands level
   @param cause   (optional) `String` reason why event is sent (default = `"PHYSICAL_INTERACTION"`)
   @return the success of sending the even
   @retval true   event has been sent successfully
   @retval false  event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProSpeaker::sendBandsEvent(String bands, int level, String cause)
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "setBands", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  JsonArray event_value_bands = event_value.createNestedArray("bands");
  JsonObject event_bands = event_value_bands.createNestedObject();
  event_bands["name"] = bands;
  event_bands["value"] = level;
  return sendEvent(eventMessage);
}

#endif    //_SINRIC_PRO_SPEAKER_H_

