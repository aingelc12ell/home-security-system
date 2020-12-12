// Reusable sketch for MQ Gas Sensors that reads analog data and present it in 16x2 LCD screen

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define greenLED 5
#define redLED 6
#define CO2threshold 400
#define buzzerPin 3

#define MQpin 		A0
#define MQDigital 4
#include "./modules/led.h"
#include "./modules/buzzer.h"

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x26;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

int alarmCounter = 10;
const int MQisOn = LOW;
const float analogThreshold = 300; // at which reading will it set an Alarm

void setup(){
	Serial.begin(9600);
	initLED(greenLED);
	initLED(redLED);
	initBuzzer(buzzerPin);
	lcd.begin(16,2);
	lcd.backlight();
	pinMode(MQpin, INPUT);
	pinMode(MQDigital, INPUT);
}
void loop(){
	lcd.clear();
	doLED(greenLED,HIGH);
	if(alarmCounter > 0){
		doLED(redLED,HIGH);
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		
		int analogSensor = analogRead(MQpin);
		lcd.setCursor(0,0);
		lcd.print("MQ Preheating:");
		lcd.setCursor(14,0);
		lcd.print(alarmCounter);
		lcd.setCursor(3,1);
		lcd.print(analogSensor);
		
		alarmCounter--;
		delay(1000);
	}else{
		int analogSensor = analogRead(MQpin);
		int stat = digitalRead(MQDigital);

		Serial.print("MQ Reading: ");
		Serial.print(analogSensor);
		Serial.print("   ");
		Serial.println(stat);
		
		lcd.setCursor(0,0);
		lcd.print("MQ Reading");
		lcd.setCursor(1,1);
		lcd.print(analogSensor);
		lcd.setCursor(8,1);
    int isAlarm = stat==MQisOn || analogSensor >= analogThreshold ? 1 : 0;
		lcd.print(isAlarm>0 ? "Alarm !!" : "Fine :)");
		
		if(isAlarm > 0){
			doLED(redLED,HIGH);
      doBuzzerOn(buzzerPin);
		}
		else{
			doLED(redLED,LOW);
		}
		delay(500);
	}
	delay(500);
	doLED(redLED,LOW);
	doLED(greenLED,LOW);
	delay(500);
}
		
