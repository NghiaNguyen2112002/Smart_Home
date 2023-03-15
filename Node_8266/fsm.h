#ifndef __INC_FSM_H__
#define __INC_FSM_H__

#include <ESP8266WiFi.h>
#include <espnow.h>
#include "global.h"
#include "wifi.h"
#include "output.h"

//=============MODE FSM LCD============//
#define INIT                0
#define CONNECT_WIFI        1
#define READ_DATA           2
#define SEND_DATA           3

void FSM_Init(void);
void FSM_DataProcessing(void);


#endif