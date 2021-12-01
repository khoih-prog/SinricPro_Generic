/****************************************************************************************************************************
  TV.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
   Example for how to use SinricPro TV device:
   - setup a TV device
   - handle request using callbacks

   If you encounter any issues:
   - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
   - ensure all dependent libraries are installed
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
     - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
   - open serial monitor and check whats happening
   - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
   - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
*/

#if !(defined(ESP32))
  #error This code is intended to run on the WT32 boards and ESP32 platform ! Please check your Tools->Board setting.
#endif

// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#define WEBSOCKET_SSL     true

#include <WebServer_WT32_ETH01.h>

#include "SinricPro_Generic.h"
#include "SinricProTV.h"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define TV_ID             "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200              // Change baudrate to your need

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

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
  (void) deviceId;
  (void) volumeDefault;

  tvVolume += volumeDelta;  // calcualte new absolute volume
  
  Serial.println("Volume changed about " + String(volumeDelta) + " to " + String(tvVolume));
  
  volumeDelta = tvVolume; // return new absolute volume
  return true;
}

bool onChangeChannel(const String &deviceId, String &channel) 
{
  (void) deviceId;
  
  tvChannel = channelNumbers[channel]; // save new channelNumber in tvChannel variable
  
  Serial.println("Change channel to \"" + channel + "\" / channel number " + String(tvChannel));
  
  return true;
}

bool onChangeChannelNumber(const String& deviceId, int channelNumber, String& channelName) 
{
  (void) deviceId;
  
  tvChannel = channelNumber; // update tvChannel to new channel number
     
  if (tvChannel > MAX_CHANNELS - 1) 
    tvChannel = MAX_CHANNELS - 1;

  channelName = channelNames[tvChannel]; // return the channelName

  Serial.println("Change channel to \"" + channelName + "\" / channel number " + String(tvChannel));
  return true;
}

bool onMediaControl(const String &deviceId, String &control) 
{
  (void) deviceId;
  
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
  (void) deviceId;
  
  Serial.println("TV volume is " + String(mute ? "muted" : "unmuted"));
  tvMuted = mute; // set tvMuted state
  return true;
}

bool onPowerState(const String &deviceId, bool &state) 
{
  (void) deviceId;
  
  Serial.println("TV turned " + String(state ? "on" : "off"));
  tvPowerState = state; // set powerState
  return true;
}

bool onSelectInput(const String &deviceId, String &input) 
{
  (void) deviceId;
  
  Serial.println("Input changed to " + input);
  return true;
}

bool onSetVolume(const String &deviceId, int &volume) 
{
  (void) deviceId;
  
  Serial.println("Volume set to:  " + String(volume));
  tvVolume = volume; // update tvVolume
  return true;
}

bool onSkipChannels(const String &deviceId, const int channelCount, String &channelName) 
{
  (void) deviceId;
  
  tvChannel += channelCount; // calculate new channel number
      
  if (tvChannel > MAX_CHANNELS - 1) 
    tvChannel = MAX_CHANNELS - 1;
    
  channelName = String(channelNames[tvChannel]); // return channel name

  Serial.println("Skip channel: " + String(channelCount) + " (number: " + String(tvChannel) + " / name: \"" + channelName + "\"");

  return true;
}

// setup function for ETH connection
void setupETH() 
{
  Serial.print("[ETH]: Connecting");
  
  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();
  
  Serial.print("[ETH]: IP-Address is ");
  Serial.println(ETH.localIP());
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
  
  Serial.print(F("\nStart TV on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(SINRICPRO_VERSION_STR);
  
  Serial.println(String(MAX_CHANNELS) + " channels configured");

  setupETH();
  setupSinricPro();
  setupChannelNumbers();
}

void loop() 
{
  SinricPro.handle();
}
