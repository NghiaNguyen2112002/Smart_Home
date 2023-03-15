#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include "timer.h"
#include "global.h"
#include "wifi.h"
#include "fsm.h"
#include "output.h"
#include "input.h"

#define SERIAL_DEBUG_BAUD   9600

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  WF_Init();
  FSM_Init();
  IN_Init();
  OUT_Init();
  TMR1_Init(50);
  
  TMR1_SetTime_ms(1000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(timer1_flag){
    timer1_flag = 0;
    FSM_DataProcessing();
  }
}
