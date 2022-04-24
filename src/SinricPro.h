/*********************************************************************************************************************************
  SinricPro.h - Sinric Pro Library for boards

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

#ifndef _SINRIC_PRO_H_
#define _SINRIC_PRO_H_

#include "SinricProInterface.h"
#include "SinricProDeviceInterface.h"
#include "SinricProWebsocket.h"
#include "SinricProUDP.h"
#include "SinricProSignature.h"
#include "SinricProMessageid.h"
#include "SinricProQueue.h"
#include "SinricProId.h"

/**
   @class SinricProClass
   @brief The main class of this library, handling communication between SinricPro Server and your devices
 **/
class SinricProClass : public SinricProInterface
{
  public:
    void begin(AppKey socketAuthToken, AppSecret signingKey, String serverURL = SINRICPRO_SERVER_URL);
    //void begin(String socketAuthToken, String signingKey, String serverURL = SINRICPRO_SERVER_URL);

#if 0    
    // KH, add from v2.5.1 to pass IP and mac to WebSockets Headers
    void begin(String socketAuthToken, String signingKey, IPAddress deviceIP, byte* macAddress, String serverURL = SINRICPRO_SERVER_URL);
    void begin(String socketAuthToken, String signingKey, IPAddress deviceIP, String macAddress, String serverURL = SINRICPRO_SERVER_URL);
    //////
#endif
    
    template <typename DeviceType>
    DeviceType& add(DeviceId deviceId);

    void add(SinricProDeviceInterface& newDevice);
    void add(SinricProDeviceInterface* newDevice);
    void handle();
    void stop();
    bool isConnected();

    /**
       @brief Callback definition for onConnected function

       Gets called when device is connected to SinricPro server
       @param void
       @return void
    */
    typedef std::function<void(void)> ConnectedCallbackHandler;
    /**
       @brief Callback definition for onDisconnected function

       Gets called when device is disconnected from SinricPro server
       @param void
       @return void
    */
    typedef std::function<void(void)> DisconnectedCallbackHandler;
    void onConnected(ConnectedCallbackHandler cb);
    void onDisconnected(DisconnectedCallbackHandler cb);

    void restoreDeviceStates(bool flag);

    DynamicJsonDocument prepareResponse(JsonDocument& requestMessage);
    DynamicJsonDocument prepareEvent(DeviceId deviceId, const char* action, const char* cause) override;
    void sendMessage(JsonDocument& jsonMessage) override;

    struct proxy
    {
      proxy(SinricProClass* ptr, DeviceId deviceId) : ptr(ptr), deviceId(deviceId) {}
      SinricProClass* ptr;
      DeviceId deviceId;

      template <typename DeviceType> operator DeviceType&()
      {
        return as<DeviceType>();
      }

      template <typename DeviceType> DeviceType& as()
      {
        return ptr->getDeviceInstance<DeviceType>(deviceId);
      }
    };
    /**
       @brief operator[] is used tor create a new device instance or get an existing device instance

       If the device is unknown to SinricProClass it will create a new device instance
       @param deviceId a String containing deviceId for device that have to been created or retrieved
       @return returns a proxy object representing the reference to a device derrivered from SinricProDevice
       @section Syntax
       `<DeviceType> &reference = SinricPro[<DEVICE_ID>];`
       @section operator[] Example-Code
       @code
       #define SWITCH_ID         "YOUR-DEVICE-ID"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
       ..
         SinricProSwitch &mySwitch = SinricPro[SWITCH_ID];
       ..
       @endcode
     **/
    proxy operator[](const DeviceId deviceId)
    {
      return proxy(this, deviceId);
    }

    // setResponseMessage is is just a workaround until verison 3.x.x will be released
    void setResponseMessage(String &&message)
    {
      responseMessageStr = message;
    }

    /**
       @brief Get the current timestamp

       @return unsigned long current timestamp (unix epoch time)
    */
    unsigned long getTimestamp() override
    {
      return baseTimestamp + (millis() / 1000);
    }

  private:
    void handleReceiveQueue();
    void handleSendQueue();

    void handleRequest(DynamicJsonDocument& requestMessage, interface_t Interface);
    void handleResponse(DynamicJsonDocument& responseMessage);

    DynamicJsonDocument prepareRequest(DeviceId deviceId, const char* action);

    void connect();
    void disconnect();
    void reconnect();

    void onConnect()
    {
      SRP_LOGINFO1("Connected to ", serverURL);
    }

