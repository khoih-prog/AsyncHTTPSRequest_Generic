# AsyncHTTPSRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPSRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPSRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPSRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPSRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v2.2.0](#releases-v220)
  * [Releases v2.1.3](#releases-v213)
  * [Releases v2.1.2](#releases-v212)
  * [Releases v2.1.1](#releases-v211)
  * [Releases v2.1.0](#releases-v210)
  * [Releases v2.0.1](#releases-v201)
  * [Releases v2.0.0](#releases-v200)
  * [Releases v1.4.1](#releases-v141)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

---
---


## Changelog

### Releases v2.2.0

1. Fix crash when turn-on debug or start
2. Fix memory leak. Check [Having problemen with AsyncHTTPS memory leak #11](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/11) and [Update for memleak in AsyncHTTPSRequest_Impl_Generic.h #13](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/pull/13)

### Releases v2.1.3

1. Not try to reconnect to the same host:port after connected. Check [setReuse feature #12](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/12)

### Releases v2.1.2

1. Fix bug
2. Fix compiler error in some cases

### Releases v2.1.1

1. Fix ESP32 chipID for example `AsyncHTTPSRequest_ESP_WiFiManager`

### Releases v2.1.0

1. Fix long timeout if using bad or unreachable `IPAddress`
2. Optimize code
3. Display only successful `responseText` in examples
4. Improve debug messages by adding functions to display `error messages` instead of `cryptic error number`

### Releases v2.0.1

1. Increase `DEFAULT_RX_TIMEOUT` to `30s` from `3s` for slower networks. Check [No result from github https query #8](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues/8)


### Releases v2.0.0

1. Breaking change to permit coexisting with AsyncHTTPRequest library to send and receive both HTTP and HTTPS.
2. Add example [AsyncHTTP_HTTPSRequest_ESP](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/tree/main/examples/AsyncHTTP_HTTPSRequest_ESP) to demonstrate how to send HTTP and HTTPS requests to multiple addresses and receive responses from them.

### Releases v1.4.1

1. Add example [AsyncHTTPSRequest_ESP_Multi](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/tree/main/examples/AsyncHTTPSRequest_ESP_Multi) to demonstrate how to send requests to multiple addresses and receive responses from them.


### Releases v1.4.0

1. Add support to new `ESP32-S3` 
2. Add `LittleFS` support to `ESP32-C3`
3. Use ESP32-core's LittleFS library instead of Lorol's LITTLEFS library for v2.0.0+
4. Add complex example [AsyncHTTPSRequest_ESP_WiFiManager](examples/AsyncHTTPSRequest_ESP_WiFiManager)

### Releases v1.3.0

1. Reduce the breaking effect of v1.2.0 by enabling compatibility with old code to include only `AsyncHTTPSRequest_Generic.h`
2. Modify to be compatible with [AsyncTCP_SSL releases v1.2.0](https://github.com/khoih-prog/AsyncTCP_SSL/releases/tag/v1.2.0)
3. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.

### Releases v1.2.0

1. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`. Check [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)
2. Optimize library code by using `reference-passing` instead of `value-passing`
3. Update all examples

#### Releases v1.1.1

##### Warning: Releases v1.1.1+ can be used and autodetect ESP32 core v2.0.0+ or v1.0.6- for WT32_ETH01

1. Auto detect ESP32 core to use for WT32_ETH01
2. Fix bug in WT32_ETH01 examples to reduce connection time

### Releases v1.1.0

1. Add support to ESP32-based WT32_ETH01 using LAN8720 using either ESP32 core v1.0.6- or core v2.0.0+
2. Add example for WT32_ETH01

### Releases v1.0.0

1. Initial coding to support Async HTTPS to **ESP32, ESP32_S2 and ESP32_C3** using built-in WiFi


