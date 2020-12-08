
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>

#define greenLED 5
#define redLED 6
#define CO2threshold 400


#define MQ2pin 		A0
#include "./modules/mq2.h"
#include "./modules/led.h"

//LiquidCrystal_I2C lcd(0x26, 16, 2);


// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
//const int  en = 4, rw = 5, rs = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3, bl = 7;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x26;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup(){
	Serial.begin(9600);
	initMQ2();
  initLED(greenLED);
  initLED(redLED);
  lcd.begin(16,2);
  lcd.backlight();
}
void loop(){
  lcd.clear();
  doLED(redLED,LOW);
  doLED(greenLED,HIGH);
	float stat[3];
	checkMQ2(stat);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CO   LPG  Prop");
  lcd.setCursor(0,1);
  lcd.print(stat[0]);
  Serial.print(stat[0]);
  
  lcd.setCursor(6,1);
  lcd.print(stat[1]);
  Serial.print(stat[1]);

  lcd.setCursor(12,1);
  lcd.print(stat[2]);
  Serial.print(stat[2]);
  

  delay(500);
  doLED(greenLED,LOW);
  delay(500);
}
		
