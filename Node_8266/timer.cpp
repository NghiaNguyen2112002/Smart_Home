#include "timer.h"

uint32_t timer1_MUL = 1, timer1_counter = 0, timer1_value = 0, timer1_period = 1;
uint8_t timer1_flag = 0;

void TMR1_Init(uint32_t period_ms){
  timer1_disable();

  timer1_period = period_ms;
  timer1_value = timer1_period *  5000 ;            //1000ms     -   5000000 cycle
                                                    //period_ms  -      ?
  timer1_isr_init();
  timer1_attachInterrupt(TMR1_Isr);
  timer1_write(timer1_value);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);     //DIV16 => 5MHz
}

void TMR1_Start(void){
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);     //DIV16 => 5MHz
}
void TMR1_Stop(void){
  timer1_disable();
}

void TMR1_Isr(void){
  if(timer1_counter < timer1_MUL){
    timer1_counter++;
      if(timer1_counter >= timer1_MUL){
        timer1_counter = 0;
        timer1_flag = 1;
      }
  }

}

void TMR1_SetTime_ms(uint32_t duration){
  timer1_counter = 0;
  timer1_flag = 0;
  timer1_MUL = duration / timer1_period;        
}