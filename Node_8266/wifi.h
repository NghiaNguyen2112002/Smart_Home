#ifndef __INC_WIFI_CONNECTION_H__
#define __INC_WIFI_CONNECTION_H__


#include <ESP8266WiFi.h>
#include <espnow.h>

#include "global.h"

#define WIFI_NAME                 "GATEWAY"
#define WIFI_PASSWORD             "123456789"

void WF_Init(void);
void WF_CheckConnection(void);
void WF_SendDataEspnow(char* address_node, char* data);
void WF_Reconnect(void);
bool WF_IsConnected(void);

#endif