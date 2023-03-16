#include "global.h"

WiFiClient espClient = WiFiClient();

Struct_Data_Node _data_node = {NODE_ID, 0, 0, 0, false, false};

uint8_t Broadcast_Address[] = {0x3C, 0x61, 0x05, 0xD0, 0x8F, 0xD2};

Struct_Command _command;

bool _flag_receive_command = false;