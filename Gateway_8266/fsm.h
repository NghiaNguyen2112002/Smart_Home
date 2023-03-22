#ifndef __INC_FSM_H__
#define __INC_FSM_H__

#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

// #include <espnow.h>

#include "global.h"
#include "lcd.h"
#include "wifi.h"
#include "MQTT_server.h"
#include "input.h"

//=============MODE FSM LCD============//
#define INIT                        0
#define DISPLAY_DHT                 1
#define DISPLAY_LIGHT               2
#define DISPLAY_RELAY               3
#define DISPLAY_WIFI_STATE          4
#define DISPLAY_WF_CONF             5
#define TURN_NEXT_NODE              6


//=============MODE FSM DATA============//
// #define INIT                 0
#define CHECK_CONNECTION        1
#define READ_DATA_GATEWAY       2
#define TRANSFER_DATA           3
#define DATA_LCD_BUFFER         4


//=============MODE FSM WIFI============//
// #define INIT                 0
#define WIFI_CHECKCONNECTION    1
#define WIFI_CONFIG             2
#define WF_CONNECT              3

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

#define SCREEN_WIFI_CONNECTING_0        "CONNECTING  WIFI"
#define SCREEN_WIFI_CONNECTING_1        "                "

// #define SCREEN_WIFI_CONNECTED           " WIFI CONNECTED "

#define LCD_RELAY_STATE_ON                  "ON "
#define LCD_RELAY_STATE_OFF                 "OFF"

//==============TIME==================//
#define SCREEN_TIME                 300         //3000 ms for every screen
#define FSM_DATA_CONTROL_TIME       100         //1000 ms

//===========INDEX ON LCD============//
#define INDEX_CEL_SYMBOL            14
#define INDEX_LCD_NODE              0
#define INDEX_HUMID_VALUE           9
#define INDEX_TEMP_VALUE            9
#define INDEX_LIGHT_VALUE           10
#define INDEX_RELAY_STATE           13

void FSM_Init(void);
void FSM_LcdControl(void);
void FSM_DataControl(void);
void FSM_WifiControl(void);
#endif