    void onDisconnect()
    {
      SRP_LOGINFO("Disconnect");
    }

    void extractTimestamp(JsonDocument &message);

    SinricProDeviceInterface* getDevice(DeviceId deviceId);

    template <typename DeviceType>
    DeviceType& getDeviceInstance(DeviceId deviceId);

    std::vector<SinricProDeviceInterface*> devices;
    
    AppKey socketAuthToken;
    AppSecret signingKey;
    String serverURL;

    websocketListener _websocketListener;
    udpListener       _udpListener;
    SinricProQueue_t  receiveQueue;
    SinricProQueue_t  sendQueue;

    unsigned long baseTimestamp = 0;

    bool _begin = false;
    String responseMessageStr = "";
    
    // KH, add from v2.5.1 to pass IP and mac to WebSockets Headers
    // Init with invalid value
    IPAddress _deviceIP     = IPAddress(0,0,0,0);
    String    _macAddress   = "00:00:00:00:00:00";
    //////
};


SinricProDeviceInterface* SinricProClass::getDevice(DeviceId deviceId)
{
  for (auto& device : devices)
  {
    if (deviceId == device->getDeviceId()) 
      return device;
  }
  
  return nullptr;
}

template <typename DeviceType>
DeviceType& SinricProClass::getDeviceInstance(DeviceId deviceId)
{
  DeviceType* tmp_device = (DeviceType*) getDevice(deviceId);

  if (tmp_device)
    return *tmp_device;

  // KH, Check toString() equivalent
  SRP_LOGINFO1("Creating new device. No current DeviceId =", deviceId.toString());
  
  DeviceType& tmp_deviceInstance = add<DeviceType>(deviceId);

  if (isConnected())
  {
    SRP_LOGINFO("Reconnecting to server");
    reconnect();
  }

  return tmp_deviceInstance;
}

/**
   @brief Initializing SinricProClass to be able to connect to SinricPro Server

   @param socketAuthToken `String` containing APP_KEY (see credentials from https://sinric.pro )
   @param signingKey `String` containing APP_SECRET (see credentials from https:://sinric.pro)
   @param serverURL `String` containing SinricPro Server URL (default="ws.sinric.pro")
   @section Example-Code
   @code
   #define APP_KEY           "YOUR-APP-KEY"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
   #define APP_SECRET        "YOUR-APP-SECRET"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

   void setup() {
     SinricPro.begin(APP_KEY, APP_SECRET);
   }
   @endcode
 **/
void SinricProClass::begin(AppKey socketAuthToken, AppSecret signingKey, String serverURL)
{
  bool success = true;

  SRP_LOGINFO1("begin(): App-Key =", socketAuthToken.toString());
  SRP_LOGINFO1("begin(): App-Secret =", signingKey.toString());
  
  if (!socketAuthToken.isValid())
  {
    SRP_LOGERROR1("begin(): Invalid App-Key =", socketAuthToken.toString());
    success = false;
  }

  if (!signingKey.isValid())
  {
    SRP_LOGERROR1("begin(): Invalid App-Secret =", signingKey.toString());
    success = false;
  }

  if (!success)
  {
    _begin = false;
    return;
  }

  this->socketAuthToken = socketAuthToken;
  this->signingKey = signingKey;
  this->serverURL = serverURL;
  _begin = true;
  
  _udpListener.begin(&receiveQueue);
}

#if 0
// KH, add from v2.5.1 to pass IP and mac to WebSockets Headers
void SinricProClass::begin(String socketAuthToken, String signingKey, IPAddress deviceIP, byte* macAddress, String serverURL = SINRICPRO_SERVER_URL)
{
  // Convert byte* macAddress to String. Store to _deviceIP and _macAddress.
  // Then call begin()
  char macAddressStr[18] = { 0 };
  sprintf(macAddressStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2], 
            macAddress[3], macAddress[4], macAddress[5]);
   
  _deviceIP     = deviceIP;
  _macAddress   = String(macAddressStr);
  
  this->begin();
}
    
    
void SinricProClass::begin(String socketAuthToken, String signingKey, IPAddress deviceIP, String macAddress, String serverURL = SINRICPRO_SERVER_URL)
{
  // Store to _deviceIP and _macAddress.
  // Then call begin()
  _deviceIP     = deviceIP;
  _macAddress   = macAddress;
  
  this->begin();
}
//////
#endif

