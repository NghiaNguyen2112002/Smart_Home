#include "input.h"

unsigned int CounterForButtonPress[] = {0, 0};
unsigned char BUTTON_PIN[] = {SW1_PIN, SW2_PIN};

DHT dht(DHT_PIN, DHTTYPE);     // Initialize DHT sensor

float temp, humid;

void IN_Init(void){
  dht.begin();
  pinMode(ADC_PIN, INPUT);
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
}

void IN_ButtonReading(void){
  for(int i = 0; i < NO_OF_BUTTONS; i++){
    if(digitalRead(BUTTON_PIN[i]) == BUTTON_IS_PRESSED){
      if(CounterForButtonPress[i] < DURATION_FOR_AUTO_INCREASING){
        CounterForButtonPress[i]++;
      }   
    }
    else CounterForButtonPress[i] = 0;    
  }
}

float IN_ReadHumid(void){
  humid = dht.readHumidity();

  if(isnan(humid)) {
    Serial.println("DHT Error!");
    return 0;
  }

  // Serial.print("HUMI: "); Serial.println(humid);
  return humid;
}

float IN_ReadTemp(void){
  temp = dht.readTemperature();
  
  if(isnan(temp)) {
    Serial.println("DHT Error!");
    return 0;
  }

  // Serial.print("TEMP: "); Serial.println(temp); 
  return temp;
}

unsigned char IN_ReadLight(void){
  return analogRead(ADC_PIN);
}

bool IN_IsPressed(unsigned char index){
  return CounterForButtonPress[index] == 2;
}

bool IN_IsPressed_ms(unsigned char index, unsigned int duration){
    if(index >= NO_OF_BUTTONS) return 0;
    return CounterForButtonPress[index] ==  (duration / 50);       //button is scaned every 50ms
}