#include "lcd.h"

LiquidCrystal_I2C  lcd(0x3F, 16, 2);


unsigned char current_row, current_col;

char LcdScreen[2][16] = {
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};


void LCD_Init(void){
  Wire.begin(PIN_SDA, PIN_SCL);
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  lcd.noBlink();
  lcd.noCursor();
  lcd.clear();
}

void LCD_ClearBuffer(void){
    unsigned char i, j;
    for(i = 0; i < 2; i++){
        for(j = 0; j < 16; j++){
            LcdScreen[i][j] = ' ';
        }
    }
}

void LCD_PrintCharBuffer(unsigned char x, unsigned char y, unsigned char c){
    current_row = x % 2;
    current_col = y % 16;
    LcdScreen[current_row][current_col] = c;
}

void LCD_UpdateCharBuffer(unsigned char c){
    LcdScreen[current_row][current_col] = c;
    current_col++;
}

void LCD_PrintNumBuffer(unsigned char x, unsigned char y, unsigned char num){
    if(num > 99) return;
    char flag_num = 0;
    unsigned char i;
    unsigned long power_of_10 = 1000000000;
    current_row = x % 2;
    current_col = y % 16;
    
    LCD_UpdateCharBuffer(num / 10 + '0');
    LCD_UpdateCharBuffer(num % 10 + '0');
  
}

void LCD_PrintFloatBuffer(unsigned char x, unsigned char y, float num){
    if(num > 99) return;
    unsigned char integerPart, decimalPlaces;
    current_row = x % 2;
    current_col = y % 16;

    integerPart = (unsigned char)floor(num);
    decimalPlaces = (unsigned char) round ( (num - integerPart) * 10);

    LCD_UpdateCharBuffer(integerPart / 10 + '0');
    LCD_UpdateCharBuffer(integerPart % 10 + '0');
    LCD_UpdateCharBuffer('.');
    LCD_UpdateCharBuffer(decimalPlaces + '0');
}

void LCD_PrintStringBuffer(unsigned char x, unsigned char y, String str){

    current_row = x % 2;
    current_col = y % 16;
    
    for(int i = 0; i < (int)str.length(); i++){
        LCD_UpdateCharBuffer(str[i]);
    }
}


void LCD_DisplayScreen(void){
  lcd.setCursor(0, 0);
  lcd.printstr(LcdScreen[0]);
  lcd.setCursor(0, 1);
  lcd.printstr(LcdScreen[1]);
}