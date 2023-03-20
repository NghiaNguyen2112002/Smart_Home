#include "input.h"

unsigned char BUTTON_PIN[] = {SW1_PIN, SW2_PIN};

DHT dht(DHT_PIN, DHTTYPE);     // Initialize DHT sensor

float temp, humid;

void IN_Init(void){
  dht.begin();
  pinMode(ADC_PIN, INPUT);
  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);
}

float IN_ReadHumid(void){
  humid = dht.readHumidity();

  if(isnan(humid)) {
    Serial.println("DHT Error!");
    return 0;
  }

  Serial.print("HUMI: "); Serial.println(humid);
  return humid;
}

float IN_ReadTemp(void){
  temp = dht.readTemperature();
  
  if(isnan(temp)) {
    Serial.println("DHT Error!");
    return 0;
  }

  Serial.print("TEMP: "); Serial.println(temp); 
  return temp;
}

unsigned char IN_ReadLight(void){
  return analogRead(ADC_PIN);
}

unsigned char IN_IsPress(unsigned char index){
  return digitalRead(BUTTON_PIN[index]);
}