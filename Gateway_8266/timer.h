#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <Arduino.h>


void TMR1_Init(uint32_t period_ms);
void TMR1_Start(void);
void TMR1_Stop(void);
void TMR1_Isr(void);
void TMR1_SetTime_ms(uint32_t duration);


extern uint8_t timer1_flag;

#endif
