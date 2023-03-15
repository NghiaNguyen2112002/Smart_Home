#include "fsm.h"

unsigned char mode_lcd;



void FSM_Init(void){
  mode_lcd = INIT;
  node_turn_for_lcd_display = 1;
  _display_time = SCREEN_TIME;
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
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');
        LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_DHT;
      }
    break;
    case DISPLAY_DHT:
      
      LCD_PrintFloatBuffer(0, INDEX_TEMP_VALUE, _data_lcd_buffer.temp);
      LCD_PrintFloatBuffer(1, INDEX_HUMID_VALUE, _data_lcd_buffer.humid);

      if(_display_time == 0){
        LCD_PrintStringBuffer(0, 0, SCREEN_LIGHT_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_LIGHT_1);
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');
        // LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1'); 
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_LIGHT;
      }
    break;
    case DISPLAY_LIGHT:

      LCD_PrintNumBuffer(0, INDEX_LIGHT_VALUE, _data_lcd_buffer.light_intensity);

      if(_display_time == 0){
        LCD_PrintStringBuffer(0, 0, SCREEN_RELAY_0);
        LCD_PrintStringBuffer(1, 0, SCREEN_RELAY_1);
        LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');
        LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');
        _display_time = SCREEN_TIME;
        mode_lcd = DISPLAY_RELAY;
      }
    break;
    case DISPLAY_RELAY:

      LCD_PrintStringBuffer(0, INDEX_RELAY_STATE, _data_lcd_buffer.status_relay_0 ? LCD_RELAY_STATE_ON : LCD_RELAY_STATE_OFF);
      LCD_PrintStringBuffer(1, INDEX_RELAY_STATE, _data_lcd_buffer.status_relay_1 ? LCD_RELAY_STATE_ON : LCD_RELAY_STATE_OFF);

      if(_display_time == 0){
        mode_lcd = TURN_NEXT_NODE;
      }
    break;
    case TURN_NEXT_NODE:
      // node_turn_for_lcd_display = (node_turn_for_lcd_display + 1) % NO_OF_NODE_SENSOR;
      

      LCD_PrintStringBuffer(0, 0, SCREEN_HUMID_TEMP_0);
      LCD_PrintCharBuffer(0, INDEX_CEL_SYMBOL, 0xDF);
      LCD_PrintStringBuffer(1, 0, SCREEN_HUMID_TEMP_1);
      LCD_PrintCharBuffer(0, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');
      LCD_PrintCharBuffer(1, INDEX_LCD_NODE, _data_lcd_buffer.node_id + '1');  
      _display_time = SCREEN_TIME;
      mode_lcd = DISPLAY_DHT;
    break;
    case DISPLAY_WF_CONF:

    break;
    default: 
      mode_lcd = INIT;
    break;
  }
}
