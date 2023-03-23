#ifndef __INPUT_DHT_H__
#define __INPUT_DHT_H__

#include <DHT.h>

#define DHTTYPE       DHT11 // DHT 11
#define DHT_PIN       D7
#define ADC_PIN       A0
#define SW1_PIN       D6
#define SW2_PIN       D5


#define NO_OF_BUTTONS         2
#define BUTTON_IS_PRESSED     0
#define BUTTON_IS_RELEASED    1

#define DURATION_FOR_AUTO_INCREASING        5000      //10s

void IN_Init(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);
unsigned char IN_ReadLight(void);
void IN_ButtonReading(void);
bool IN_IsPressed(unsigned char index);


#endif