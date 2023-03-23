#include "global.h"

WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);
ESP8266WebServer WebServer(80);


Struct_Data_Node _data_node = {0, 0, 0, 0, false, false};
Struct_Data_Node _data_lcd_buffer[NO_OF_NODE_SENSOR];

Struct_Command _command = {0, 0, 0};

uint8_t Broadcast_Address[][6] = { {0x48, 0x3F, 0xDA, 0x68, 0x13, 0xC5},
                                    {0x48, 0x3F, 0xDA, 0x67, 0xB5, 0x0A} };


unsigned char node_turn_for_lcd_display = 0;


unsigned char _counter_time = 0;

unsigned int _display_time = 0;
unsigned int _time_call_FSM_data = 0;

bool _flag_send_data_sv = false, _flag_send_data_node = 0;

bool _flag_wf_selected = 0;
bool _flag_special_mode_lcd = 0;

String _wifi_name = "", _wifi_pass = "";