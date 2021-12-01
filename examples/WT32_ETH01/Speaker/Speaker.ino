/****************************************************************************************************************************
  Speaker.ino
  For ESP32/ESP8266 boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
 
/*
   Example for how to use SinricPro Speaker device

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
#include "SinricProSpeaker.h"

#define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SPEAKER_ID        "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"

#define BAUD_RATE         115200              // Change baudrate to your need

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

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
  int bands[3] = {0, 0, 0};
} speakerState;

// Speaker device callbacks
bool onPowerState(const String &deviceId, bool &state) 
{
  (void) deviceId;
  
  Serial.printf("Speaker turned %s\r\n", state ? "on" : "off");
  speakerState.power = state; // set powerState
  
  return true;
}

bool onSetVolume(const String &deviceId, int &volume) 
{
  (void) deviceId;
  
  Serial.printf("Volume set to:  %i\r\n", volume);
  speakerState.volume = volume; // update Volume
  
  return true;
}

bool onAdjustVolume(const String &deviceId, int &volumeDelta, bool volumeDefault)
{
  (void) deviceId;
  (void) volumeDefault;
  
  speakerState.volume += volumeDelta;  // calcualte new absolute volume
  Serial.printf("Volume changed about %i to %i\r\n", volumeDelta, speakerState.volume);
  volumeDelta = speakerState.volume; // return new absolute volume
  
  return true;
}

bool onMute(const String &deviceId, bool &mute) 
{
  (void) deviceId;
  
  Serial.printf("Speaker is %s\r\n", mute ? "muted" : "unmuted");
  speakerState.muted = mute; // update muted state
  
  return true;
}

bool onMediaControl(const String &deviceId, String &control) 
{
  (void) deviceId;
  
  Serial.printf("MediaControl: %s\r\n", control.c_str());
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
  (void) deviceId;
  
  Serial.printf("Speaker mode set to %s\r\n", mode.c_str());
  
  if (mode == "MOVIE") 
    speakerState.mode = mode_movie;
    
  if (mode == "MUSIC") 
    speakerState.mode = mode_music;
    
  if (mode == "NIGHT") 
    speakerState.mode = mode_night;
    
  if (mode == "SPORT") 
    speakerState.mode = mode_sport;
    
  if (mode == "TV") 
    speakerState.mode = mode_tv;
  
  return true;
}

bool onSetBands(const String& deviceId, const String &bands, int &level) 
{
  Serial.printf("Device %s bands %s set to %d\r\n", deviceId.c_str(), bands.c_str(), level);
  int index;
  
  if (bands == "BASS") 
    index = BANDS_INDEX_BASS;
    
  if (bands == "MIDRANGE") 
    index = BANDS_INDEX_MIDRANGE;
    
  if (bands == "TREBBLE") 
    index = BANDS_INDEX_TREBBLE;
    
  speakerState.bands[index] = level;
  
  return true;
}

bool onAdjustBands(const String &deviceId, const String &bands, int &levelDelta) 
{
  int index;
  
  if (bands == "BASS") 
    index = BANDS_INDEX_BASS;
    
  if (bands == "MIDRANGE") 
    index = BANDS_INDEX_MIDRANGE;
    
  if (bands == "TREBBLE") 
    index = BANDS_INDEX_TREBBLE;
    
  speakerState.bands[index] += levelDelta;
  levelDelta = speakerState.bands[index]; // return absolute trebble level

  Serial.printf("Device %s bands \"%s\" adjusted about %i to %d\r\n", deviceId.c_str(), bands.c_str(), levelDelta, speakerState.bands[index]);
  
  return true; // request handled properly
}

bool onResetBands(const String &deviceId, const String &bands, int &level) 
{
  int index;
  
  if (bands == "BASS") 
    index = BANDS_INDEX_BASS;
    
  if (bands == "MIDRANGE") 
    index = BANDS_INDEX_MIDRANGE;
    
  if (bands == "TREBBLE") 
    index = BANDS_INDEX_TREBBLE;
    
  speakerState.bands[index] = 0;
  level = speakerState.bands[index]; // return new level

  Serial.printf("Device %s bands \"%s\" reset to%d\r\n", deviceId.c_str(), bands.c_str(), speakerState.bands[index]);
  
  return true; // request handled properly
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
   
  Serial.print(F("\nStart Speaker on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(SINRICPRO_VERSION_STR);
  
  setupETH();
  setupSinricPro();
}

void loop() 
{
  SinricPro.handle();
}
