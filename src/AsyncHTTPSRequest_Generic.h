/****************************************************************************************************************************
  AsyncHTTPSRequest_Generic.h
  
  For ESP32, ESP8266 and STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
  AsyncHTTPSRequest is a library for the ESP8266, ESP32 and currently STM32 run built-in Ethernet WebServer
  
  Based on and modified from AsyncHTTPRequest Library (https://github.com/boblemaire/asyncHTTPrequest)
  
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncHTTPSRequest_Generic
  
  Copyright (C) <2018>  <Bob Lemaire, IoTaWatt, Inc.>
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.  
 
  Version: 1.4.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     21/10/2021 Initial coding to support only ESP32
  1.1.0    K Hoang     23/10/2021 Add support to ESP32-based WT32-ETH01 using LAN8720
  1.1.1    K Hoang     29/11/2021 Auto detect ESP32 core version and improve connection time for WT32_ETH01
  1.2.0    K Hoang     30/12/2021 Fix `multiple-definitions` linker error
  1.3.0    K Hoang     23/01/2022 Enable compatibility with old code to include only AsyncHTTPSRequest_Generic.h
  1.4.0    K Hoang     11/02/2022 Add support to new ESP32-S3. Add LittleFS support to ESP32-C3. Use core LittleFS
  1.4.1    K Hoang     25/02/2022 Add example AsyncHTTPSRequest_ESP_Multi to demo connection to multiple addresses
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNC_HTTPS_REQUEST_GENERIC_H
#define ASYNC_HTTPS_REQUEST_GENERIC_H

#include "AsyncHTTPSRequest_Generic.hpp"
#include "AsyncHTTPSRequest_Impl_Generic.h"

#endif    // ASYNC_HTTPS_REQUEST_GENERIC_H
