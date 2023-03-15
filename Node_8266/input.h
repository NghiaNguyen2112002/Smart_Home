#ifndef __INPUT_DHT_H__
#define __INPUT_DHT_H__

#include <DHT.h>


#define DHTTYPE       DHT11 // DHT 11
#define DHT_PIN       13

void IN_Init(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);

#endif