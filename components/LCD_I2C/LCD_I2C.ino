#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int lcdCounter = 0;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x26, 16, 2);

void initLCD()
{
  // initialize the LCD, 
  lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();
}

void printLCD()
{
  lcd.clear();
  lcd.print("Hi Aingaile!");
  lcd.setCursor (0,1); // go to start of 2nd line
  int greet = lcdCounter % 3;
  switch(greet){
      case 0: lcd.print("How are you?"); break;
      case 1: lcd.print("You're Amazing!"); break;
      case 2: lcd.print("Take Care!"); break;
  }
  delay(5000);
  lcdCounter++;
}

void setup(){
  Serial.begin(9600);
  initLCD();
}

void loop(){
  printLCD();
}
