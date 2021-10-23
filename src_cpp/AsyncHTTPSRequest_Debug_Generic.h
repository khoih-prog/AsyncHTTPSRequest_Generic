/****************************************************************************************************************************
  AsyncHTTPSRequest_Debug_Generic.h
  
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
 
  Version: 1.0.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0    K Hoang     21/10/2021 Initial coding to support only ESP32
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNC_HTTPS_REQUEST_DEBUG_GENERIC_H
#define ASYNC_HTTPS_REQUEST_DEBUG_GENERIC_H

#ifdef ASYNC_HTTPS_DEBUG_PORT
  #define A_DBG_PORT      ASYNC_HTTPS_DEBUG_PORT
#else
  #define A_DBG_PORT      Serial
#endif

// Change _ASYNC_HTTPS_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ASYNC_HTTPS_LOGLEVEL_
  #define _ASYNC_HTTPS_LOGLEVEL_       0
#endif

/////////////////////////////////////////////////////////

const char AHTTPS_MARK[] = "[AHTTPS] ";

#define AHTTPS_PRINT_MARK   AHTTPS_PRINT(AHTTPS_MARK)
#define AHTTPS_PRINT_SP     A_DBG_PORT.print(" ")

#define AHTTPS_PRINT        A_DBG_PORT.print
#define AHTTPS_PRINTLN      A_DBG_PORT.println

/////////////////////////////////////////////////////////

#define AHTTPS_LOGERROR(x)         if(_ASYNC_HTTPS_LOGLEVEL_>0) { AHTTPS_PRINT_MARK; AHTTPS_PRINTLN(x); }
#define AHTTPS_LOGERROR0(x)        if(_ASYNC_HTTPS_LOGLEVEL_>0) { AHTTPS_PRINT(x); }
#define AHTTPS_LOGERROR1(x,y)      if(_ASYNC_HTTPS_LOGLEVEL_>0) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(y); }
#define AHTTPS_LOGERROR2(x,y,z)    if(_ASYNC_HTTPS_LOGLEVEL_>0) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(z); }
#define AHTTPS_LOGERROR3(x,y,z,w)  if(_ASYNC_HTTPS_LOGLEVEL_>0) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINT(z); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define AHTTPS_LOGWARN(x)          if(_ASYNC_HTTPS_LOGLEVEL_>1) { AHTTPS_PRINT_MARK; AHTTPS_PRINTLN(x); }
#define AHTTPS_LOGWARN0(x)         if(_ASYNC_HTTPS_LOGLEVEL_>1) { AHTTPS_PRINT(x); }
#define AHTTPS_LOGWARN1(x,y)       if(_ASYNC_HTTPS_LOGLEVEL_>1) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(y); }
#define AHTTPS_LOGWARN2(x,y,z)     if(_ASYNC_HTTPS_LOGLEVEL_>1) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(z); }
#define AHTTPS_LOGWARN3(x,y,z,w)   if(_ASYNC_HTTPS_LOGLEVEL_>1) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINT(z); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define AHTTPS_LOGINFO(x)          if(_ASYNC_HTTPS_LOGLEVEL_>2) { AHTTPS_PRINT_MARK; AHTTPS_PRINTLN(x); }
#define AHTTPS_LOGINFO0(x)         if(_ASYNC_HTTPS_LOGLEVEL_>2) { AHTTPS_PRINT(x); }
#define AHTTPS_LOGINFO1(x,y)       if(_ASYNC_HTTPS_LOGLEVEL_>2) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(y); }
#define AHTTPS_LOGINFO2(x,y,z)     if(_ASYNC_HTTPS_LOGLEVEL_>2) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(z); }
#define AHTTPS_LOGINFO3(x,y,z,w)   if(_ASYNC_HTTPS_LOGLEVEL_>2) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINT(z); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define AHTTPS_LOGDEBUG(x)         if(_ASYNC_HTTPS_LOGLEVEL_>3) { AHTTPS_PRINT_MARK; AHTTPS_PRINTLN(x); }
#define AHTTPS_LOGDEBUG0(x)        if(_ASYNC_HTTPS_LOGLEVEL_>3) { AHTTPS_PRINT(x); }
#define AHTTPS_LOGDEBUG1(x,y)      if(_ASYNC_HTTPS_LOGLEVEL_>3) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(y); }
#define AHTTPS_LOGDEBUG2(x,y,z)    if(_ASYNC_HTTPS_LOGLEVEL_>3) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(z); }
#define AHTTPS_LOGDEBUG3(x,y,z,w)  if(_ASYNC_HTTPS_LOGLEVEL_>3) { AHTTPS_PRINT_MARK; AHTTPS_PRINT(x); AHTTPS_PRINT_SP; AHTTPS_PRINT(y); AHTTPS_PRINT_SP; AHTTPS_PRINT(z); AHTTPS_PRINT_SP; AHTTPS_PRINTLN(w); }

/////////////////////////////////////////////////////////

#endif    // ASYNC_HTTPS_REQUEST_DEBUG_GENERIC_H

