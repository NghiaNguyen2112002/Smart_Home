#ifndef __INPUT_H__
#define __INPUT_H__

#include <DHT.h>



#define DHTTYPE       DHT11 // DHT 11
#define DHT_PIN       D6
#define ADC_PIN       A0
#define SW1_PIN       D8
#define SW2_PIN       D7    

#define NO_OF_BUTTONS         2
#define BUTTON_IS_PRESSED     0
#define BUTTON_IS_RELEASED    1

#define DURATION_FOR_AUTO_INCREASING        1000      //50s

#define BUTTON_CONFIG       0
#define BUTTON_MODE         1


void IN_Init(void);
void IN_ButtonReading(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);
unsigned char IN_ReadLight(void);
bool IN_IsPressed(unsigned char index);
bool IN_IsPressed_ms(unsigned char index, unsigned int duration);
#endif