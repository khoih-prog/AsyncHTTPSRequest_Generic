# AsyncHTTPSRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPSRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPSRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPSRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPSRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues)

---
---

## Table of Contents

* [Important Breaking Change from v1.2.0](#Important-Breaking-Change-from-v120)
* [Why do we need the new Async AsyncHTTPSRequest_Generic library](#why-do-we-need-this-async-AsyncHTTPSRequest_Generic-library)
  * [Important notes for WT32_ETH01](#Important-notes-for-WT32_ETH01)
  * [Features](#features)
  * [Supports](#supports)
  * [Principles of operation](#principles-of-operation)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs) 
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Examples](#examples)
  * [For ESP32](#for-esp32)
    * [1. AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP)
    * [2. AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager)
  * [For WT32_ETH01](#for-WT32_ETH01)
    * [1. AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01)
* [Example AsyncHTTPSRequest_ESP](#example-AsyncHTTPSRequest_ESP)
  * [1. File AsyncHTTPSRequest_ESP.ino](#1-file-AsyncHTTPSRequest_ESPino)
* [Debug Terminal Output Samples](#debug-terminal-output-samples) 
  * [1. AsyncHTTPSRequest_ESP on ESP32_DEV](#1-AsyncHTTPSRequest_ESP-on-ESP32_DEV)
  * [2. AsyncHTTPSRequest_ESP on ESP32S2_DEV](#2-AsyncHTTPSRequest_ESP-on-ESP32S2_DEV)
  * [3. AsyncHTTPSRequest_ESP on ESP32C3_DEV](#3-AsyncHTTPSRequest_ESP-on-ESP32C3_DEV)
  * [4. AsyncHTTPSRequest_ESP_WiFiManager on ESP32_DEV](#4-AsyncHTTPSRequest_ESP_WiFiManager-on-ESP32_DEV)
  * [5. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v2.0.0](#5-AsyncHTTPSRequest_WT32_ETH01-on-WT32_ETH01-using-ESP32-core-v200)
  * [6. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v1.0.6](#6-AsyncHTTPSRequest_WT32_ETH01-on-WT32_ETH01-using-ESP32-core-v106)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License and credits](#license-and-credits)
* [Copyright](#copyright)

---
---

### Important Breaking Change from v1.2.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

From v1.2.0, you must use

```
#include <AsyncHTTPSRequest_Generic.h>           //https://github.com/khoih-prog/AsyncHTTPSRequest_Generic

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPSRequest_Impl_Generic.h>      // https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
```

instead of only

```
#include <AsyncHTTPRequest_Generic.h>           //https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
```


---
---

## Why do we need this Async [AsyncHTTPSRequest_Generic library](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic)

#### Important notes for WT32_ETH01

ESP32 Core v2.0.0+ introduces new enum breaking almost all `WT32_ETH01` codes written for core v1.0.6-.

It's really strange to define a breaking enum `arduino_event_id_t` in [**WiFiGeneric.h**#L36-L78](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiGeneric.h#L36-L78), compared to the old `system_event_id_t`, now placed in [**esp_event_legacy.h**#L29-L63](https://github.com/espressif/arduino-esp32/blob/master/tools/sdk/esp32/include/esp_event/include/esp_event_legacy.h#L29-L63)

It's better to preserve the old enum order and just adding new items **to do no harm to pre-2.0.0 codes**

- [**WebServer_WT32_ETH01** Releases v1.2.0-**](https://github.com/khoih-prog/WebServer_WT32_ETH01) to be used for EP32 core v1.0.6- only
- [**WebServer_WT32_ETH01** Releases v1.3.0+**](https://github.com/khoih-prog/WebServer_WT32_ETH01) can be used for either EP32 core v2.0.0+ or v1.0.6-. **Default is using core v2.0.0+**

To use with core v1.0.6-, just define in your sketch

```
#define USING_CORE_ESP32_CORE_V200_PLUS       false
```

- [**WebServer_WT32_ETH01** Releases v1.4.0+**](https://github.com/khoih-prog/WebServer_WT32_ETH01) can be used for either ESP32 core v2.0.0+ or v1.0.6-. **Autodetect core**

---

### Features

1. Asynchronous HTTPS Request library for ESP32, ESP32_S2, ESP32_C3 using built-in WiFi.
2. Providing a subset of HTTPS.
3. Relying on on [`AsyncTCP_SSL`](https://github.com/khoih-prog/AsyncTCP_SSL) for ESP32
4. Methods similar in format and usage to XmlHTTPrequest in Javascript.

### Supports

1. **GET, POST, PUT, PATCH, DELETE and HEAD**
2. Request and response headers
3. Chunked response
4. Single String response for short (<~5K) responses (heap permitting).
5. Optional onData callback.
6. Optional onReadyStatechange callback.

### Principles of operation

This library adds a simple HTTPS layer on top of the [**AsyncTCP_SSL** library](https://github.com/khoih-prog/AsyncTCP_SSL) to **facilitate REST communication from a Client to a Server**. The paradigm is similar to the XMLHttpRequest in Javascript, employing the notion of a ready-state progression through the transaction request.

**Synchronization can be accomplished using callbacks on ready-state change, a callback on data receipt, or simply polling for ready-state change**. Data retrieval can be incremental as received, or bulk retrieved when the transaction completes provided there is enough heap to buffer the entire response.

The underlying buffering uses a new xbuf class. It handles both character and binary data. Class xbuf uses a chain of small (64 byte) segments that are allocated and added to the tail as data is added and deallocated from the head as data is read, achieving the same result as a dynamic circular buffer limited only by the size of heap. The xbuf implements indexOf and readUntil functions.

For short transactions, buffer space should not be an issue. In fact, it can be more economical than other methods that use larger fixed length buffers. Data is acked when retrieved by the caller, so there is some limited flow control to limit heap usage for larger transfers.

Request and response headers are handled in the typical fashion.

Chunked responses are recognized and handled transparently.

This library is based on, modified from:

1. [Bob Lemaire's asyncHTTPrequest Library](https://github.com/boblemaire/asyncHTTPrequest)
2. [Khoi Hoang's AsyncHTTPRequest_Generic Library](https://github.com/khoih-prog/AsyncHTTPRequest_Generic)

---

### Currently Supported Boards

#### 1. ESP32 including ESP32_S2 and ESP32_C3
#### 2. ESP32-based WT32_ETH01 (ESP32_S1 + LAN8720)


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://www.arduino.cc/en/Main/Software)
 
 2. [`ESP32 Core 2.0.2+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [Latest stable release ![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32.svg?style=plastic)

 3. [`AsyncTCP_SSL v1.1.0+`](https://github.com/khoih-prog/AsyncTCP_SSL) for ESP32. [![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncTCP_SSL.svg)](https://github.com/khoih-prog/AsyncTCP_SSL/releases)
 4. [`WebServer_WT32_ETH01 v1.4.1+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) for ESP32-based WT32_ETH01 using **either ESP32 core v2.0.0+ or v1.0.6-**. [![GitHub release](https://img.shields.io/github/release/khoih-prog/WebServer_WT32_ETH01.svg)](https://github.com/khoih-prog/WebServer_WT32_ETH01/releases)
 5. [`ESPAsync_WiFiManager library v1.10.0+`](https://github.com/khoih-prog/ESPAsync_WiFiManager) for ESP32/ESP8266 using some examples. [![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/releases)

---
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `AsyncHTTPSRequest_Generic`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPSRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPSRequest_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncHTTPSRequest_Generic](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic) page.
2. Download the latest release `AsyncHTTPSRequest_Generic-master.zip`.
3. Extract the zip file to `AsyncHTTPSRequest_Generic-master` directory 
4. Copy the whole `AsyncHTTPSRequest_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncHTTPSRequest_Generic** library](https://platformio.org/lib/show/12969/AsyncHTTPSRequest_Generic) by using [Library Manager](https://platformio.org/lib/show/12969/AsyncHTTPSRequest_Generic/installation). Search for AsyncHTTPSRequest_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can use

```
#include <AsyncHTTPSRequest_Generic.h>      //https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
```

in many files. But be sure to use the following `#include <AsyncHTTPSRequest_Impl_Generic.h>` **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPSRequest_Impl_Generic.h> // https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
```

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)

---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.5+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### Examples

#### For ESP32

 1. [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP)

#### For WT32_ETH01

 1. [AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01)
 
 
 
---

### Example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP)

#### 1. File [AsyncHTTPSRequest_ESP.ino](examples/AsyncHTTPSRequest_ESP/AsyncHTTPSRequest_ESP.ino)

```cpp
#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN_TARGET      "AsyncHTTPSRequest_Generic v1.2.0"
#define ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN             1002000

// Level from 0-4
#define ASYNC_HTTPS_DEBUG_PORT      Serial

#define _ASYNC_TCP_SSL_LOGLEVEL_    1
#define _ASYNC_HTTPS_LOGLEVEL_      1

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

#include <AsyncHTTPSRequest_Generic.h>            // https://github.com/khoih-prog/AsyncHTTPSRequest_Generic

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <AsyncHTTPSRequest_Impl_Generic.h>       // https://github.com/khoih-prog/AsyncHTTPSRequest_Generic

#include <Ticker.h>

AsyncHTTPSRequest request;
Ticker ticker;
Ticker ticker1;

void heartBeatPrint(void)
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

void sendRequest()
{
  static bool requestOpenResult;

  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    //requestOpenResult = request.open("GET", "https://worldtimeapi.org/api/timezone/Europe/London.txt");
    //requestOpenResult = request.open("GET", "https://worldtimeapi.org/api/timezone/America/Toronto.txt");
    requestOpenResult = request.open("GET", "https://worldtimeapi.org/api/timezone/America/Toronto.txt");

    if (requestOpenResult)
    {
      // Only send() if open() returns true, or crash
      request.send();
    }
    else
    {
      Serial.println("Can't send bad request");
    }
  }
  else
  {
    Serial.println("Can't send request");
  }
}

void requestCB(void* optParm, AsyncHTTPSRequest* request, int readyState)
{
  (void) optParm;

  if (readyState == readyStateDone)
  {
    Serial.println("\n**************************************");
    Serial.println(request->responseText());
    Serial.println("**************************************");

    request->setDebug(false);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting AsyncHTTPSRequest_ESP using " + String(ARDUINO_BOARD));

#if defined(ESP32)
  Serial.println(ASYNC_TCP_SSL_VERSION);
#else
  //Serial.println(ESPASYNC_TCP_SSL_VERSION);
#endif

  Serial.println(ASYNC_HTTPS_REQUEST_GENERIC_VERSION);

#if defined(ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN)
  if (ASYNC_HTTPS_REQUEST_GENERIC_VERSION_INT < ASYNC_HTTPS_REQUEST_GENERIC_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
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

  request.setDebug(false);

  request.onReadyStateChange(requestCB);

  ticker.attach(HTTPS_REQUEST_INTERVAL, sendRequest);

  ticker1.attach(HEARTBEAT_INTERVAL, heartBeatPrint);

  // Send first request now
  sendRequest();
}

void loop()
{
  //delay(1);
}
```

---
---

### Debug Terminal Output Samples

#### 1. AsyncHTTPSRequest_ESP on ESP32_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP) on ESP32_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL).

```
Starting AsyncHTTPSRequest_ESP using ESP32_DEV
AsyncTCP_SSL v1.1.0
AsyncHTTPSRequest_Generic v1.2.0
Connecting to WiFi SSID: HueNet1
........
AsyncHTTPSRequest @ IP : 192.168.2.168

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T20:50:41.119790-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640915441
utc_datetime: 2021-12-31T01:50:41.119790+00:00
utc_offset: -05:00
week_number: 52
**************************************
HHHHHH
**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T20:51:39.491816-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640915499
utc_datetime: 2021-12-31T01:51:39.491816+00:00
utc_offset: -05:00
week_number: 52

```
---

#### 2. AsyncHTTPSRequest_ESP on ESP32S2_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP) on ESP32S2_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL).

```
Starting AsyncHTTPSRequest_ESP using ESP32S2_DEV
AsyncTCP_SSL v1.1.0
AsyncHTTPSRequest_Generic v1.2.0
Connecting to WiFi SSID: HueNet1
.......
AsyncHTTPSRequest @ IP : 192.168.2.79
[ATCP] _handle_async_event: LWIP_TCP_DNS = 0x3FFE4E24
[ATCP] _handle_async_event: LWIP_TCP_DNS, name = worldtimeapi.org , IP = 213.188.196.246
[ATCP] _handle_async_event: LWIP_TCP_CONNECTED = 0x3FFE4E24 0x3FFE5024
[ATCP] _handle_async_event: LWIP_TCP_CONNECTED =  0
[ATCP] _handle_async_event: LWIP_TCP_SENT = 0x3FFE5024
[ATCP] _sent: len = 305
[ATCP] _handle_async_event: LWIP_TCP_RECV = 0x3FFE5024
[ATCP] _recv: tot_len = 1436
[ATCP] _handle_async_event: LWIP_TCP_RECV = 0x3FFE5024
[ATCP] _recv: tot_len = 1436
[ATCP] _handle_async_event: LWIP_TCP_RECV = 0x3FFE5024
[ATCP] _recv: tot_len = 1242
[ATCP] _handle_async_event: LWIP_TCP_SENT = 0x3FFE5024
[ATCP] _sent: len = 107
[ATCP] _handle_async_event: LWIP_TCP_SENT = 0x3FFE5024
[ATCP] _sent: len = 6
[ATCP] _handle_async_event: LWIP_TCP_SENT = 0x3FFE5024
[ATCP] _sent: len = 45
[ATCP] _handle_async_event: LWIP_TCP_RECV = 0x3FFE5024
[ATCP] _recv: tot_len = 51
[ATCP] _handle_async_event: LWIP_TCP_SENT = 0x3FFE5024
[ATCP] _sent: len = 106
[ATCP] _handle_async_event: LWIP_TCP_RECV = 0x3FFE5024
[ATCP] _recv: tot_len = 1016

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T20:53:39.490856-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640915619
utc_datetime: 2021-12-31T01:53:39.490856+00:00
utc_offset: -05:00
week_number: 52
**************************************
```

---

#### 3. AsyncHTTPSRequest_ESP on ESP32C3_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP) on ESP32C3_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL).

```
Starting AsyncHTTPSRequest_ESP using ESP32C3_DEV
AsyncTCP_SSL v1.1.0
AsyncHTTPSRequest_Generic v1.2.0
Connecting to WiFi SSID: HueNet1
.........
AsyncHTTPSRequest @ IP : 192.168.2.80

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T20:58:39.493064-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640915919
utc_datetime: 2021-12-31T01:58:39.493064+00:00
utc_offset: -05:00
week_number: 52

**************************************
```

---

#### 4. AsyncHTTPSRequest_ESP_WiFiManager on ESP32_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager) on ESP32_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL), and [ESPAsync_WiFiManager Library](https://github.com/khoih-prog/ESPAsync_WiFiManager)

```
Starting AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32_DEV
ESPAsync_WiFiManager v1.10.0
AsyncTCP_SSL v1.1.0
AsyncHTTPSRequest_Generic v1.2.0
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 11.38 secs more in setup(), connection result is connected. Local IP: 192.168.2.232
H
**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T21:02:39.495006-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640916159
utc_datetime: 2021-12-31T02:02:39.495006+00:00
utc_offset: -05:00
week_number: 52

**************************************
H
```

---

#### 5. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v2.0.0

Following is the debug terminal when running example [AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01) on WT32_ETH01 to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL) and **ESP32 core v2.0.0**

```
Starting AsyncHTTPSRequest_WT32_ETH01 using ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
AsyncTCP_SSL v1.1.0
AsyncHTTPSRequest_Generic v1.2.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.82, FULL_DUPLEX, 100Mbps

HTTP WebClient is @ IP : 192.168.2.82

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T21:07:43.532333-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640916463
utc_datetime: 2021-12-31T02:07:43.532333+00:00
utc_offset: -05:00
week_number: 52

**************************************
```

---

#### 6. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v1.0.6

Following is the debug terminal when running example [AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01) on WT32_ETH01 to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL) and **ESP32 core v1.0.6**

```
Starting AsyncHTTPSRequest_WT32_ETH01 using ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v1.0.6-
AsyncTCP_SSL v1.1.0
AsyncHTTPSRequest_Generic v1.2.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps

HTTP WebClient is @ IP : 192.168.2.232

**************************************
abbreviation: EST
client_ip: aaa.bbb.ccc.ddd
datetime: 2021-12-30T21:04:39.498040-05:00
day_of_week: 4
day_of_year: 364
dst: false
dst_from: 
dst_offset: 0
dst_until: 
raw_offset: -18000
timezone: America/Toronto
unixtime: 1640916279
utc_datetime: 2021-12-31T02:04:39.498040+00:00
utc_offset: -05:00
week_number: 52

**************************************
```

---
---


### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
#define ASYNC_HTTP_DEBUG_PORT           Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_TCP_SSL_LOGLEVEL_        1
#define _ASYNC_HTTPS_LOGLEVEL_          1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP32 / ESP8266 / STM32` core for Arduino.

Sometimes, the library will only work if you update the `ESP32 / ESP8266 / STM32` core to the latest version because I am using newly added functions.

---

### Issues ###

Submit issues to: [AsyncHTTPSRequest_Generic issues](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues)

---

## TO DO

 1. Fix bug. Add enhancement
 2. Add support to more Ethernet / WiFi shields
 3. Add support to more boards.
 4. Add many more examples.


## DONE

 1. Initially add support to ESP32 using built-in WiFi
 2. Support breaking ESP32 core v2.0.0+ as well as v1.0.6-
 3. Auto detect ESP32 core v1.0.6- or v2.0.0+ to use correct settings

---
---


### Contributions and Thanks

This library is based on, modified, bug-fixed and improved from:

1. [Bob Lemaire's **asyncHTTPrequest Library**](https://github.com/boblemaire/asyncHTTPrequest) to use the better **asynchronous** features of these following Async TCP Libraries : ( [`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP), [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP), and [`STM32AsyncTCP`](https://github.com/philbowles/STM32AsyncTCP) ).


<table>
  <tr>
    <td align="center"><a href="https://github.com/boblemaire"><img src="https://github.com/boblemaire.png" width="100px;" alt="boblemaire"/><br /><sub><b>⭐️ Bob Lemaire</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License and credits ###

- The library is licensed under [GPLv3](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/blob/main/LICENSE)

---

## Copyright

Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>

Copyright 2021- Khoi Hoang



