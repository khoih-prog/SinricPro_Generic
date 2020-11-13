/****************************************************************************************************************************
  SAMD_WiFiNINA_TV.ino
  For Arduino SAMD21, Adafruit SAMD21, SAMD51 boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 **********************************************************************************************************************************/

// STM32 Boards supported: Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.
// SAM DUE
// Teensy 4.1, 4.0, 3.6, 3.5, 3.2/3.1, 3.0

#include "defines.h"

#include "SinricPro_Generic.h"
#include "SinricProTV.h"

bool tvPowerState;
unsigned int tvVolume;
unsigned int tvChannel;
bool tvMuted;

// channelNames used to convert channelNumber into channelName
// please put in your TV channel names
// channel numbers starts counting from 0!
// so "CBC" is channel 2
const char* channelNames[] = 
{
  "A/V",
  "CTV",
  "CBC",
  "CBS",
  "CNN",
  "Fox",
  "CNBC",
  "Global News",
  "BBC",
  "RTL II",
  "SUPER RTL",
  "KiKA"
};

#define MAX_CHANNELS sizeof(channelNames) / sizeof(channelNames[0])  // just to determine how many channels are in channelNames array

// map channelNumbers used to convert channelName into channelNumber
// This map is initialized in "setupChannelNumbers()" function by using the "channelNames" array
std::map<String, unsigned int> channelNumbers;

void setupChannelNumbers() 
{
  for (unsigned int i = 0; i < MAX_CHANNELS; i++) 
  {
    channelNumbers[channelNames[i]] = i;
  }
}

// TV device callbacks

bool onAdjustVolume(const String &deviceId, int &volumeDelta, bool volumeDefault)
{
  tvVolume += volumeDelta;  // calcualte new absolute volume
  
  Serial.println("Volume changed about " + String(volumeDelta) + " to " + String(tvVolume));
  
  volumeDelta = tvVolume; // return new absolute volume
  return true;
}

bool onChangeChannel(const String &deviceId, String &channel) 
{
  tvChannel = channelNumbers[channel]; // save new channelNumber in tvChannel variable
  
  Serial.println("Change channel to \"" + channel + "\" / channel number " + String(tvChannel));
  
  return true;
}

bool onChangeChannelNumber(const String& deviceId, int channelNumber, String& channelName) 
{
  tvChannel = channelNumber; // update tvChannel to new channel number
  
  if (tvChannel < 0) 
    tvChannel = 0;
    
  if (tvChannel > MAX_CHANNELS - 1) 
    tvChannel = MAX_CHANNELS - 1;

  channelName = channelNames[tvChannel]; // return the channelName

  Serial.println("Change channel to \"" + channelName + "\" / channel number " + String(tvChannel));
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

bool onMute(const String &deviceId, bool &mute) 
{
  Serial.println("TV volume is " + String(mute ? "muted" : "unmuted"));
  tvMuted = mute; // set tvMuted state
  return true;
}

bool onPowerState(const String &deviceId, bool &state) 
{
  Serial.println("TV turned " + String(state ? "on" : "off"));
  tvPowerState = state; // set powerState
  return true;
}

bool onSelectInput(const String &deviceId, String &input) 
{
  Serial.println("Input changed to " + input);
  return true;
}

bool onSetVolume(const String &deviceId, int &volume) 
{
  Serial.println("Volume set to:  " + String(volume));
  tvVolume = volume; // update tvVolume
  return true;
}

bool onSkipChannels(const String &deviceId, const int channelCount, String &channelName) 
{
  tvChannel += channelCount; // calculate new channel number
  
  if (tvChannel < 0) 
    tvChannel = 0;
    
  if (tvChannel > MAX_CHANNELS - 1) 
    tvChannel = MAX_CHANNELS - 1;
    
  channelName = String(channelNames[tvChannel]); // return channel name

  Serial.println("Skip channel: " + String(channelCount) + " (number: " + String(tvChannel) + " / name: \"" + channelName + "\"");

  return true;
}

// setup function for WiFi connection
void setupWiFi() 
{
  Serial.println("\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("\n[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());
}

// setup function for SinricPro
void setupSinricPro() 
{
  // add device to SinricPro
  SinricProTV& myTV = SinricPro[TV_ID];

  // set callback functions to device
  myTV.onAdjustVolume(onAdjustVolume);
  myTV.onChangeChannel(onChangeChannel);
  myTV.onChangeChannelNumber(onChangeChannelNumber);
  myTV.onMediaControl(onMediaControl);
  myTV.onMute(onMute);
  myTV.onPowerState(onPowerState);
  myTV.onSelectInput(onSelectInput);
  myTV.onSetVolume(onSetVolume);
  myTV.onSkipChannels(onSkipChannels);

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
  
  Serial.println("\nStarting SAMD_WiFiNINA_TV on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  Serial.println(String(MAX_CHANNELS) + " channels configured");

  setupWiFi();
  setupSinricPro();
  setupChannelNumbers();
}

void loop() 
{
  SinricPro.handle();
}
