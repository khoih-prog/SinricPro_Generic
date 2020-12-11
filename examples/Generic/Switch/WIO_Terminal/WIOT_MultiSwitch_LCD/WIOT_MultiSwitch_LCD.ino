/****************************************************************************************************************************
  WIOT_MultiSwitch_LCD.ino
  For WIO Terminal boards, running RTL8720DN WiFi, using Seeed_Arduino_rpcWiFi and Seeed_Arduino_rpcUnified libraries

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 **********************************************************************************************************************************/
 
#include "defines.h"
#include "SinricPro_Generic.h"          // https://github.com/khoih-prog/SinricPro_Generic
#include "SinricProSwitch.h"

#define USING_LCD     true

#if USING_LCD

  #include <LovyanGFX.hpp>              // https://github.com/lovyan03/LovyanGFX
  
  LGFX lcd;
  LGFX_Sprite spr = LGFX_Sprite(&lcd);

  #define tft lcd

#else

  #include <TFT_eSPI.h>                 // https://github.com/Bodmer/TFT_eSPI
  #include <SPI.h>
  
  TFT_eSPI tft = TFT_eSPI();            // Invoke custom library
  TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite

#endif

bool myPowerState1 = false;
bool myPowerState2 = false;
bool myPowerState3 = false;

int LED1_PIN = 2;
int LED2_PIN = 3;
int LED3_PIN = 4;

bool isSinricConnected  = false;
bool isWiFiConnected    = false;

typedef struct
{
  int   deviceIndex;
  int   LED_PIN;
  int   BUTTON_PIN;
  bool  powerState;
} deviceConfig_t;

// To use for Y_Coordinate
typedef enum
{
  WIFI        = 0,
  SINRIC      = 1,
  DEVICE1     = 2,
  DEVICE2     = 3,
  DEVICE3     = 4,
  MAX_Y_INDEX
} Device_Y_Index;

// Coordinates to display "WIFI", "Sinric", "Device1", etc.
int16_t Y_Coordinate[MAX_Y_INDEX] = { 5, 35, 65, 95, 125 };

#define WIFI_STATUS_COORDINATE    120
#define ON_OFF_X_COORDINATE       120

#define START_Y_COORDINATE        10

#define MAX_X_SPRITE              280
#define MAX_Y_SPRITE              175

#define FONT_SIZE                 4

// this is the main configuration
// please put in your deviceId, the PIN for Relay and PIN for flipSwitch
// this can be up to N devices...depending on how much pin's available on your device ;)
// right now we have 3 devicesIds going to 3 relays and 3 flip switches to switch the relay manually
std::map<String, deviceConfig_t> devices =
{
  //{deviceId, {deviceIndex,  LED_PIN, BUTTON_PIN, powerState}}
  // You have to set the pins correctly. This is for WIO Terminal
  { SWITCH_ID_1, {  1, LED1_PIN,  WIO_KEY_C,  false }},
  { SWITCH_ID_2, {  2, LED2_PIN,  WIO_KEY_B,  false }},
  { SWITCH_ID_3, {  3, LED3_PIN,  WIO_KEY_A,  false }},
};

typedef struct
{
  // struct for the std::map below
  String deviceId;
  bool lastFlipSwitchState;
  unsigned long lastFlipSwitchChange;
} flipSwitchConfig_t;

// this map is used to map flipSwitch PINs to deviceId and handling debounce and last flipSwitch state checks
// it will be setup in "setupFlipSwitches" function, using informations from devices map
std::map<int, flipSwitchConfig_t> flipSwitches;

void setupLEDs()
{
  for (auto &device : devices)
  {
    // for each device (relay, flipSwitch combination)
    int LEDPIN = device.second.LED_PIN;   // get the relay pin

    pinMode(LEDPIN, OUTPUT);              // set relay pin to OUTPUT
    digitalWrite(LEDPIN, LOW);            // turn off LED on bootup
  }
}

