#include "global.h"

WiFiClient espClient = WiFiClient();

Struct_Data_Node _data_node = {1, 0, 0, 0, false, false};

uint8_t Broadcast_Address[] = {0x3C, 0x61, 0x05, 0xD0, 0x8F, 0xD2};

