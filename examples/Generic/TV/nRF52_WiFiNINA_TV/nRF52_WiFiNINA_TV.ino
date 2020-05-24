/****************************************************************************************************************************
  nRF52_WiFiNINA_TV.ino
  For Adafruit nRF52 boards, running WiFiNINA

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.4.0

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Example for how to use SinricPro TV device:
   - setup a TV device
   - handle request using callbacks

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
 *****************************************************************************************************************************/

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG    true

#if ENABLE_DEBUG
  #define DEBUG_PORT            Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) | defined(NINA_B302_ublox) )
  #if defined(WIFININA_USE_NRF52)
    #undef WIFININA_USE_NRF52
  #endif
  #define WIFININA_USE_NRF52          true
  #define WIFI_USE_NRF52              true
  #define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA
#else
  #error This code is intended to run only on the Adafruit nRF52 boards ! Please check your Tools->Board setting.
#endif


#if defined(NRF52840_FEATHER)
  #define BOARD_TYPE      "NRF52840_FEATHER"
#elif defined(NRF52832_FEATHER)
  #define BOARD_TYPE      "NRF52832_FEATHER"
#elif defined(NRF52840_FEATHER_SENSE)
  #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
#elif defined(NRF52840_ITSYBITSY)
  #define BOARD_TYPE      "NRF52840_ITSYBITSY"
#elif defined(NRF52840_CIRCUITPLAY)
  #define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
#elif defined(NRF52840_CLUE)
  #define BOARD_TYPE      "NRF52840_CLUE"
#elif defined(NRF52840_METRO)
  #define BOARD_TYPE      "NRF52840_METRO"
#elif defined(NRF52840_PCA10056)
  #define BOARD_TYPE      "NRF52840_PCA10056"
#elif defined(PARTICLE_XENON)
  #define BOARD_TYPE      "PARTICLE_XENON"
#elif defined(NINA_B302_ublox)
  #define BOARD_TYPE      "NINA_B302_ublox"
#elif defined(ARDUINO_NRF52_ADAFRUIT)
  #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
#elif defined(NRF52_SERIES)
  #define BOARD_TYPE      "NRF52_SERIES"
#else
  #define BOARD_TYPE      "NRF52_UNKNOWN"
#endif

#include "SinricPro_Generic.h"
#include "SinricProTV.h"

#define WIFI_SSID         "YOUR-WIFI-SSID"
#define WIFI_PASS         "YOUR-WIFI-PASSWORD"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define TV_ID             "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200

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

bool onAdjustVolume(const String &deviceId, int &volumeDelta) 
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
  
#if defined(BOARD_TYPE)  
  Serial.println("\nStarting nRF52_WiFiNINA_TV on " + String(BOARD_TYPE));
#else
  Serial.println("\nStarting nRF52_WiFiNINA_TV on unknown board");
#endif  

  Serial.println(String(MAX_CHANNELS) + " channels configured");

  setupWiFi();
  setupSinricPro();
  setupChannelNumbers();
}

void loop() 
{
  SinricPro.handle();
}
