#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "timer.h"
#include "global.h"
#include "wifi.h"
#include "MQTT_server.h"
#include "lcd.h"
#include "fsm.h"
#include "input.h"

#define SERIAL_DEBUG_BAUD   9600


void setup() {
  // put your setup code here, to run once:

  EEPROM.begin(512);

  Serial.begin(SERIAL_DEBUG_BAUD);
  WF_Init();
  SV_Init();
  FSM_Init();
  IN_Init();
  LCD_Init();
  TMR1_Init(50);
  
  TMR1_SetTime_ms(50); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(timer1_flag){
    timer1_flag = 0;

    IN_ButtonReading();
    
    if(_display_time >= 5) _display_time -= 5;
    if(_time_call_FSM_data >= 5) _time_call_FSM_data -= 5;
    
    if(_counter_time > 250) _counter_time = 0;
    else _counter_time += 1;

    FSM_WifiControl();
    FSM_DataControl();
    FSM_LcdControl();
    
    LCD_DisplayScreen();
  }
  
  client.loop();
  WebServer.handleClient();
}
