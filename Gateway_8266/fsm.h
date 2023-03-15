#ifndef __INC_FSM_H__
#define __INC_FSM_H__


#include <ESP8266WiFi.h>

#include "global.h"
#include "lcd.h"

//=============MODE FSM LCD============//
#define INIT              0
#define DISPLAY_DHT       1
#define DISPLAY_LIGHT     2
#define DISPLAY_RELAY     3
#define DISPLAY_WF_CONF   4
#define TURN_NEXT_NODE    5

//=============LCD SCREEN=============//
#define SCREEN_INIT_0                   "   SMART HOME   "
#define SCREEN_INIT_1                   "                "

#define SCREEN_HUMID_TEMP_0             " .TEMP :       C"        //"1.TEMP : 30.3 *C"        
#define SCREEN_HUMID_TEMP_1             " .HUMI :      % "        //"1.HUMI : 50.0 % "

#define SCREEN_LIGHT_0                  " .LIGHT :       "        //"1.LIGHT : 20    " 
#define SCREEN_LIGHT_1                  "                "

#define SCREEN_RELAY_0                  " .RELAY 1 :     "        //"1.RELAY 1 :  ON  "
#define SCREEN_RELAY_1                  " .RELAY 2 :     "        //"1.RELAY 2 :  OFF "

#define SCREEN_CONFIG_WIFI_0            "  CONFIG  WIFI  "
#define SCREEN_CONFIG_WIFI_1            "                "   

#define LCD_RELAY_STATE_ON                  "ON "
#define LCD_RELAY_STATE_OFF                 "OFF"

//==============TIME==================//
#define SCREEN_TIME                 300         //3000 ms for every screen

//===========INDEX ON LCD============//
#define INDEX_CEL_SYMBOL            14
#define INDEX_LCD_NODE              0
#define INDEX_HUMID_VALUE           9
#define INDEX_TEMP_VALUE            9
#define INDEX_LIGHT_VALUE           10
#define INDEX_RELAY_STATE           13

void FSM_Init(void);
void FSM_LcdControl(void);


#endif