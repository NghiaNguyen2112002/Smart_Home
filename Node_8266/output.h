#ifndef __INC_OUT_H__
#define __INC_OUT_H__

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "input.h"

// static const uint8_t D0   = 16;
// static const uint8_t D1   = 5;
// static const uint8_t D2   = 4;
// static const uint8_t D3   = 0;
// static const uint8_t D4   = 2;
// static const uint8_t D5   = 14;
// static const uint8_t D6   = 12;
// static const uint8_t D7   = 13;
// static const uint8_t D8   = 15;
// static const uint8_t D9   = 3;
// static const uint8_t D10  = 1;

#define NO_OF_RELAYS                      2
#define PIN_RELAY_1                       D3
#define PIN_RELAY_2                       D4


void OUT_Init(void);
bool OUT_IsRelayOn(unsigned char index);
void OUT_TurnRelayOn(unsigned char index);
void OUT_TurnRelayOff(unsigned char index);
void OUT_TuggleRelay(unsigned char index);

#endif