#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 
#include <SoftwareSerial.h>

#include "timer.h"
#include "global.h"
#include "wifi.h"
#include "MQTT_server.h"
#include "lcd.h"
#include "fsm.h"

#define SERIAL_DEBUG_BAUD   9600

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  WF_Init();
  // SV_Init();
  FSM_Init();
  LCD_Init();
  TMR1_Init(50);
  
  TMR1_SetTime_ms(50); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(timer1_flag){
    timer1_flag = 0;

    if(_time_check_WF >= 5) _time_check_WF -= 5;

    if(_time_check_WF == 0){
      _time_check_WF = TIME_CHECK_WF;
      WF_CheckConnection();
    }
    
    // SV_CheckConnection();

    if(_display_time >= 5) _display_time -= 5;
    
    FSM_LcdControl();

    LCD_DisplayScreen();
  }

  // // client.loop();

}