void setupFlipSwitches()
{
  for (auto &device : devices)
  {
    // for each device (relay / flipSwitch combination)
    flipSwitchConfig_t flipSwitchConfig;              // create a new flipSwitch configuration

    flipSwitchConfig.deviceId = device.first;         // set the deviceId
    flipSwitchConfig.lastFlipSwitchChange = 0;        // set debounce time
    flipSwitchConfig.lastFlipSwitchState = true;      // set lastFlipSwitchState to true (HIGH)

    int flipSwitchPIN = device.second.BUTTON_PIN;     // get the flipSwitchPIN

    flipSwitches[flipSwitchPIN] = flipSwitchConfig;   // save the flipSwitch config to flipSwitches map
    pinMode(flipSwitchPIN, INPUT);                    // set the flipSwitch pin to INPUT
  }
}

void processSinricProGUI()
{
  if (isSinricConnected)
  {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString("Connected   ", ON_OFF_X_COORDINATE , Y_Coordinate[SINRIC] + 5, FONT_SIZE);
  }
  else
  {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("Disconnect", ON_OFF_X_COORDINATE , Y_Coordinate[SINRIC] + 5, FONT_SIZE);
  }
}

void processGUI()
{
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("WIFI :", START_Y_COORDINATE , Y_Coordinate[WIFI]);
  spr.drawString("Sinric:", START_Y_COORDINATE , Y_Coordinate[SINRIC]);
  spr.setTextColor(TFT_GREEN, TFT_BLACK);
  spr.drawString(isWiFiConnected ? "Connected" : "Disconnect", WIFI_STATUS_COORDINATE , FONT_SIZE);

  processSinricProGUI();

  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  spr.drawString("Device1: ", START_Y_COORDINATE, Y_Coordinate[DEVICE1]);
  spr.drawString("Device2: ", START_Y_COORDINATE, Y_Coordinate[DEVICE2]);
  spr.drawString("Device3: ", START_Y_COORDINATE, Y_Coordinate[DEVICE3]);
}

bool onPowerState(const String &deviceId, bool &state)
{
  int index = devices[deviceId].deviceIndex;
  
  Serial.println( "\n=======================================");
  Serial.printf( "Device %d turned %s\r\n", index, state ? "ON" : "OFF");

  int LED_PIN = devices[deviceId].LED_PIN; // get the relay pin for corresponding device

  devices[deviceId].powerState = state;

  digitalWrite(LED_PIN, state ? HIGH : LOW);

  processGUI();

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString(state ? " ON  " : "OFF", ON_OFF_X_COORDINATE , Y_Coordinate[index + DEVICE1 - 1] + 5, FONT_SIZE);

  return true; // request handled properly
}

void handleFlipSwitches()
{
  unsigned long actualMillis = millis();

  // get actual millis
  for (auto &flipSwitch : flipSwitches)
  {
    // for each flipSwitch in flipSwitches map
    unsigned long lastFlipSwitchChange = flipSwitch.second.lastFlipSwitchChange;  // get the timestamp when flipSwitch was pressed last time (used to debounce / limit events)

    if (actualMillis - lastFlipSwitchChange > DEBOUNCE_TIME)
    {
      // if time is > debounce time...
      int flipSwitchPIN = flipSwitch.first;                                       // get the flipSwitch pin from configuration
      bool lastFlipSwitchState = flipSwitch.second.lastFlipSwitchState;           // get the lastFlipSwitchState
      bool flipSwitchState = digitalRead(flipSwitchPIN);                          // read the current flipSwitch state

      if (flipSwitchState != lastFlipSwitchState)
      {
        // if the flipSwitchState has changed...
#ifdef TACTILE_BUTTON
        if (flipSwitchState)
        {
          // if the tactile button is pressed
#endif
          flipSwitch.second.lastFlipSwitchChange = actualMillis;                  // update lastFlipSwitchChange time
          String deviceId = flipSwitch.second.deviceId;                           // get the deviceId from config

          handleButtonPress(deviceId);                                            // call handling function

#ifdef TACTILE_BUTTON
        }
#endif
        flipSwitch.second.lastFlipSwitchState = flipSwitchState;                  // update lastFlipSwitchState
      }
    }
  }
}

