#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 
#include <espnow.h>

#define NO_OF_NODE_SENSOR             3

typedef struct Struct_Command{
  unsigned char node_id;
  unsigned char actuator_index;
  unsigned char value;
} Struct_Command;

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

// Create web server
extern ESP8266WebServer WebServer;

// Data receive from sensor, node
extern Struct_Data_Node _data_node; 

// Command receive from server
extern Struct_Command _command;

// Buffer node for lcd display
extern Struct_Data_Node _data_lcd_buffer[];

// REPLACE WITH THE MAC Address of your receiver 
extern uint8_t Broadcast_Address[][6];

extern unsigned char node_turn_for_lcd_display;

// time counter for striggering event
extern unsigned int _display_time;
extern unsigned int _time_call_FSM_data;

// flag send data to server and send command to node
extern bool _flag_send_data_sv, _flag_send_data_node;

// flag wifi name and pass selected  in webserver
extern bool _flag_wf_selected;

// flag for mode view lcd
extern bool _flag_special_mode_lcd;

// wifi name and pass
extern String _wifi_name, _wifi_pass;

// auto counter for task needing duration
extern unsigned char _counter_time;
#endif