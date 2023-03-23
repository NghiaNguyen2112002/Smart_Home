#include "fsm.h"

unsigned char mode;

void FSM_Init(void){
  mode = INIT;
}



void FSM_DataProcessing(void){
  switch(mode){
    case INIT:
      if(WF_IsConnected()) mode = READ_DATA;
      else mode = CONNECT_WIFI;
    break;
    case CONNECT_WIFI:
      WF_Reconnect();
      mode = READ_DATA;
    break;
    case IDLING:
      if(_time_read_data == 0){
        _time_read_data = TIME_READ_DATA;
        mode = READ_DATA;
      }
      else if(_flag_receive_command){
        mode = RECEIVED_CMD;
      }
      else if(IN_IsPressed(0)){
        OUT_TuggleRelay(0);
        mode = READ_DATA;
      }
      else if(IN_IsPressed(1)){
        OUT_TuggleRelay(1);
        mode = READ_DATA;
      }
    break;
    case READ_DATA:
      _data_node.status_relay_0 = OUT_IsRelayOn(0);
      _data_node.status_relay_1 = OUT_IsRelayOn(1);
      _data_node.humid = IN_ReadHumid();
      _data_node.temp =  IN_ReadTemp();
      _data_node.light_intensity = IN_ReadLight();

      if(WF_IsConnected()) mode = SEND_DATA;
      else mode = CONNECT_WIFI;
    break;
    case SEND_DATA:    
      _data_node.node_id = NODE_ID;
      esp_now_send(Broadcast_Address, (uint8_t *) &_data_node, sizeof(_data_node));
      mode = IDLING;
      
    break;
    case RECEIVED_CMD:
      if(_command.value == 1){
        OUT_TurnRelayOn(_command.actuator_index);
      }
      else if(_command.value == 0){
        OUT_TurnRelayOff(_command.actuator_index);
      }
    break;
  }
}