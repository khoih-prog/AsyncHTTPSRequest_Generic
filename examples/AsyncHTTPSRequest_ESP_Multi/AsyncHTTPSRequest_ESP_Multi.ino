/****************************************************************************************************************************
  AsyncHTTPSRequest_ESP_Multi.ino - Dead simple AsyncHTTPSRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet

  For ESP8266, ESP32 and STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)

  AsyncHTTPSRequest_Generic is a library for the ESP8266, ESP32 and currently STM32 run built-in Ethernet WebServer

  Based on and modified from AsyncHTTPRequest Library (https://github.com/boblemaire/AsyncHTTPRequest)

  Built by Khoi Hoang https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
  Licensed under MIT license

  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *****************************************************************************************************************************/
//************************************************************************************************************
//
// There are scores of ways to use AsyncHTTPSRequest.  The important thing to keep in mind is that
// it is asynchronous and just like in JavaScript, everything is event driven.  You will have some
// reason to initiate an asynchronous HTTP request in your program, but then sending the request
// headers and payload, gathering the response headers and any payload, and processing
// of that response, can (and probably should) all be done asynchronously.
//
// In this example, a Ticker function is setup to fire every 300 seconds to initiate a request.
// Everything is handled in AsyncHTTPSRequest without blocking.
// The callback onReadyStateChange is made progressively and like most JS scripts, we look for
// readyState == 4 (complete) here.  At that time the response is retrieved and printed.
//
// Note that there is no code in loop().  A code entered into loop would run oblivious to
// the ongoing HTTP requests.  The Ticker could be removed and periodic calls to sendRequest()
// could be made in loop(), resulting in the same asynchronous handling.
//
// For demo purposes, debug is turned on for handling of the first request.  These are the
// events that are being handled in AsyncHTTPSRequest.  They all begin with Debug(nnn) where
// nnn is the elapsed time in milliseconds since the transaction was started.
//
//*************************************************************************************************************

#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN_TARGET      "AsyncHTTPSRequest_Generic v2.2.0"
#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN             2002000

// Level from 0-4
#define ASYNC_HTTPS_DEBUG_PORT      Serial

#define _ASYNC_TCP_SSL_LOGLEVEL_    1
#define _ASYNC_HTTPS_LOGLEVEL_      3

// 300s = 5 minutes to not flooding
#define HTTPS_REQUEST_INTERVAL      60  //300

// 10s
#define HEARTBEAT_INTERVAL          10

int status;     // the Wifi radio's status

const char* ssid        = "your_ssid";
const char* password    = "your_pass";

#if (ESP8266)
  #include <ESP8266WiFi.h>
#elif (ESP32)
  #include <WiFi.h>
#endif

// Use larger queue size if necessary for large data transfer. Default is 512 bytes if not defined here
//#define ASYNC_QUEUE_LENGTH     512

// Use larger priority if necessary. Default is 10 if not defined here. Must be > 4 or adjusted to 4
//#define CONFIG_ASYNC_TCP_PRIORITY   (12)

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPSRequest_Generic.h>            // https://github.com/khoih-prog/AsyncHTTPSRequest_Generic

#include <Ticker.h>

#define NUM_DIFFERENT_SITES     2

const char* addreses[][NUM_DIFFERENT_SITES] = 
{
  {"https://worldtimeapi.org/api/timezone/America/Toronto.txt", "https://worldtimeapi.org/api/timezone/Europe/Prague.txt"},
  {"https://www.myexternalip.com/raw"}
};

#define NUM_ENTRIES_SITE_0        2
#define NUM_ENTRIES_SITE_1        1

byte reqCount[NUM_DIFFERENT_SITES]  = { NUM_ENTRIES_SITE_0, NUM_ENTRIES_SITE_1 };
bool readySend[NUM_DIFFERENT_SITES] = { true, true };

AsyncHTTPSRequest request[NUM_DIFFERENT_SITES];

void requestCB0(void* optParm, AsyncHTTPSRequest* thisRequest, int readyState);
void requestCB1(void* optParm, AsyncHTTPSRequest* thisRequest, int readyState);

