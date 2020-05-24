/****************************************************************************************************************************
  Generic_WiFiNINA_Speaker.ino
  For Generic boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  Example for how to use SinricPro Speaker device

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
 *****************************************************************************************************************************/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0


#if defined(ESP8266) || defined(ESP32)
#error This code is not intended to run on the ESP32/ESP8266 boards ! Please check your Tools->Board setting.
#endif

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true   

#if ENABLE_DEBUG
  #define DEBUG_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA

#include "SinricPro_Generic.h"
#include "SinricProSpeaker.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define SPEAKER_ID          "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200                // Change baudrate to your need

#define BANDS_INDEX_BASS      0
#define BANDS_INDEX_MIDRANGE  1
#define BANDS_INDEX_TREBBLE   2

enum speakerModes 
{
  mode_movie,
  mode_music,
  mode_night,
  mode_sport,
  mode_tv
};

// we use a struct to store all states and values for our speaker
struct 
{
  bool power;
  unsigned int volume;
  bool muted;
  speakerModes mode;
  int bands[3] = { 0, 0, 0 };
} speakerState;

// Speaker device callbacks
bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("Speaker turned " + String(state ? "on" : "off"));
  
  speakerState.power = state; // set powerState
  return true;
}

bool onSetVolume(const String &deviceId, int &volume) 
{
  Serial.println("Volume set to: " + String(volume));
  
  speakerState.volume = volume; // update Volume
  return true;
}

bool onAdjustVolume(const String &deviceId, int &volumeDelta) 
{
  speakerState.volume += volumeDelta;  // calcualte new absolute volume
  
  Serial.println("Volume changed about " + String() + " to " + String(speakerState.volume));
  
  volumeDelta = speakerState.volume; // return new absolute volume
  return true;
}

bool onMute(const String &deviceId, bool &mute) 
{
  Serial.println("Speaker is " + String(mute ? "muted" : "unmuted"));
  
  speakerState.muted = mute; // update muted state
  return true;
}

bool onMediaControl(const String &deviceId, String &control) 
{
  Serial.println("MediaControl: " + control);
  
  if (control == "Play") {}           // do whatever you want to do here
  if (control == "Pause") {}          // do whatever you want to do here
  if (control == "Stop") {}           // do whatever you want to do here
  if (control == "StartOver") {}      // do whatever you want to do here
  if (control == "Previous") {}       // do whatever you want to do here
  if (control == "Next") {}           // do whatever you want to do here
  if (control == "Rewind") {}         // do whatever you want to do here
  if (control == "FastForward") {}    // do whatever you want to do here
  return true;
}

bool onSetMode(const String &deviceId, String &mode) 
{
  Serial.println("Speaker mode set to " + mode);
  
  if (mode == "MOVIE") speakerState.mode = mode_movie;
  if (mode == "MUSIC") speakerState.mode = mode_music;
  if (mode == "NIGHT") speakerState.mode = mode_night;
  if (mode == "SPORT") speakerState.mode = mode_sport;
  if (mode == "TV") speakerState.mode = mode_tv;
  return true;
}

bool onSetBands(const String& deviceId, const String &bands, int &level) 
{
  Serial.println("Device " + deviceId + " bands " + bands + " set to " + String(level));
  
  int index;
  
  if (bands == "BASS") index = BANDS_INDEX_BASS;
  if (bands == "MIDRANGE") index = BANDS_INDEX_MIDRANGE;
  if (bands == "TREBBLE") index = BANDS_INDEX_TREBBLE;
  
  speakerState.bands[index] = level;
  return true;
}

bool onAdjustBands(const String &deviceId, const String &bands, int &levelDelta) 
{
  int index;
  
  if (bands == "BASS") index = BANDS_INDEX_BASS;
  if (bands == "MIDRANGE") index = BANDS_INDEX_MIDRANGE;
  if (bands == "TREBBLE") index = BANDS_INDEX_TREBBLE;
  speakerState.bands[index] += levelDelta;
  levelDelta = speakerState.bands[index]; // return absolute trebble level

  Serial.println("Device " + deviceId + " bands \"" + bands + "\" adjusted about " + String(levelDelta) + " to " + String(speakerState.bands[index]));
  
  return true; // request handled properly
}

bool onResetBands(const String &deviceId, const String &bands, int &level) 
{
  int index;
  
  if (bands == "BASS") index = BANDS_INDEX_BASS;
  if (bands == "MIDRANGE") index = BANDS_INDEX_MIDRANGE;
  if (bands == "TREBBLE") index = BANDS_INDEX_TREBBLE;
  speakerState.bands[index] = 0;
  level = speakerState.bands[index]; // return new level

  Serial.println("Device " + deviceId + " bands \"" + bands + "\" reset to " + String(speakerState.bands[index]));
  
  return true; // request handled properly
}


// setup function for WiFi connection
void setupWiFi()
{
  Serial.print("\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
}

// setup function for SinricPro
void setupSinricPro() 
{
  // add device to SinricPro
  SinricProSpeaker& speaker = SinricPro[SPEAKER_ID];

  // set callback functions to device
  speaker.onPowerState(onPowerState);
  speaker.onSetVolume(onSetVolume);
  speaker.onAdjustVolume(onAdjustVolume);
  speaker.onMute(onMute);
  speaker.onSetBands(onSetBands);
  speaker.onAdjustBands(onAdjustBands);
  speaker.onResetBands(onResetBands);
  speaker.onSetMode(onSetMode);
  speaker.onMediaControl(onMediaControl);

  // setup SinricPro
  SinricPro.onConnected([]()
  {
    Serial.println("Connected to SinricPro");
  });

  SinricPro.onDisconnected([]()
  {
    Serial.println("Disconnected from SinricPro");
  });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() 
{
  Serial.begin(BAUD_RATE);
  while (!Serial);

  Serial.println("\nStarting Generic_WiFiNINA_Speaker");

  setupWiFi();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
