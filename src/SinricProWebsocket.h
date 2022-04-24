/*********************************************************************************************************************************
  SinricProWebSockets.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_WEBSOCKET_H__
#define _SINRIC_PRO_WEBSOCKET_H__

#if defined ESP8266
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#elif (SINRIC_PRO_USING_RTL8720DN)
  #warning Use SINRIC_PRO_USING_RTL8720DN rpcWiFi Library in SinricProWebSocket
  #include <rpcWiFi.h>    
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

// New from v2.7.0
class AdvWebSocketsClient : public WebSocketsClient 
{
  public:
    void onPong(std::function<void(uint32_t)> cb) 
    { 
      _rttCb = cb; 
    }
    
  protected:
    void messageReceived(WSclient_t * client, WSopcode_t opcode, uint8_t * payload, size_t length, bool fin) 
    {
      if ((opcode == WSop_pong)&& (_rttCb)) 
      {
        _rttCb(millis()-_client.lastPing);
      }
      
      WebSocketsClient::messageReceived(client, opcode, payload, length, fin);
    }
    
  private:
    std::function<void(uint32_t)> _rttCb = nullptr;
};
//////

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

    // New from v2.7.0
    AdvWebSocketsClient webSocket;
    //////

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
// To add for Ethernet / WiFiNINA, etc. Add SINRIC_PRO_USING_RTL8720DN from v2.7.4
#if (ESP8266 || ESP32 || SINRIC_PRO_USING_RTL8720DN)
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

#elif ( SINRIC_PRO_USING_WIFININA || WIFININA_USE_SAMD || WIFININA_USE_NRF528XX || WIFININA_USE_SAM_DUE || WIFININA_USE_STM32 )
  #warning Very good. Using IP and macAddress for WebSockets header
  #warning If you have error here, Use the Library Patches to fix the issue
  
  IPAddress localIP = WiFi.localIP();
  headers += "ip:" + String(localIP[0]) + "." + String(localIP[1]) + "." + String(localIP[2]) + "." 
                   + String(localIP[3]) + + "\r\n";
                   
  uint8_t macAddress[6];
  char macAddressStr[18] = { 0 };      
  
  WiFi.macAddress(macAddress);
  
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
#elif (SINRIC_PRO_USING_RTL8720DN)
  headers += "platform:WIO_Terminal_RTL8720DN\r\n";
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
  
  SRP_LOGINFO0("Websocket: headers:\n");
  SRP_LOGINFO0(headers);
  SRP_LOGINFO0("\n");
  
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

// Currently working only on ESP32
#if (defined(WEBSOCKET_SSL) && WEBSOCKET_SSL)
  #warning Using WEBSOCKET_SSL
  SRP_LOGINFO1("Websocket: Connecting SSL to WebSocket Server: ", server);
#else
  #warning Not using WEBSOCKET_SSL
  SRP_LOGINFO1("Websocket: Connecting to WebSocket Server: ", server);
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

#if (defined(WEBSOCKET_SSL) && WEBSOCKET_SSL)
  #if (SINRIC_PRO_USING_RTL8720DN)
    webSocket.beginSSL(server.c_str(), SINRICPRO_SERVER_SSL_PORT, "/");
  #else  
    webSocket.beginSSL(server.c_str(), SINRICPRO_SERVER_SSL_PORT, "/");
  #endif
#else
  webSocket.begin(server.c_str(), SINRICPRO_SERVER_PORT, "/"); // server address, port and URL
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
  (void) length;
  
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

#endif    //_SINRIC_PRO_WEBSOCKET_H__
