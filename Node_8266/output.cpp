#include "output.h"

bool Relay_State[NO_OF_RELAYS];
static const uint8_t Pin_Relay[NO_OF_RELAYS] = {PIN_RELAY_1, PIN_RELAY_2};

void OUT_Init(void){
  for(int i = 0; i < NO_OF_RELAYS; i++){
    pinMode(Pin_Relay[i], OUTPUT);
    digitalWrite(Pin_Relay[i], 0);
    Relay_State[i] = false;
  }
}

bool OUT_IsRelayOn(unsigned char index){
  return Relay_State[index];
}

void OUT_TurnRelayOn(unsigned char index){
  digitalWrite(Pin_Relay[index], 1);
  Relay_State[index] = true;
}

void OUT_TurnRelayOff(unsigned char index){
  digitalWrite(Pin_Relay[index], 0);
  Relay_State[index] = false;
}

void OUT_TuggleRelay(unsigned char index){
  if(Relay_State[index]) OUT_TurnRelayOff(index);
  else OUT_TurnRelayOn(index);
}

