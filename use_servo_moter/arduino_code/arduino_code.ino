//서보모터 사용법
#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,6,5,4,3);

void setup(){
  lcd.begin(16,2);
  lcd.print("Hello, Arduino!!");
}

void loop(){
  lcd.setCursor(0,1);
  lcd.print("1234567890");
}