#ifndef __INC_LCD_H__
#define __INC_LCD_H__

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
// static const uint8_t D0   = 16;
// static const uint8_t D1   = 5;
// static const uint8_t D2   = 4;
// static const uint8_t D3   = 0;
// static const uint8_t D4   = 2;
// static const uint8_t D5   = 14;
// static const uint8_t D6   = 12;
// static const uint8_t D7   = 13;
// static const uint8_t D8   = 15;
// static const uint8_t D9   = 3;
// static const uint8_t D10  = 1;

#define PIN_SDA             0
#define PIN_SCL             2


void LCD_Init(void);
void LCD_ClearBuffer(void);

void LCD_PrintCharBuffer(unsigned char x, unsigned char y, unsigned char c);
void LCD_PrintNumBuffer(unsigned char x, unsigned char y, unsigned char num);
void LCD_PrintFloatBuffer(unsigned char x, unsigned char y, float num);
void LCD_PrintStringBuffer(unsigned char x, unsigned char y, String str);

void LCD_DisplayScreen(void);

#endif