#ifndef __GLOBAL_H__
#define __GLOBAL_H__


// #include <ThingsBoard.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
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

// Create a struct
extern Struct_Data_Node _data_node; 



// REPLACE WITH THE MAC Address of your receiver 
extern uint8_t Broadcast_Address[];




#endif