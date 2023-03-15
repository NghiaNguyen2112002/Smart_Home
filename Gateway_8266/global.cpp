#include "global.h"

WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);

Struct_Data_Node _data_node = {0, 0, 0, 0, false, false};
Struct_Data_Node _data_lcd_buffer = {0, 30.4, 50.3, 87, false, true};


uint8_t Broadcast_Address_1[] = {0x48, 0x3F, 0xDA, 0x68, 0x13, 0xC5};
uint8_t Broadcast_Address_2[] = {0x48, 0x3F, 0xDA, 0x67, 0xB5, 0x0A};


unsigned char node_turn_for_lcd_display = 0;

unsigned int _display_time = 0;
unsigned int _time_check_WF = 0;
