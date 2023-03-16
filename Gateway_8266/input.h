#ifndef __INPUT_H__
#define __INPUT_H__

#include <DHT.h>


#define DHTTYPE       DHT11 // DHT 11
#define DHT_PIN       13
#define ADC_PIN       A0
#define CONFIG_PIN    15    

void IN_Init(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);
unsigned char IN_ReadLight(void);
bool IN_IsConfigButtonPressed(void);

#endif