template <typename DeviceType>
DeviceType& SinricProClass::add(DeviceId deviceId)
{
  DeviceType* newDevice = new DeviceType(deviceId);
  
  if (DeviceId(deviceId).isValid())
  {
    SRP_LOGINFO1("add(): Adding DeviceId =", deviceId.toString());
    newDevice->begin(this);

    if (socketAuthToken.isValid() && signingKey.isValid())
      _begin = true;
  }
  else
  {
    SRP_LOGERROR1("add(): Invalid DeviceId =", deviceId.toString());
  }
  
  devices.push_back(newDevice);
  
  return *newDevice;
}

__attribute__ ((deprecated("Please use DeviceType& myDevice = SinricPro.add<DeviceType>(DeviceId);")))
void SinricProClass::add(SinricProDeviceInterface* newDevice)
{
  if (!newDevice->getDeviceId().isValid())
    return;

  newDevice->begin(this);
  devices.push_back(newDevice);
}

__attribute__ ((deprecated("Please use DeviceType& myDevice = SinricPro.add<DeviceType>(DeviceId);")))
void SinricProClass::add(SinricProDeviceInterface& newDevice)
{
  if (!newDevice.getDeviceId().isValid())
    return;

  newDevice.begin(this);
  devices.push_back(&newDevice);
}

/**
   @brief Handles communication between device and SinricPro Server

   This is the absolute main function which handles communication between your device and SinricPro Server. \n
   It is responsible for connect, disconnect to SinricPro Server, handling requests, responses and events. \n
   This function has to be called as often as possible. So it must be called in your main loop() function! \n

   For proper function, begin() must be called with valid values for 'APP_KEY' and 'APP_SECRET' \n
   @section handle Example-Code
   @code
   void loop() {
     SinricPro.handle();
   }
   @endcode
 **/
void SinricProClass::handle()
{
  static bool begin_error = false;

  if (!_begin)
  {
    if (!begin_error)
    {
      // print this only once!
      SRP_LOGERROR("handle(): ERROR! begin() failed or was not called prior to event handler");
      SRP_LOGERROR("-Reasons: Invalid app-key, app-secret or deviceIds");
      SRP_LOGERROR("-SinricPro is disabled! Check earlier log messages for details.");
      begin_error = true;
    }
    
    return;
  }

  if (!isConnected())
    connect();

  _websocketListener.handle();
  _udpListener.handle();

  handleReceiveQueue();
  handleSendQueue();
}

DynamicJsonDocument SinricProClass::prepareRequest(DeviceId deviceId, const char* action)
{
  DynamicJsonDocument requestMessage(1024);
  JsonObject header = requestMessage.createNestedObject("header");
  header["payloadVersion"]    = 2;
  header["signatureVersion"]  = 1;

  JsonObject payload    = requestMessage.createNestedObject("payload");
  payload["action"]     = action;
  payload["createdAt"]  = 0;
  payload["deviceId"]   = deviceId.toString();
  payload["replyToken"] = MessageID().getID();
  payload["type"]       = "request";
  
  payload.createNestedObject("value");
  
  return requestMessage;
}

void SinricProClass::handleResponse(DynamicJsonDocument& responseMessage) 
{
  SRP_LOGINFO("handleResponse():");

#ifndef NODEBUG_SINRIC
  serializeJsonPretty(responseMessage, SRP_DEBUG_OUTPUT);
  SRP_LOGINFO0("\n");
#endif
}

void SinricProClass::handleRequest(DynamicJsonDocument& requestMessage, interface_t Interface) 
{
  SRP_LOGINFO("handleRequest(): handling request");
  
#ifndef NODEBUG_SINRIC
  serializeJsonPretty(requestMessage, SRP_DEBUG_OUTPUT);
  SRP_LOGINFO0("\n");
#endif

  DynamicJsonDocument responseMessage = prepareResponse(requestMessage);

  // handle devices
  bool success = false;
  const char* deviceId      = requestMessage["payload"]["deviceId"];
  const char* action        = requestMessage["payload"]["action"];
  JsonObject request_value  = requestMessage["payload"]["value"];
  JsonObject response_value = responseMessage["payload"]["value"];

  for (auto& device : devices) 
  {
    if (device->getDeviceId() == deviceId && success == false)
    {
      success = device->handleRequest(deviceId, action, request_value, response_value);
      responseMessage["payload"]["success"] = success;
      
      if (!success) 
      {
        if (responseMessageStr.length() > 0) 
        {
          responseMessage["payload"]["message"] = responseMessageStr;
          responseMessageStr = "";
        } 
        else 
        {
          responseMessage["payload"]["message"] = "Device returned an error while processing the request!";
        }
      }
    }
  }

  String responseString;
  serializeJson(responseMessage, responseString);
  sendQueue.push(new SinricProMessage(Interface, responseString.c_str()));
}

