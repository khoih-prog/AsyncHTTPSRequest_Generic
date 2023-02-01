/****************************************************************************************************************************
  AsyncHTTPSRequest_ESP32_W6100.ino - Dead simple AsyncHTTPSRequest for ESP8266, ESP32 and currently STM32 with built-in LAN8742A Ethernet

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
// There are scores of ways to use AsyncHTTPRequest.  The important thing to keep in mind is that
// it is asynchronous and just like in JavaScript, everything is event driven.  You will have some
// reason to initiate an asynchronous HTTP request in your program, but then sending the request
// headers and payload, gathering the response headers and any payload, and processing
// of that response, can (and probably should) all be done asynchronously.
//
// In this example, a Ticker function is setup to fire every 300 seconds to initiate a request.
// Everything is handled in AsyncHTTPRequest without blocking.
// The callback onReadyStateChange is made progressively and like most JS scripts, we look for
// readyState == 4 (complete) here.  At that time the response is retrieved and printed.
//
// Note that there is no code in loop().  A code entered into loop would run oblivious to
// the ongoing HTTP requests.  The Ticker could be removed and periodic calls to sendRequest()
// could be made in loop(), resulting in the same asynchronous handling.
//
// For demo purposes, debug is turned on for handling of the first request.  These are the
// events that are being handled in AsyncHTTPRequest.  They all begin with Debug(nnn) where
// nnn is the elapsed time in milliseconds since the transaction was started.
//
//*************************************************************************************************************

#if !( defined(ESP32) )
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN_TARGET      "AsyncHTTPSRequest_Generic v2.5.0"
#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN             2005000

/////////////////////////////////////////////////////////

// Uncomment for certain HTTP site to optimize
//#define NOT_SEND_HEADER_AFTER_CONNECTED        true

// Use larger queue size if necessary for large data transfer. Default is 512 bytes if not defined here
//#define ASYNC_QUEUE_LENGTH     512

// Use larger priority if necessary. Default is 10 if not defined here. Must be > 4 or adjusted to 4
//#define CONFIG_ASYNC_TCP_PRIORITY   (12)

/////////////////////////////////////////////////////////

// Level from 0-4
#define ASYNC_HTTPS_DEBUG_PORT          Serial

#define _ASYNC_TCP_SSL_LOGLEVEL_        1
#define _ASYNC_HTTPS_LOGLEVEL_          2
#define _ETHERNET_WEBSERVER_LOGLEVEL_   1

// 300s = 5 minutes to not flooding
#define HTTPS_REQUEST_INTERVAL      60  //300

// 10s
#define HEARTBEAT_INTERVAL          10

// Uncomment to use ESP32 core v1.0.6-
//#define USING_CORE_ESP32_CORE_V200_PLUS     false

//////////////////////////////////////////////////////////

// Optional values to override default settings
// Don't change unless you know what you're doing
//#define ETH_SPI_HOST        SPI3_HOST
//#define SPI_CLOCK_MHZ       25

// Must connect INT to GPIOxx or not working
//#define INT_GPIO            4

//#define MISO_GPIO           19
//#define MOSI_GPIO           23
//#define SCK_GPIO            18
//#define CS_GPIO             5

//////////////////////////////////////////////////////////

#include <WebServer_ESP32_W6100.h>               // https://github.com/khoih-prog/WebServer_ESP32_W6100

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPSRequest_Generic.h>            // https://github.com/khoih-prog/AsyncHTTPSRequest_Generic

#include <Ticker.h>

AsyncHTTPSRequest request;
Ticker ticker;
Ticker ticker1;

/////////////////////////////////////////////

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

/////////////////////////////////////////////

void heartBeatPrint()
{
  static int num = 1;

  if (ESP32_W6100_isConnected())
    Serial.print(F("H"));        // H means connected
  else
    Serial.print(F("F"));        // F means not connected

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

void sendRequest()
{
  static bool requestOpenResult;

  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    //requestOpenResult = request.open("GET", "https://worldtimeapi.org/api/timezone/Europe/London.txt");
    requestOpenResult = request.open("GET", "https://worldtimeapi.org/api/timezone/America/Toronto.txt");

    if (requestOpenResult)
    {
      // Only send() if open() returns true, or crash
      request.send();
    }
    else
    {
      Serial.println(F("Can't send bad request"));
    }
  }
  else
  {
    Serial.println(F("Can't send request"));
  }
}

void requestCB(void *optParm, AsyncHTTPSRequest *request, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    AHTTPS_LOGDEBUG0(F("\n**************************************\n"));
    AHTTPS_LOGDEBUG1(F("Response Code = "), request->responseHTTPString());

    if (request->responseHTTPcode() == 200)
    {
      Serial.println(F("\n**************************************"));
      Serial.println(request->responseText());
      Serial.println(F("**************************************"));
    }

    request->setDebug(false);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(200);

  Serial.print(F("\nStarting AsyncHTTPSRequest_ESP32_W6100 using "));
  Serial.print(ARDUINO_BOARD);
  Serial.print(F(" with "));
  Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_ESP32_W6100_VERSION);
  Serial.println(ASYNC_TCP_SSL_VERSION);
  Serial.println(ASYNC_HTTPS_REQUEST_GENERIC_VERSION);

  Serial.setDebugOutput(true);

#if defined(ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN)

  if (ASYNC_HTTPS_REQUEST_GENERIC_VERSION_INT < ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN)
  {
    Serial.print(F("Warning. Must use this example on Version equal or later than : "));
    Serial.println(ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN_TARGET);
  }

#endif

  AHTTPS_LOGWARN(F("Default SPI pinout:"));
  AHTTPS_LOGWARN1(F("SPI_HOST:"), ETH_SPI_HOST);
  AHTTPS_LOGWARN1(F("MOSI:"), MOSI_GPIO);
  AHTTPS_LOGWARN1(F("MISO:"), MISO_GPIO);
  AHTTPS_LOGWARN1(F("SCK:"),  SCK_GPIO);
  AHTTPS_LOGWARN1(F("CS:"),   CS_GPIO);
  AHTTPS_LOGWARN1(F("INT:"),  INT_GPIO);
  AHTTPS_LOGWARN1(F("SPI Clock (MHz):"), SPI_CLOCK_MHZ);
  AHTTPS_LOGWARN(F("========================="));

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_W6100_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W6100_Mac = W6100_Default_Mac);
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[index] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  //ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_W6100_waitForConnect();

  ///////////////////////////////////

  Serial.print(F("\nHTTP WebClient is @ IP : "));
  Serial.println(ETH.localIP());

  request.setDebug(false);

  request.onReadyStateChange(requestCB);
  ticker.attach(HTTPS_REQUEST_INTERVAL, sendRequest);

  ticker1.attach(HEARTBEAT_INTERVAL, heartBeatPrint);

  // Send first request now
  sendRequest();
}

void loop()
{
}
