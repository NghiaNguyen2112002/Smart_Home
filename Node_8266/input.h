#ifndef __INPUT_DHT_H__
#define __INPUT_DHT_H__

#include <DHT.h>

#define DHTTYPE       DHT11 // DHT 11
#define DHT_PIN       D7
#define ADC_PIN       A0
#define SW1_PIN       D6
#define SW2_PIN       D5

void IN_Init(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);
unsigned char IN_ReadLight(void);
void IN_ButtonReading(void){
bool IN_IsPress(unsigned char index);


#endif