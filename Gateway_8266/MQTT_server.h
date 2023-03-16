#ifndef __MQTT_SERVER_H__
#define __MQTT_SERVER_H__

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 

#include "global.h"

// Adafruit server is used in this library//
#define SERVER_PASS                         ""
#define SERVER_DOMAIN                       "broker.mqtt-dashboard.com"
#define SERVER_USER                         ""

#define CLIENT_ID                           "Gateway_8266"

#define TIME_RECONNECTION_THINGSBOARD       500                     //5000 ms

//==========CHANNEL===========//
#define CHANNEL_DATA                             "smart_home_data"
#define CHANNEL_COMMAND                          "smart_home_command"

void SV_Init(void);
void SV_Connect(void);
bool SV_IsConnected(void);
void SV_SendData(char* channel, char* json_string);

#endif