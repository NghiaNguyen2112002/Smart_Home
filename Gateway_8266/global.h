#ifndef __GLOBAL_H__
#define __GLOBAL_H__


// #include <ThingsBoard.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 
#include <espnow.h>

#define NO_OF_NODE_SENSOR             3



typedef struct Struct_Data_Node{
  unsigned char node_id;
  float temp;
  float humid;
  int light_intensity;
  bool status_relay_0;
  bool status_relay_1;
} Struct_Data_Node;


// Create WF client
extern WiFiClient espClient;
// Create ThingsBoard instance
extern PubSubClient client;

// Create a struct
extern Struct_Data_Node _data_node; 

// Buffer node for lcd display
extern Struct_Data_Node _data_lcd_buffer;

// REPLACE WITH THE MAC Address of your receiver 
extern uint8_t Broadcast_Address_1[];
extern uint8_t Broadcast_Address_2[];

extern unsigned char node_turn_for_lcd_display;

// time counter for striggering event
extern unsigned int _display_time;
extern unsigned int _time_check_WF;


#endif