void handleButtonPress(const String &deviceId)
{

  int index = devices[deviceId].deviceIndex;

  // SW with deviceId / index pressed
  bool powerState = devices[deviceId].powerState;   //devices[deviceId].powerState;

  // is button pressed (inverted logic! button pressed = LOW) and debounced?
  if (powerState)
  {
    // flip myPowerState: if it was true, set it to false, vice versa
    devices[deviceId].powerState = powerState = false;
    spr.fillSprite(TFT_BLACK);
    spr.setFreeFont(&FreeSansBoldOblique12pt7b);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString("OFF", ON_OFF_X_COORDINATE , Y_Coordinate[index + DEVICE1 - 1] + 5, FONT_SIZE);
  }
  else
  {
    devices[deviceId].powerState = powerState = true;
    spr.fillSprite(TFT_BLACK);
    spr.setFreeFont(&FreeSansBoldOblique12pt7b);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString(" ON  ", ON_OFF_X_COORDINATE , Y_Coordinate[index + DEVICE1 - 1] + 5, FONT_SIZE);
  }

  digitalWrite(devices[deviceId].LED_PIN, powerState ? HIGH : LOW); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)

  // get Switch device back
  SinricProSwitch &mySwitch = SinricPro[deviceId];

  // send powerstate event
  mySwitch.sendPowerStateEvent(powerState); // send the new powerState to SinricPro server

  Serial.printf("Device %d with deviceID :", index);
  Serial.print(mySwitch.getDeviceId().toString());
  Serial.print(powerState ? "turned ON" : "turned OFF");
  Serial.println(" (manually via flashbutton)");

  processSinricProGUI();
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

  isWiFiConnected = true;

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("\n[WiFi]: IP-Address is ");
  Serial.println(WiFi.localIP());

  processGUI();

  spr.pushSprite(0, 0);
}

void handleSinricProConnect(bool isConnected)
{
  Serial.printf("SinricPro %s\r\n", isConnected ? "Connected" : "Disconnect");

  isSinricConnected = isConnected;

  Serial.printf("isSinricConnected %s\r\n", isSinricConnected ? "Connected" : "Disconnect");

  spr.fillSprite(TFT_BLACK);
  spr.createSprite(MAX_X_SPRITE, MAX_Y_SPRITE);

  processGUI();
}

void setupSinricPro()
{
  for (auto &device : devices)
  {
    const char *deviceId = device.first.c_str();
    SinricProSwitch &mySwitch = SinricPro[deviceId];
    mySwitch.onPowerState(onPowerState);
  }

  // setup SinricPro
  SinricPro.onConnected([]()
  {
    Serial.println("Connected to SinricPro");
    handleSinricProConnect(true);
  });

  SinricPro.onDisconnected([]()
  {
    Serial.println("Disconnected from SinricPro");
    handleSinricProConnect(false);
  });

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setupTFT()
{
  tft.begin();
  tft.startWrite();

  if (tft.width() < tft.height())
    tft.setRotation(tft.getRotation() ^ 1);

  spr.createSprite(MAX_X_SPRITE, MAX_Y_SPRITE);
  spr.fillSprite(TFT_BLACK);

  processGUI();
  
  spr.pushSprite(0, 0);
}

void setup()
{
  Serial.begin(BAUD_RATE);
  while (!Serial);

  Serial.println("\nStarting WIOT_MultiSwitch_LCD on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SINRICPRO_VERSION_STR));

  setupLEDs();
  setupFlipSwitches();
  setupTFT();
  setupWiFi();
  setupSinricPro();
}

void loop()
{
  SinricPro.handle();
  handleFlipSwitches();
}
