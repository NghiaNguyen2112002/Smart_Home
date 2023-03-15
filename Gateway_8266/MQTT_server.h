#ifndef __MQTT_SERVER_H__
#define __MQTT_SERVER_H__

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 

#include "global.h"

// Thingsboard server is used in this library//
#define SERVER_PASS                         "NcLZaxMKfNR0N61P8RpMuEhG"
#define SERVER_DOMAIN                       "mqtt3.thingspeak.com"
#define SERVER_USER                         "MDUYFQcfGxgSLjYlIjw3DTc"

#define CLIENT_ID                           "MDUYFQcfGxgSLjYlIjw3DTc"

#define TIME_RECONNECTION_THINGSBOARD       500                     //5000 ms

//==========CHANNEL PUBLISH===========//
// #define CHANNEL_REQUEST_DATA                  "v1/devices/me/attributes/request/1"
// #define CHANNEL_STORE_DATA                    "v1/devices/me/attributes"


void SV_Init(void);
void SV_CheckConnection(void);
void SV_SendData(char* channel, char* json_string);

#endif