# AsyncHTTPSRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPSRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPSRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPSRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPSRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Change from v2.0.0](#Important-Change-from-v200)
* [Important Change from v1.3.0](#Important-Change-from-v130)
* [Why do we need the new Async AsyncHTTPSRequest_Generic library](#why-do-we-need-this-async-AsyncHTTPSRequest_Generic-library)
  * [Important notes for WT32_ETH01](#Important-notes-for-WT32_ETH01)
  * [Features](#features)
  * [Supports](#supports)
  * [Principles of operation](#principles-of-operation)
  * [Currently supported Boards](#currently-supported-boards)
  * [To be supported boards in the future](#To-be-supported-boards-in-the-future)
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
    * [3. AsyncHTTPSRequest_ESP_Multi](examples/AsyncHTTPSRequest_ESP_Multi) **New**
    * [4. AsyncHTTP_HTTPSRequest_ESP](examples/AsyncHTTP_HTTPSRequest_ESP) **New**
  * [For WT32_ETH01](#for-WT32_ETH01)
    * [1. AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01)
  * [For ESP32 or WT32_ETH01](#for-esp32-or-WT32_ETH01) 
    * [1. multiFileProject](examples/multiFileProject)
* [Example AsyncHTTP_HTTPSRequest_ESP](#example-AsyncHTTP_HTTPSRequest_ESP)
* [Debug Terminal Output Samples](#debug-terminal-output-samples) 
  * [ 1. AsyncHTTPSRequest_ESP on ESP32_DEV](#1-AsyncHTTPSRequest_ESP-on-ESP32_DEV)
  * [ 2. AsyncHTTPSRequest_ESP on ESP32S2_DEV](#2-AsyncHTTPSRequest_ESP-on-ESP32S2_DEV)
  * [ 3. AsyncHTTPSRequest_ESP on ESP32C3_DEV](#3-AsyncHTTPSRequest_ESP-on-ESP32C3_DEV)
  * [ 4. AsyncHTTPSRequest_ESP_WiFiManager on ESP32_DEV](#4-AsyncHTTPSRequest_ESP_WiFiManager-on-ESP32_DEV)
  * [ 5. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v2.0.0](#5-AsyncHTTPSRequest_WT32_ETH01-on-WT32_ETH01-using-ESP32-core-v200)
  * [ 6. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v1.0.6](#6-AsyncHTTPSRequest_WT32_ETH01-on-WT32_ETH01-using-ESP32-core-v106)
  * [ 7. AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32C3_DEV](#7-AsyncHTTPSRequest_ESP_WiFiManager-using-LittleFS-on-ESP32C3_DEV)
  * [ 8. AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32S3_DEV](#8-AsyncHTTPSRequest_ESP_WiFiManager-using-LittleFS-on-ESP32S3_DEV)
  * [ 9. AsyncHTTPSRequest_ESP_Multi on ESP32_DEV](#9-AsyncHTTPSRequest_ESP_Multi-on-ESP32_DEV) **New**
  * [10. AsyncHTTP_HTTPSRequest_ESP on ESP32_DEV](#10-AsyncHTTP_HTTPSRequest_ESP-on-ESP32_DEV) **New**
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

### Important Change from v2.0.0

**Breaking change to permit coexisting with AsyncHTTPRequest library. Now you can send HTTP / HTTPS requests to multiple addresses and receive responses from them.**

### Important Change from v1.3.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)


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

1. Asynchronous HTTPS Request library for **ESP32, ESP32_S2, ESP32_C3, ESP32_S3** using built-in WiFi or **WT32_ETH01** using either WiFi of built-in LAN8720 Ethernet
2. Providing a subset of HTTPS.
3. Relying on [`AsyncTCP_SSL` library](https://github.com/khoih-prog/AsyncTCP_SSL) for ESP32
4. Methods similar in format and usage to `XmlHTTPrequest` in Javascript.
5. Coexist with `AsyncHTTPRequest` library to permit sending `HTTP / HTTPS` requests to multiple addresses and receive responses from them

### Supports

1. **GET, POST, PUT, PATCH, DELETE and HEAD**
2. Request and response headers
3. Chunked response
4. Single String response for short (<~5K) responses (heap permitting).
5. Optional onData callback.
6. Optional onReadyStatechange callback.

---

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

#### 1. ESP32 including ESP32_S2 (ESP32_S2 Saola, AI-Thinker ESP-12K, etc.), ESP32_S3 and ESP32_C3

1. **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.) using EEPROM, SPIFFS or LittleFS**.
2. **ESP32-C3 (ARDUINO_ESP32C3_DEV) using EEPROM, SPIFFS or LittleFS**.
3. **ESP32-S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.) using EEPROM, SPIFFS or LittleFS**.

#### 2. **WT32_ETH01** using ESP32-based boards and LAN8720 Ethernet

---

### To be supported boards in the future

1. **ESP8266**
2. **RP2040W using arduino-pico core**
3. **STM32 using built-in LAN8742A**
4. **Portenta_H7 using either Ethernet or built-in WiFi**


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ESP32 Core 2.0.4+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [Latest stable release ![Release Version](https://img.shields.io/github/release/espressif/arduino-esp32.svg?style=plastic)
 3. [`AsyncTCP_SSL v1.2.0+`](https://github.com/khoih-prog/AsyncTCP_SSL) for ESP32. [![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncTCP_SSL.svg)](https://github.com/khoih-prog/AsyncTCP_SSL/releases)
 4. [`WebServer_WT32_ETH01 v1.5.0+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) for ESP32-based WT32_ETH01 using **either ESP32 core v2.0.0+ or v1.0.6-**. [![GitHub release](https://img.shields.io/github/release/khoih-prog/WebServer_WT32_ETH01.svg)](https://github.com/khoih-prog/WebServer_WT32_ETH01/releases)
 5. [`ESPAsync_WiFiManager library v1.13.0+`](https://github.com/khoih-prog/ESPAsync_WiFiManager) for ESP32/ESP8266 using some examples. [![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/releases)
 6. [`AsyncHTTPRequest_Generic library v1.9.0+`](https://github.com/khoih-prog/AsyncHTTPRequest_Generic) for ESP32/ESP8266 using with [AsyncHTTP_HTTPSRequest_ESP example](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/tree/main/examples/AsyncHTTP_HTTPSRequest_ESP). [![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/releases)

---
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `AsyncHTTPSRequest_Generic`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPSRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPSRequest_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncHTTPSRequest_Generic](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic) page.
2. Download the latest release `AsyncHTTPSRequest_Generic-main.zip`.
3. Extract the zip file to `AsyncHTTPSRequest_Generic-main` directory 
4. Copy the whole `AsyncHTTPSRequest_Generic-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncHTTPSRequest_Generic** library](https://registry.platformio.org/libraries/khoih-prog/AsyncHTTPSRequest_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/AsyncHTTPSRequest_Generic/installation). Search for AsyncHTTPSRequest_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
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

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncHTTPSRequest_Generic.hpp"     //https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "AsyncHTTPSRequest_Generic.h"           //https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

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
 2. [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager)
 3. [AsyncHTTPSRequest_ESP_Multi](examples/AsyncHTTPSRequest_ESP_Multi) **New**
 4. [AsyncHTTP_HTTPSRequest_ESP](examples/AsyncHTTP_HTTPSRequest_ESP) **New**

#### For WT32_ETH01

 1. [AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01)
 
#### For ESP32 or WT32_ETH01

  1. [multiFileProject](examples/multiFileProject)
 
---

### Example [AsyncHTTP_HTTPSRequest_ESP](examples/AsyncHTTP_HTTPSRequest_ESP)

https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/blob/053554d15437de037438c1955c94d4f98ac7b7f0/examples/AsyncHTTP_HTTPSRequest_ESP/AsyncHTTP_HTTPSRequest_ESP.ino#L43-L381


---
---

### Debug Terminal Output Samples

#### 1. AsyncHTTPSRequest_ESP on ESP32_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP) on ESP32_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL).

```
21:38:45.215 -> Starting AsyncHTTPSRequest_ESP using ESP32_DEV
21:38:45.215 -> AsyncTCP_SSL v1.2.0
21:38:45.215 -> AsyncHTTPSRequest_Generic v2.1.0
21:38:45.348 -> Connecting to WiFi SSID: HueNet1
21:38:45.844 -> ....
21:38:47.335 -> AsyncHTTPSRequest @ IP : 192.168.2.186
21:38:48.727 -> [AHTTPS] _onError handler SSL error = OK
**************************************
[AHTTPS] Response Code =  HTTP OK

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:38:48.720807-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169128
utc_datetime: 2022-09-03T01:38:48.720807+00:00
utc_offset: -04:00
week_number: 35
**************************************
21:38:57.347 -> HHHHHH
**************************************
[AHTTPS] Response Code =  HTTP OK

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:39:47.331884-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169187
utc_datetime: 2022-09-03T01:39:47.331884+00:00
utc_offset: -04:00
week_number: 35
**************************************
```
---

#### 2. AsyncHTTPSRequest_ESP on ESP32S2_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP) on ESP32S2_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL).

```
Starting AsyncHTTPSRequest_ESP using ESP32S2_DEV
AsyncTCP_SSL v1.2.0
AsyncHTTPSRequest_Generic v2.1.0
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
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:38:48.720807-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169128
utc_datetime: 2022-09-03T01:38:48.720807+00:00
utc_offset: -04:00
week_number: 35
**************************************
HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:39:47.331884-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169187
utc_datetime: 2022-09-03T01:39:47.331884+00:00
utc_offset: -04:00
week_number: 35
**************************************
```

---

#### 3. AsyncHTTPSRequest_ESP on ESP32C3_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP](examples/AsyncHTTPSRequest_ESP) on ESP32C3_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL).

```
Starting AsyncHTTPSRequest_ESP using ESP32C3_DEV
AsyncTCP_SSL v1.2.0
AsyncHTTPSRequest_Generic v2.1.0
Connecting to WiFi SSID: HueNet1
.........
AsyncHTTPSRequest @ IP : 192.168.2.80
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:38:48.720807-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169128
utc_datetime: 2022-09-03T01:38:48.720807+00:00
utc_offset: -04:00
week_number: 35
**************************************
HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:39:47.331884-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169187
utc_datetime: 2022-09-03T01:39:47.331884+00:00
utc_offset: -04:00
week_number: 35
**************************************
```

---

#### 4. AsyncHTTPSRequest_ESP_WiFiManager on ESP32_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager) on ESP32_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL), and [ESPAsync_WiFiManager Library](https://github.com/khoih-prog/ESPAsync_WiFiManager)

```
Starting AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32_DEV
ESPAsync_WiFiManager v1.13.0
AsyncTCP_SSL v1.2.0
AsyncHTTPSRequest_Generic v2.1.0
Stored: SSID = HueNet1, Pass = 12345678
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 11.38 secs more in setup(), connection result is connected. Local IP: 192.168.2.232
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T22:15:12.862161-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662171312
utc_datetime: 2022-09-03T02:15:12.862161+00:00
utc_offset: -04:00
week_number: 35
**************************************
H
```

---

#### 5. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v2.0.0

Following is the debug terminal when running example [AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01) on WT32_ETH01 to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL) and **ESP32 core v2.0.0**

```
Starting AsyncHTTPSRequest_WT32_ETH01 using ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.5.0 for core v2.0.0+
AsyncTCP_SSL v1.2.0
AsyncHTTPSRequest_Generic v2.1.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.82, FULL_DUPLEX, 100Mbps

HTTP WebClient is @ IP : 192.168.2.82

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T22:15:12.862161-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662171312
utc_datetime: 2022-09-03T02:15:12.862161+00:00
utc_offset: -04:00
week_number: 35
**************************************
```

---

#### 6. AsyncHTTPSRequest_WT32_ETH01 on WT32_ETH01 using ESP32 core v1.0.6

Following is the debug terminal when running example [AsyncHTTPSRequest_WT32_ETH01](examples/WT32_ETH01/AsyncHTTPSRequest_WT32_ETH01) on WT32_ETH01 to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL) and **ESP32 core v1.0.6**

```
Starting AsyncHTTPSRequest_WT32_ETH01 using ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.5.0 for core v1.0.6-
AsyncTCP_SSL v1.2.0
AsyncHTTPSRequest_Generic v2.1.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps

HTTP WebClient is @ IP : 192.168.2.232
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T22:15:12.862161-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662171312
utc_datetime: 2022-09-03T02:15:12.862161+00:00
utc_offset: -04:00
week_number: 35
**************************************
```

---


#### 7. AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32C3_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager) on ESP32C3_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL), and [ESPAsync_WiFiManager Library](https://github.com/khoih-prog/ESPAsync_WiFiManager)

```
Starting AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32C3_DEV
ESPAsync_WiFiManager v1.13.0
AsyncHTTPSRequest_Generic v2.1.0
Stored: SSID = HueNet1, Pass = password
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 8.75 secs more in setup(), connection result is connected. Local IP: 192.168.2.85
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:38:48.720807-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169128
utc_datetime: 2022-09-03T01:38:48.720807+00:00
utc_offset: -04:00
week_number: 35
**************************************
HHHHHH
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T21:39:47.331884-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662169187
utc_datetime: 2022-09-03T01:39:47.331884+00:00
utc_offset: -04:00
week_number: 35
**************************************
HH
```

---


#### 8. AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32S3_DEV

Following is the debug terminal when running example [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager) on ESP32S3_DEV to demonstrate the operation of SSL Async HTTPS request, using [AsyncTCP_SSL Library](https://github.com/khoih-prog/AsyncTCP_SSL), and [ESPAsync_WiFiManager Library](https://github.com/khoih-prog/ESPAsync_WiFiManager)

```
Starting AsyncHTTPSRequest_ESP_WiFiManager using LittleFS on ESP32S3_DEV
ESPAsync_WiFiManager v1.13.0
AsyncHTTPSRequest_Generic v2.1.0
Stored: SSID = HueNet1, Pass = password
Got stored Credentials. Timeout 120s
ConnectMultiWiFi in setup
After waiting 8.26 secs more in setup(), connection result is connected. Local IP: 192.168.2.83
H
**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T22:15:12.862161-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662171312
utc_datetime: 2022-09-03T02:15:12.862161+00:00
utc_offset: -04:00
week_number: 35
**************************************
HHHH
```

---


#### 9. AsyncHTTPSRequest_ESP_Multi on ESP32_DEV

The terminal output of [AsyncHTTPSRequest_ESP_Multi example](examples/AsyncHTTPSRequest_ESP_Multi) running on `ESP32_DEV` to demonstrate how to send requests to multiple addresses and receive responses from them. 

```
Starting AsyncHTTPSRequest_ESP_Multi on ESP32_DEV
AsyncTCP_SSL v1.2.0
AsyncHTTPSRequest_Generic v2.1.0
Connecting to WiFi SSID: HueNet1
...
AsyncHTTPSRequest @ IP : 192.168.2.186

Sending request: https://worldtimeapi.org/api/timezone/Europe/Prague.txt

Sending request: https://www.myexternalip.com/raw
[AHTTPS] _onError handler SSL error = OK

**************************************
[AHTTPS] Response Code =  HTTP OK

**************************************
abbreviation: CEST
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-03T04:15:12.762149+02:00
day_of_week: 6
day_of_year: 246
dst: true
dst_from: 2022-03-27T01:00:00+00:00
dst_offset: 3600
dst_until: 2022-10-30T01:00:00+00:00
raw_offset: 3600
timezone: Europe/Prague
unixtime: 1662171312
utc_datetime: 2022-09-03T02:15:12.762149+00:00
utc_offset: +02:00
week_number: 35
**************************************

Sending request: https://worldtimeapi.org/api/timezone/America/Toronto.txt

**************************************
[AHTTPS] Response Code =  HTTP OK

**************************************
abbreviation: EDT
client_ip: aaa.bbb.ccc.ddd
datetime: 2022-09-02T22:15:12.862161-04:00
day_of_week: 5
day_of_year: 245
dst: true
dst_from: 2022-03-13T07:00:00+00:00
dst_offset: 3600
dst_until: 2022-11-06T06:00:00+00:00
raw_offset: -18000
timezone: America/Toronto
unixtime: 1662171312
utc_datetime: 2022-09-03T02:15:12.862161+00:00
utc_offset: -04:00
week_number: 35
**************************************
[AHTTPS] _onError handler SSL error = OK

**************************************
[AHTTPS] Response Code =  HTTP OK

**************************************
aaa.bbb.ccc.ddd
**************************************
H
```

---


#### 10. AsyncHTTP_HTTPSRequest_ESP on ESP32_DEV

The terminal output of [AsyncHTTP_HTTPSRequest_ESP example](examples/AsyncHTTP_HTTPSRequest_ESP) running on `ESP32_DEV` to demonstrate how to send HTTP and HTTPS requests to multiple addresses and receive responses from them. 

```
21:49:19.090 -> Starting AsyncHTTP_HTTPSRequest_ESP on ESP32_DEV
21:49:19.090 -> AsyncTCP_SSL v1.2.0
21:49:19.090 -> AsyncHTTPSRequest_Generic v2.1.0
21:49:19.090 -> AsyncHTTPRequest_Generic v1.9.0
21:49:19.190 -> Connecting to WiFi SSID: HueNet1
21:49:19.686 -> ...
21:49:20.713 -> AsyncHTTPSRequest @ IP : 192.168.2.186
21:49:20.713 -> 
21:49:20.713 -> Sending HTTPS request: https://worldtimeapi.org/api/timezone/Europe/Prague.txt
21:49:21.907 -> 
21:49:21.907 -> Sending HTTP request: http://worldtimeapi.org/api/timezone/America/Vancouver.txt
21:49:21.907 -> [AHTTPS] _onError handler SSL error = OK
21:49:21.940 -> 
21:49:21.940 -> **************************************
21:49:21.940 -> abbreviation: PDT
21:49:21.940 -> client_ip: aaa.bbb.ccc.ddd
21:49:21.940 -> datetime: 2022-09-02T18:49:21.890939-07:00
21:49:21.940 -> day_of_week: 5
21:49:21.940 -> day_of_year: 245
21:49:21.940 -> dst: true
21:49:21.940 -> dst_from: 2022-03-13T10:00:00+00:00
21:49:21.940 -> dst_offset: 3600
21:49:21.940 -> dst_until: 2022-11-06T09:00:00+00:00
21:49:21.973 -> raw_offset: -28800
21:49:21.973 -> timezone: America/Vancouver
21:49:21.973 -> unixtime: 1662169761
21:49:21.973 -> utc_datetime: 2022-09-03T01:49:21.890939+00:00
21:49:21.973 -> utc_offset: -07:00
21:49:21.973 -> week_number: 35
21:49:21.973 -> **************************************
21:49:21.973 -> 
21:49:21.973 -> **************************************
21:49:21.973 -> [AHTTPS] Response Code =  HTTP OK
21:49:21.973 -> 
21:49:21.973 -> **************************************
21:49:21.973 -> abbreviation: CEST
21:49:21.973 -> client_ip: aaa.bbb.ccc.ddd
21:49:21.973 -> datetime: 2022-09-03T03:49:21.903031+02:00
21:49:21.973 -> day_of_week: 6
21:49:21.973 -> day_of_year: 246
21:49:21.973 -> dst: true
21:49:21.973 -> dst_from: 2022-03-27T01:00:00+00:00
21:49:21.973 -> dst_offset: 3600
21:49:21.973 -> dst_until: 2022-10-30T01:00:00+00:00
21:49:22.006 -> raw_offset: 3600
21:49:22.006 -> timezone: Europe/Prague
21:49:22.006 -> unixtime: 1662169761
21:49:22.006 -> utc_datetime: 2022-09-03T01:49:21.903031+00:00
21:49:22.006 -> utc_offset: +02:00
21:49:22.006 -> week_number: 35
21:49:22.006 -> **************************************
21:49:22.006 -> 
21:49:22.006 -> Sending HTTP request: http://www.myexternalip.com/raw
21:49:22.105 -> 
21:49:22.105 -> **************************************
21:49:22.105 -> aaa.bbb.ccc.ddd
21:49:22.105 -> **************************************
21:49:22.105 -> 
21:49:22.105 -> Sending HTTPS request: https://worldtimeapi.org/api/timezone/America/Toronto.txt
21:49:22.138 -> 
21:49:22.138 -> **************************************
21:49:22.138 -> [AHTTPS] Response Code =  HTTP OK
21:49:22.138 -> 
21:49:22.138 -> **************************************
21:49:22.138 -> abbreviation: EDT
21:49:22.138 -> client_ip: aaa.bbb.ccc.ddd
21:49:22.138 -> datetime: 2022-09-02T21:49:22.102346-04:00
21:49:22.138 -> day_of_week: 5
21:49:22.138 -> day_of_year: 245
21:49:22.138 -> dst: true
21:49:22.138 -> dst_from: 2022-03-13T07:00:00+00:00
21:49:22.172 -> dst_offset: 3600
21:49:22.172 -> dst_until: 2022-11-06T06:00:00+00:00
21:49:22.172 -> raw_offset: -18000
21:49:22.172 -> timezone: America/Toronto
21:49:22.172 -> unixtime: 1662169762
21:49:22.172 -> utc_datetime: 2022-09-03T01:49:22.102346+00:00
21:49:22.172 -> utc_offset: -04:00
21:49:22.172 -> week_number: 35
21:49:22.172 -> **************************************
21:49:22.205 -> 
21:49:22.205 -> Sending HTTP request: http://worldtimeapi.org/api/timezone/Europe/London.txt
21:49:22.238 -> 
21:49:22.238 -> **************************************
21:49:22.238 -> abbreviation: BST
21:49:22.238 -> client_ip: aaa.bbb.ccc.ddd
21:49:22.238 -> datetime: 2022-09-03T02:49:22.199791+01:00
21:49:22.238 -> day_of_week: 6
21:49:22.238 -> day_of_year: 246
21:49:22.238 -> dst: true
21:49:22.238 -> dst_from: 2022-03-27T01:00:00+00:00
21:49:22.238 -> dst_offset: 3600
21:49:22.238 -> dst_until: 2022-10-30T01:00:00+00:00
21:49:22.271 -> raw_offset: 0
21:49:22.271 -> timezone: Europe/London
21:49:22.271 -> unixtime: 1662169762
21:49:22.271 -> utc_datetime: 2022-09-03T01:49:22.199791+00:00
21:49:22.271 -> utc_offset: +01:00
21:49:22.271 -> week_number: 35
21:49:22.271 -> **************************************
21:49:30.692 -> H
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
#define _ASYNC_HTTPS_LOGLEVEL_          2
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the `ESP32 / ESP8266 / STM32` core for Arduino.

Sometimes, the library will only work if you update the `ESP32 / ESP8266 / STM32` core to the latest version because I am using newly added functions.

---

### Issues ###

Submit issues to: [AsyncHTTPSRequest_Generic issues](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues)

---
---

## TO DO

 1. Fix bug. Add enhancement
 2. Add support to more Ethernet / WiFi shields
 3. Add support to RP2040W, ESP8266, Portenta_H7, STM32 and many more boards
 4. Add many more examples.
 
 ---

## DONE

 1. Initially add support to ESP32 using built-in WiFi
 2. Support `breaking` ESP32 core v2.0.0+ as well as v1.0.6-
 3. Auto detect ESP32 core v1.0.6- or v2.0.0+ to use correct settings
 4. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`.
 5. Enable compatibility with old code to include only `AsyncHTTPSRequest_Generic.h`
 6. Modify to be compatible with [AsyncTCP_SSL releases v1.2.0+](https://github.com/khoih-prog/AsyncTCP_SSL/releases/tag/v1.2.0)
 7. Add complex example [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager)
 8. Add support to **ESP32-S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.) using EEPROM, SPIFFS or LittleFS**
 9. Add `LittleFS` support to **ESP32-C3**
10. Use `ESP32-core's LittleFS` library instead of `Lorol's LITTLEFS` library for ESP32 core v2.0.0+
11. Add example [AsyncHTTPSRequest_ESP_Multi](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/tree/main/examples/AsyncHTTPSRequest_ESP_Multi) to demonstrate how to send requests to multiple addresses and receive responses from them.
12. Permit coexisting with AsyncHTTPRequest library to send and receive both HTTP and HTTPS
13. Add example [AsyncHTTP_HTTPSRequest_ESP](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/tree/main/examples/AsyncHTTP_HTTPSRequest_ESP) to demonstrate how to send HTTP and HTTPS requests to multiple addresses and receive responses from them.
14. Increase `DEFAULT_RX_TIMEOUT` to `30s` from `3s` for slower networks.
15. Fix long timeout if using bad or unreachable `IPAddress`
16. Display only successful `responseText` in examples
17. Improve debug messages by adding functions to display `error messages` instead of `cryptic error number`



---
---


### Contributions and Thanks

This library is based on, modified, bug-fixed and improved from:

1. [Bob Lemaire's **asyncHTTPrequest Library**](https://github.com/boblemaire/asyncHTTPrequest) to use the better **asynchronous** features of the following Async SSL TCP Libraries : ( [`AsyncTCP_SSL`](https://github.com/khoih-prog/AsyncTCP_SSL) ).
2. Thanks to [DavidAntonin](https://github.com/DavidAntonin) 
- to report [Cannot send requests to different addresses #4](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/4) leading to new release v1.4.1 to demonstrate how to send requests to multiple addresses and receive responses from them.
- to raise the idea and request enhancement [Pushover https post request #21](https://github.com/khoih-prog/AsyncHTTPRequest_Generic/issues/21) leading to new release v2.0.0 to permit coexisting with [AsyncHTTPRequest library](https://github.com/khoih-prog/AsyncHTTPRequest_Generic) to send and receive both HTTP and HTTPS.
3. Thanks to [Glenn West](https://github.com/glennswest) 
- to report and propose a fix in [No result from github https query #8](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/8) leading to new release v2.0.1 to increase `DEFAULT_RX_TIMEOUT` to `30s` from `3s` for slower networks


<table>
  <tr>
    <td align="center"><a href="https://github.com/boblemaire"><img src="https://github.com/boblemaire.png" width="100px;" alt="boblemaire"/><br /><sub><b>⭐️ Bob Lemaire</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/DavidAntonin"><img src="https://github.com/DavidAntonin.png" width="100px;" alt="DavidAntonin"/><br /><sub><b>David Antonin</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/glennswest"><img src="https://github.com/glennswest.png" width="100px;" alt="glennswest"/><br /><sub><b>Glenn West</b></sub></a><br /></td>
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

Copyright (C) 2021- Khoi Hoang