void SinricProClass::handleReceiveQueue() 
{
  if (receiveQueue.size() == 0) 
    return;

  SRP_LOGINFO1("handleReceiveQueue(): Message(s) in receiveQueue =", receiveQueue.size());
  
  while (receiveQueue.size() > 0) 
  {
    SinricProMessage* rawMessage = receiveQueue.front();
    receiveQueue.pop();

    DynamicJsonDocument jsonMessage(1024);
    deserializeJson(jsonMessage, rawMessage->getMessage());

    bool sigMatch = false;

    if (strncmp(rawMessage->getMessage(), "{\"timestamp\":", 13) == 0 && strlen(rawMessage->getMessage()) <= 26) 
    {
      sigMatch = true; // timestamp message has no signature...ignore sigMatch for this!
    } 
    else 
    {
      sigMatch = verifyMessage(signingKey.toString(), jsonMessage);
    }

    String messageType = jsonMessage["payload"]["type"];

    if (sigMatch) 
    { 
      // signature is valid process message
      SRP_LOGINFO("handleReceiveQueue(): Valid Signature. Processing message...");
      extractTimestamp(jsonMessage);
      
      if (messageType == "response") 
        handleResponse(jsonMessage);
        
      if (messageType == "request") 
        handleRequest(jsonMessage, rawMessage->getInterface());
    } 
    else 
    {
      SRP_LOGERROR("handleReceiveQueue(): Invalid Signature! Sending messsage to [dev/null] ;=)");
    }
    
    delete rawMessage;
  }
}

void SinricProClass::handleSendQueue() 
{
  if (!isConnected()) 
    return;
    
  if (!baseTimestamp) 
    return;
   
  while (sendQueue.size() > 0) 
  {
    SRP_LOGINFO1("handleSendQueue(): Sending Number of Message(s) in sendQueue =", sendQueue.size());

    SinricProMessage* rawMessage = sendQueue.front(); 
    sendQueue.pop();

    DynamicJsonDocument jsonMessage(1024);
    deserializeJson(jsonMessage, rawMessage->getMessage());
    jsonMessage["payload"]["createdAt"] = getTimestamp();
    
    signMessage(signingKey.toString(), jsonMessage);

    String messageStr;

    serializeJson(jsonMessage, messageStr);
    
#ifndef NODEBUG_SINRIC
    serializeJsonPretty(jsonMessage, SRP_DEBUG_OUTPUT);
    Serial.println();
#endif

    switch (rawMessage->getInterface()) 
    {
      case IF_WEBSOCKET:
        SRP_LOGINFO("handleSendQueue: Sending to WebSocket"); 
        _websocketListener.sendMessage(messageStr); 
        break;
      case IF_UDP:
        SRP_LOGINFO("handleSendQueue: Sending to UDP"); 
        _udpListener.sendMessage(messageStr); 
        break;
      default:
        break;
    }
    
    delete rawMessage;
    
    SRP_LOGINFO("handleSendQueue(): Message sent.");
  }
}

void SinricProClass::connect() 
{
  String deviceList;
  int i = 0;
  
  for (auto& device : devices) 
  {
    DeviceId deviceId = device->getDeviceId();
    
    if (deviceId.isValid()) 
    {
      if (i > 0) 
        deviceList += ';';
        
      deviceList += deviceId.toString();
      i++;
    }
  }
  
  if (i == 0) 
  { 
    // no device have been added! -> do not connect!
    _begin = false;
    SRP_LOGERROR("ERROR! No valid devices. Please add first!");
    
    return;
  }

  _websocketListener.begin(serverURL, socketAuthToken.toString(), deviceList, &receiveQueue);
}


void SinricProClass::stop() 
{
  _begin = false;
  
  SRP_LOGERROR("stop()");
  
  _websocketListener.stop();
}

bool SinricProClass::isConnected() 
{
  return _websocketListener.isConnected();
};

/**
   @brief Set callback function for websocket connected event

   @param cb Function pointer to a `ConnectedCallbackHandler` function
   @return void
   @see ConnectedCallbackHandler
   @section onConnected Example-Code
   @snippet callbacks.cpp onConnected
 **/