void sendRequest0();
void sendRequest1();

typedef void (*requestCallback)(void* optParm, AsyncHTTPSRequest* thisRequest, int readyState);
typedef void (*sendCallback)();

requestCallback requestCB     [NUM_DIFFERENT_SITES] = { requestCB0,   requestCB1   };
sendCallback    sendRequestCB [NUM_DIFFERENT_SITES] = { sendRequest0, sendRequest1 };

Ticker ticker;
Ticker ticker1;

void heartBeatPrint()
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print(F("H"));        // H means connected to WiFi
  else
    Serial.print(F("F"));        // F means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void sendRequest(uint16_t index)
{
  static bool requestOpenResult;

  reqCount[index]--;
  readySend[index] = false;
  
  requestOpenResult = request[index].open("GET", addreses[index][reqCount[index]]);

  if (requestOpenResult)
  {
    // Only send() if open() returns true, or crash
    Serial.print("\nSending request: ");
    request[index].send();
  }
  else
  {
    Serial.print("\nCan't send bad request : ");
  }

  Serial.println(addreses[index][reqCount[index]]);
}

void sendRequest0()
{
  sendRequest(0);
}

void sendRequest1()
{
  sendRequest(1);
}

void sendRequests()
{
  for (int index = 0; index < NUM_DIFFERENT_SITES; index++)
  {
    reqCount[index] = 2;
  }
  reqCount[0] = NUM_ENTRIES_SITE_0;
  reqCount[1] = NUM_ENTRIES_SITE_1;
}

void requestCB0(void *optParm, AsyncHTTPSRequest *thisRequest, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    AHTTPS_LOGDEBUG0(F("\n**************************************\n"));
    AHTTPS_LOGDEBUG1(F("Response Code = "), thisRequest->responseHTTPString());

    if (thisRequest->responseHTTPcode() == 200)
    {
      Serial.println(F("\n**************************************"));
      Serial.println(thisRequest->responseText());
      Serial.println(F("**************************************"));
    }

    thisRequest->setDebug(false);
    readySend[0] = true;
  }
}

void requestCB1(void *optParm, AsyncHTTPSRequest *thisRequest, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    AHTTPS_LOGDEBUG0(F("\n**************************************\n"));
    AHTTPS_LOGDEBUG1(F("Response Code = "), thisRequest->responseHTTPString());

    if (thisRequest->responseHTTPcode() == 200)
    {
      Serial.println(F("\n**************************************"));
      Serial.println(thisRequest->responseText());
      Serial.println(F("**************************************"));
    }

    thisRequest->setDebug(false);
    readySend[1] = true;
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  delay(200);

  Serial.print("\nStarting AsyncHTTPSRequest_ESP_Multi on ");  Serial.println(ARDUINO_BOARD);

#if defined(ESP32)
  Serial.println(ASYNC_TCP_SSL_VERSION);
#else
  //Serial.println(ESPASYNC_TCP_SSL_VERSION);
#endif

  Serial.println(ASYNC_HTTPS_REQUEST_GENERIC_VERSION);

#if defined(ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN)
  if (ASYNC_HTTPS_REQUEST_GENERIC_VERSION_INT < ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN)
  {
    Serial.print(F("Warning. Must use this example on Version equal or later than : "));
    Serial.println(ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN_TARGET);
  }
#endif

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi SSID: " + String(ssid));

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print(F("\nAsyncHTTPSRequest @ IP : "));
  Serial.println(WiFi.localIP());

  for (int index = 0; index < NUM_DIFFERENT_SITES; index++)
  {
    request[index].setDebug(false);

    request[index].onReadyStateChange(requestCB[index]); 
  }

  ticker.attach(HTTPS_REQUEST_INTERVAL, sendRequests);

  ticker1.attach(HEARTBEAT_INTERVAL, heartBeatPrint);
}

void loop()
{
  for (int index = 0; index < NUM_DIFFERENT_SITES; index++)
  {
    if ((reqCount[index] > 0) && readySend[index])
    {
      sendRequestCB[index]();

      // Don't reduce this or possible crash. TLS needs long time to work.
      delay(100);
    }
  }
}
