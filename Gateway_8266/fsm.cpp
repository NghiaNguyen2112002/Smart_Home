#include "fsm.h"

unsigned char mode_lcd;
unsigned char mode_data;
unsigned char mode_wifi;

void FSM_Init(void){
  mode_lcd = INIT;
  mode_data = INIT;
  mode_wifi = INIT;
  node_turn_for_lcd_display = 0;
  _display_time = 50;
}

String ConvertDataToJsonString(void){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  data["ID"] = _data_node.node_id;
  data["TEMP"] = _data_node.temp;
  data["HUMID"] = _data_node.humid;
  data["LIGHT"] = _data_node.light_intensity;
  data["RELAY_0"] = _data_node.status_relay_0;
  data["RELAY_1"] = _data_node.status_relay_1;

  char payload[256];
  data.printTo(payload, sizeof(payload));

  String json_string = String(payload);
  Serial.println(json_string);

  return json_string; 
}

void FSM_LcdControl(void){
  switch(mode_lcd){
    case INIT:
      
      LCD_PrintStringBuffer(0, 0, SCREEN_INIT_0);
      LCD_PrintStringBuffer(1, 0, SCREEN_INIT_1);

      if(_display_time == 0){

        LCD_PrintStringBuffer(0, 0, SCREEN_HUMID_TEMP_0);
        LCD_PrintCharBuffer(0, INDEX_CEL_SYMBOL, 0xDF);
        LCD_PrintStringBuffer(1, 0, SCREEN_HUMID_TEMP_1);
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_DHT;
      }
      else if(IN_IsPress(BUTTON_CONFIG)) {
        LCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);
        mode_lcd = DISPLAY_WF_CONF;
      }
    break;
    case DISPLAY_WIFI_STATE:

    break;
    case DISPLAY_DHT:
      
      LCD_PrintFloatBuffer(0, INDEX_TEMP_VALUE, _data_lcd_buffer.temp);
      LCD_PrintFloatBuffer(1, INDEX_HUMID_VALUE, _data_lcd_buffer.humid);

      if(_display_time == 0){
        LCD_PrintStringBuffer(0, 0, SCREEN_LIGHT_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_LIGHT_1);
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        // LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0'); 
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_LIGHT;
      }
      else if(IN_IsPress(BUTTON_CONFIG)) {
        LCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);
        mode_lcd = DISPLAY_WF_CONF;
      }
    break;
    case DISPLAY_LIGHT:

      LCD_PrintNumBuffer(0, INDEX_LIGHT_VALUE, _data_lcd_buffer.light_intensity);

      if(_display_time == 0){
        LCD_PrintStringBuffer(0, 0, SCREEN_RELAY_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_RELAY_1);
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_RELAY;
      }
      else if(IN_IsPress(BUTTON_CONFIG)) {
        LCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);
        mode_lcd = DISPLAY_WF_CONF;
      }
    break;
    case DISPLAY_RELAY:

      LCD_PrintStringBuffer(0, INDEX_RELAY_STATE, _data_lcd_buffer.status_relay_0 ? LCD_RELAY_STATE_ON : LCD_RELAY_STATE_OFF);
      LCD_PrintStringBuffer(1, INDEX_RELAY_STATE, _data_lcd_buffer.status_relay_1 ? LCD_RELAY_STATE_ON : LCD_RELAY_STATE_OFF);

      if(_display_time == 0){
        mode_lcd = TURN_NEXT_NODE;
      }
      else if(IN_IsPress(BUTTON_CONFIG)) {
        LCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);
        mode_lcd = DISPLAY_WF_CONF;
      }
    break;
    case TURN_NEXT_NODE:
      node_turn_for_lcd_display = (node_turn_for_lcd_display + 1) % NO_OF_NODE_SENSOR;
      

      LCD_PrintStringBuffer(0, 0, SCREEN_HUMID_TEMP_0);
      LCD_PrintCharBuffer(0, INDEX_CEL_SYMBOL, 0xDF);
      LCD_PrintStringBuffer(1, 0, SCREEN_HUMID_TEMP_1);
      LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
      LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');  
      _display_time = SCREEN_TIME;
      mode_lcd = DISPLAY_DHT;
    break;
    case DISPLAY_WF_CONF:
      if(_flag_wf_selected){

        LCD_PrintStringBuffer(0, 0, SCREEN_HUMID_TEMP_0);
        LCD_PrintCharBuffer(0, INDEX_CEL_SYMBOL, 0xDF);
        LCD_PrintStringBuffer(1, 0, SCREEN_HUMID_TEMP_1);
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '0');
        
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_DHT;
      }
    break;
    default: 
      mode_lcd = INIT;
    break;
  }
}

void FSM_DataControl(void){
  switch(mode_data){
    case INIT:
    case READ_DATA_GATEWAY: 
      _data_node.node_id = 0;
      _data_node.humid = IN_ReadHumid();
      _data_node.temp = IN_ReadTemp();
      // _data_node.light_intensity = IN_ReadLight();

      // gateway does not have relays
      _data_node.status_relay_0 = false;
      _data_node.status_relay_1 = false;

      _flag_send_data_sv = true;

      if(SV_IsConnected()) mode_data = TRANSFER_DATA;
      else mode_data = CHECK_CONNECTION;
    break;
    case CHECK_CONNECTION:
      if(!SV_IsConnected()) SV_Connect();

      if(SV_IsConnected()) mode_data = TRANSFER_DATA;
    break;
    case TRANSFER_DATA:
      if(_flag_send_data_sv) {
        _flag_send_data_sv = false;
      // send data to server
        SV_SendData(CHANNEL_DATA, (char*)ConvertDataToJsonString().c_str());

      // data to lcd_data_buffer
        if(node_turn_for_lcd_display == _data_node.node_id) {
            memcpy(&_data_lcd_buffer, &_data_node, sizeof(_data_lcd_buffer));
        }
      }
      
      if(_flag_send_data_node){
        _flag_send_data_node = false;
      // when receive command from server, gateway send to node through espnow
        esp_now_send(Broadcast_Address[_command.node_id - 1], (uint8_t*) &_command, sizeof(_command));
      }

      if(_time_call_FSM_data < 5){
        _time_call_FSM_data = FSM_DATA_CONTROL_TIME;
        mode_data = READ_DATA_GATEWAY;
      } 
    break;
    default: 
      mode_data = INIT;
    break;
  }
}

void FSM_WifiControl(void){
  switch(mode_wifi){
    case INIT:
      _wifi_name = WIFI_NAME;
      _wifi_pass = WIFI_PASSWORD;

      mode_wifi = WIFI_CHECKCONNECTION;
    break;
    case WIFI_CHECKCONNECTION:
      if(!WF_IsConnected()) WF_Connect(_wifi_name, _wifi_pass);

      if(IN_IsPress(BUTTON_CONFIG)) {
        WF_Disconnect();
        WF_CreateWebserver();
        mode_wifi = WIFI_CONFIG;
      }
    break;
    case WIFI_CONFIG:
      if(_flag_wf_selected){
        
        mode_wifi = WIFI_CHECKCONNECTION;
      }
    break;
  }
}