/*********************************************************************************************************************************
  SinricProWebSockets.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.5.1

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
 **********************************************************************************************************************************/

#ifndef _SINRICPRO_WEBSOCKET_H__
#define _SINRICPRO_WEBSOCKET_H__

#if defined ESP8266
#include <ESP8266WiFi.h>
#endif
#if defined ESP32
#include <WiFi.h>
#endif

//KH
#include <WebSocketsClient_Generic.h>

#include <ArduinoJson.h>

// KH add v2.5.1
#include "SinricPro.h"

#include "SinricProDebug.h"
#include "SinricProConfig.h"
#include "SinricProQueue.h"
#include "SinricProInterface.h"

class websocketListener
{
  public:
    typedef std::function<void(void)> wsConnectedCallback;
    typedef std::function<void(void)> wsDisconnectedCallback;

    websocketListener();
    ~websocketListener();

    void begin(String server, String socketAuthToken, String deviceIds, SinricProQueue_t* receiveQueue);
    void handle();
    void stop();
    bool isConnected()
    {
      return _isConnected;
    }

    void setRestoreDeviceStates(bool flag)
    {
      this->restoreDeviceStates = flag;
    };

    void sendMessage(String &message);

    void onConnected(wsConnectedCallback callback)
    {
      _wsConnectedCb = callback;
    }

    void onDisconnected(wsDisconnectedCallback callback)
    {
      _wsDisconnectedCb = callback;
    }

    void disconnect()
    {
      webSocket.disconnect();
    }

  private:
    bool _begin = false;
    bool _isConnected = false;
    bool restoreDeviceStates = false;

    WebSocketsClient webSocket;

    wsConnectedCallback _wsConnectedCb;
    wsDisconnectedCallback _wsDisconnectedCb;

    void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
    void setExtraHeaders();
    SinricProQueue_t* receiveQueue;
    String deviceIds;
    String socketAuthToken;
};

void websocketListener::setExtraHeaders()
{
  String headers  = "appkey:" + socketAuthToken + "\r\n";
  headers += "deviceids:" + deviceIds + "\r\n";
  headers += "restoredevicestates:" + String(restoreDeviceStates ? "true" : "false") + "\r\n";

// From v2.5.1 to add mac and IP address at startup
// To add for Ethernet / WiFiNINA, etc.
#if (ESP8266 || ESP32)
  headers += "ip:" + WiFi.localIP().toString() + "\r\n";
  headers += "mac:" + WiFi.macAddress() + "\r\n";
#elif ( SINRIC_PRO_USING_ETHERNET || SINRIC_PRO_USING_ETHERNET_LARGE || SINRIC_PRO_USING_ETHERNET2 \
     || SINRIC_PRO_USING_ETHERNET3 || SINRIC_PRO_USING_ENC28J60 )
  // Other boards using Ethernet with Ethernet.localIP() and Ethernet.MACAddress(uint8_t *mac_address) functions
  // Ethernet2, Ethernet3 and UIPthernet don't support Ethernet.MACAddress() => to be modified to use enhanced header
  // Use the Library Patches to fix the issue
  // Here we can use both _deviceIP and _macAddress
  #warning Very good. Using IP and macAddress for WebSockets header
  #warning If you have error here, Use the Library Patches to fix the issue
  
  IPAddress localIP = Ethernet.localIP();
  headers += "ip:" + String(localIP[0]) + "." + String(localIP[1]) + "." + String(localIP[2]) + "." 
                   + String(localIP[3]) + + "\r\n";
  
  uint8_t macAddress[6];
  char macAddressStr[18] = { 0 };
  
  Ethernet.MACAddress(macAddress);
  
  sprintf(macAddressStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], 
            macAddress[3], macAddress[4], macAddress[5]);
            
  headers += "mac:" + String(macAddressStr) + "\r\n";

#else
  #warning Using no IP and macAddress for WebSockets header
  
#endif
//////
  
#if (ESP8266)
  headers += "platform:ESP8266\r\n";
#elif (ESP32)
  headers += "platform:ESP32\r\n";
#elif defined(BOARD_NAME)
  #warning Using BOARD_NAME for WebSockets header
  headers += "platform:";
  headers += BOARD_NAME;
  headers += "\r\n";
#elif defined(BOARD_TYPE)
  #warning Using BOARD_TYPE for WebSockets header
  headers += "platform:";
  headers += BOARD_TYPE;
  headers += "\r\n";  
#endif

// KH, from v2.5.1, using BOARD_NAME or BOARD_TYPE if defined


  headers += "version:" + String(SINRICPRO_VERSION);
  SRP_LOGDEBUG1("Websocket: headers:\n", headers);
  webSocket.setExtraHeaders(headers.c_str());
}

websocketListener::websocketListener() : _isConnected(false) {}

websocketListener::~websocketListener()
{
  stop();
}

void websocketListener::begin(String server, String socketAuthToken, String deviceIds, SinricProQueue_t* receiveQueue)
{
  if (_begin)
    return;

  _begin = true;

  this->receiveQueue = receiveQueue;
  this->socketAuthToken = socketAuthToken;
  this->deviceIds = deviceIds;

#ifdef WEBSOCKET_SSL
  SRP_LOGDEBUG1("Websocket: Connecting SSL to WebSocket Server: ", server);
#else
  SRP_LOGDEBUG1("Websocket: Connecting to WebSocket Server: ", server);
#endif

  if (_isConnected)
  {
    stop();
  }

  setExtraHeaders();
  webSocket.onEvent([&](WStype_t type, uint8_t * payload, size_t length)
  {
    webSocketEvent(type, payload, length);
  });

  webSocket.enableHeartbeat(WEBSOCKET_PING_INTERVAL, WEBSOCKET_PING_TIMEOUT, WEBSOCKET_RETRY_COUNT);

#ifdef WEBSOCKET_SSL
  // To get this working, WebSocketsClient.h needs to be fixed. See https://github.com/Links2004/arduinoWebSockets/issues/492
  webSocket.beginSSL(server, SINRICPRO_SERVER_SSL_PORT, "/");
#else
  webSocket.begin(server, SINRICPRO_SERVER_PORT, "/"); // server address, port and URL
#endif
}

void websocketListener::handle()
{
  webSocket.loop();
}

void websocketListener::stop()
{
  if (_isConnected)
  {
    webSocket.disconnect();
  }

  _begin = false;
}

void websocketListener::sendMessage(String &message)
{
  webSocket.sendTXT(message);
}


void websocketListener::webSocketEvent(WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_DISCONNECTED:
      if (_isConnected)
      {
        SRP_LOGDEBUG("Websocket: disconnected");
        if (_wsDisconnectedCb) _wsDisconnectedCb();
        _isConnected = false;
      }
      break;
    case WStype_CONNECTED:
      _isConnected = true;
      SRP_LOGDEBUG("Websocket: connected");

      if (_wsConnectedCb)
        _wsConnectedCb();

      if (restoreDeviceStates)
      {
        restoreDeviceStates = false;
        setExtraHeaders();
      }
      break;
    case WStype_TEXT:
      {
        SinricProMessage* request = new SinricProMessage(IF_WEBSOCKET, (char*)payload);
        SRP_LOGDEBUG("Websocket: receiving data");
        receiveQueue->push(request);
        break;
      }
    default: break;
  }
}

#endif    //_SINRICPRO_WEBSOCKET_H__
