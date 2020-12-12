// sensor array #3: Component 54
// + Ultrasonic sensor 
// + Hall Switch 
// + Light-blocking Switch
// + analog hall Switch
// + Passive Infrared

// libraries
#include <Wire.h>

// setup system
int systat, setAlarm = 0,alarmCounter = 5; // cycles to delay checking
float uhDistance, uhThreshold = 10;
#define i2cAdd  54 // i2c address

// pin registry
const int reedPin = 2;
const int hallPin = 4;
const int PIRpin = 6;
const int anaHall = 7;
const int uhEchoPin = 8;
const int uhTrigPin = 9;
const int lightBlock = 10;
const int greenLED = 11;
const int buzzerPin = 12;


// component registry
#include "./modules/buzzer2.h"
#include "./modules/ultrasonic.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// alarm Protocol
void initAlarm(){
	initBuzzer(buzzerPin);
}
void doAlarm(){
	if(setAlarm > 0){
		Serial.println("On alarm !!!");
		doBuzzerOn(buzzerPin);
	}
}

// modules
void initModules(){
	initUltraSonic(uhTrigPin,uhEchoPin);
	initDigital(reedPin);
	initDigital(hallPin);
	initDigital(PIRpin);
	initDigital(anaHall);
	initDigital(lightBlock);
	initDigital(greenLED);
}
void checkModules(){
	
	uhDistance = checkUltraSonic(uhTrigPin,uhEchoPin);
	Serial.print("Ultrasonic Sensor: ");
	Serial.print(uhDistance);
	if(uhDistance <= uhThreshold){
		setAlarm = 4;
		Serial.print("  on alarm");
	}
	else{
		setAlarm = 0;
	}
	Serial.println("");
	
	if(setAlarm == 0){
		systat = checkDigital(reedPin);
		Serial.print("Reed Switch: ");
		Serial.print(systat);
		if(systat == LOW){
			Serial.print(" on alarm");
			setAlarm = 3;
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(hallPin);
		Serial.print("Hall Magenetic Switch: ");
		Serial.print(systat);
		if(systat == HIGH){
			Serial.print(" on alarm");
			setAlarm = 5;
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(PIRpin);
		Serial.print("Passive Infrared Movement: ");
		Serial.print(systat);
		if(systat == HIGH){
			Serial.print(" on alarm");
			setAlarm = 19;
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(anaHall);
		Serial.print("Analog Hall Magenetic Switch: ");
		Serial.print(systat);
		if(systat == HIGH){
			Serial.print(" on alarm");
			setAlarm = 13;
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(lightBlock);
		Serial.print("Light Blocking Switch: ");
		Serial.print(systat);
		if(systat == HIGH){
			Serial.print(" on alarm");
			setAlarm = 12;
		}
		Serial.println(" ");
	}
	
}
////////////////////////////////////////////////////
// main functions
void setup(){
	Wire.begin(i2cAdd);
	Wire.onRequest(i2cRequest);
	Serial.begin(9600);
	initAlarm();
	initModules();
}
void i2cRequest(){
	Serial.print("Sending: ");
	Serial.println(setAlarm);
	Wire.write(setAlarm);
}

void loop(){
	if(alarmCounter > 0){
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		uhDistance = checkUltraSonic(uhTrigPin,uhEchoPin);
    systat = checkDigital(reedPin);
    systat = checkDigital(hallPin);
    systat = checkDigital(PIRpin);
    systat = checkDigital(anaHall);
    systat = checkDigital(lightBlock);
		
		alarmCounter--;
	}else{
		Serial.println("checking modules");
		checkModules();
		doAlarm();
	}
	delay(500);
}
