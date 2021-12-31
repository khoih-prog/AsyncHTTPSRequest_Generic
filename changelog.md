# AsyncHTTPSRequest_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncHTTPSRequest_Generic.svg?)](https://www.ardu-badge.com/AsyncHTTPSRequest_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncHTTPSRequest_Generic.svg)](https://github.com/khoih-prog/AsyncHTTPSRequest_Generic/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncHTTPSRequest_Generic.svg)](http://github.com/khoih-prog/AsyncHTTPSRequest_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

---
---


## Changelog

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


