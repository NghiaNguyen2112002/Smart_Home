#ifndef __INC_WIFI_CONNECTION_H__
#define __INC_WIFI_CONNECTION_H__


#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <espnow.h>

#include "global.h"
#include "MQTT_server.h"

#define WIFI_NAME                 "MANGDAYKTX H-518"
#define WIFI_PASSWORD             "20202024"

#define WIFI_GATEWAY_NAME        "GATEWAY"
#define WIFI_GATEWAY_PASS        "123456789"

#define TIME_CHECK_WF       300       //3s

void WF_Init(void);
bool WF_IsConnected(void);
void WF_Connect(String wifi_name, String wifi_pass);
void WF_Disconnect(void);
void WF_SendDataEspnow(char* address_node, char* data);
void WF_CreateWebserver(void);

#endif