void SinricProClass::onConnected(ConnectedCallbackHandler cb) 
{
  _websocketListener.onConnected(cb);
}

/**
   @brief Set callback function for websocket disconnected event

   @param cb Function pointer to a `DisconnectedCallbackHandler` function
   @return void
   @see DisconnectedCallbackHandler
   @section onDisconnected Example-Code
   @snippet callbacks.cpp onDisconnected
 **/
void SinricProClass::onDisconnected(DisconnectedCallbackHandler cb) 
{
  _websocketListener.onDisconnected(cb);
}


void SinricProClass::reconnect() 
{
  SRP_LOGINFO("reconnect(): Disconnecting");
  stop();
  
  SRP_LOGINFO("reconnect(): Connecting");
  connect();
}

void SinricProClass::extractTimestamp(JsonDocument &message) 
{
  unsigned long tempTimestamp = 0;
  
  // extract timestamp from timestamp message right after websocket connection is established
  tempTimestamp = message["timestamp"] | 0;
  
  if (tempTimestamp) 
  {
    baseTimestamp = tempTimestamp - (millis() / 1000);
    SRP_LOGINFO1("extractTimestamp(): Got Timestamp =", tempTimestamp);
    
    return;
  }

  // extract timestamp from request message
  tempTimestamp = message["payload"]["createdAt"] | 0;
  
  if (tempTimestamp) 
  {
    SRP_LOGINFO1("extractTimestamp(): Got Timestamp =", tempTimestamp);
    baseTimestamp = tempTimestamp - (millis() / 1000);
    
    return;
  }
}


void SinricProClass::sendMessage(JsonDocument& jsonMessage) 
{
  if (!isConnected()) 
  {
    SRP_LOGINFO("sendMessage(): Device is offline, message dropped");
    
    return;
  }
  
  SRP_LOGINFO("sendMessage(): pushing message into sendQueue");
  
  String messageString;
  
  serializeJson(jsonMessage, messageString);
  sendQueue.push(new SinricProMessage(IF_WEBSOCKET, messageString.c_str()));
}

/**
   @brief Enable / disable restore device states function

   If this flag is enabled (`true`), SinricProServer will send last known device states to your device directly after connection to SinricPro server has been established. \n
   For every state the corresponding callback (like `onPowerState`) will be called \n
   This is useful after a power failure / reboot of your device.

   @param flag `true` = enabled \n `false`= disabled
 **/
void SinricProClass::restoreDeviceStates(bool flag) 
{
  _websocketListener.setRestoreDeviceStates(flag);
}

DynamicJsonDocument SinricProClass::prepareResponse(JsonDocument& requestMessage) 
{
  DynamicJsonDocument responseMessage(1024);
  JsonObject header = responseMessage.createNestedObject("header");
  
  header["payloadVersion"]    = 2;
  header["signatureVersion"]  = 1;

  JsonObject payload    = responseMessage.createNestedObject("payload");
  payload["action"]     = requestMessage["payload"]["action"];
  payload["clientId"]   = requestMessage["payload"]["clientId"];
  payload["createdAt"]  = 0;
  payload["deviceId"]   = requestMessage["payload"]["deviceId"];
  payload["message"]    = "OK";
  payload["replyToken"] = requestMessage["payload"]["replyToken"];
  payload["success"]    = false;
  payload["type"]       = "response";
  
  payload.createNestedObject("value");
  
  return responseMessage;
}


DynamicJsonDocument SinricProClass::prepareEvent(DeviceId deviceId, const char* action, const char* cause)
{
  DynamicJsonDocument eventMessage(1024);
  JsonObject header = eventMessage.createNestedObject("header");
  
  header["payloadVersion"]    = 2;
  header["signatureVersion"]  = 1;

  JsonObject payload = eventMessage.createNestedObject("payload");
  
  payload["action"]         = action;
  payload["cause"].createNestedObject("type");
  payload["cause"]["type"]  = cause;
  payload["createdAt"]      = 0;
  payload["deviceId"]       = deviceId.toString();
  payload["replyToken"]     = MessageID().getID();
  payload["type"]           = "event";
  
  payload.createNestedObject("value");
  
  return eventMessage;
}

#ifndef NOSINRIC_INSTANCE
/**
   @class SinricPro
   @brief The main instance of SinricProClass

   Handles communication between SinricPro Server and your device \n
    @see SinricProClass
 **/
SinricProClass SinricPro;
#endif

#endif    //_SINRIC_PRO_H_
