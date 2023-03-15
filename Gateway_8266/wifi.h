#ifndef __INC_WIFI_CONNECTION_H__
#define __INC_WIFI_CONNECTION_H__


#include <ESP8266WiFi.h>
#include <espnow.h>

#include "global.h"
#include "MQTT_server.h"

#define WIFI_NAME                 "MANGDAYKTX H1-518"
#define WIFI_PASSWORD             "20202024"

#define WIFI_GATEWAY_NAME        "GATEWAY"
#define WIFI_GATEWAY_PASS        "123456789"

#define TIME_CHECK_WF       300       //3s

void WF_Init(void);
void WF_CheckConnection(void);
void WF_SendDataEspnow(char* address_node, char* data);


#endif