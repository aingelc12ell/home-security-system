#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2);

void initLCD(){
  lcd.begin();
  lcd.backlight();
}

void displayLCD(int lstart,int lline,char *message){
	lcd.setCursor(lstart,lline);
	lcd.print(message);
}
	
void doLCD(char *message){
	displayLCD(0,0,message);
	delay(500);
	lcd.clear();
	displayLCD(16,1,message);
	lcd.clear();
	delay(500);
}