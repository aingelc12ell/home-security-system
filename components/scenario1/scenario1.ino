// include libraries

// setup system
int systat, setAlarm = LOW;
int alarmCounter = 5; // cycles to delay checking
long uhThreshold = 10; // in centimeters; distance to trigger alarm
long uhDistance;
const int lbAlarm = HIGH; 	// HIGH|LOW; at which point the alarm be set on light blocking sensor
const int hallAlarm = LOW; // hall magnetic; HIGH - no magnet; LOW - with magnet
const int lmAlarm = HIGH; 	// linear magnetic; HIGH - with magnet; LOW - no magnet
const int reedAlarm = LOW; // reed switch; HIGH-no contact; LOW-contact

// pin registry
const int buzzerPin = 11;
const int greenLED = 12;
const int uhTrigPin = 9;
const int uhEchoPin = 8;

// single digital pin registry
const int lightBlocking = 10;
const int reedSwitch = 2;
const int linearMagnet = 4;
const int hallMagnet = 7;
const int PIR = 6;

// component registry
#include "./modules/buzzer2.h"
#include "./modules/led.h"
#include "./modules/ultrasonic.h"

#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// alarm Protocol
void initAlarm(){
	initBuzzer(buzzerPin);
}
void doAlarm(){
	Serial.println("ALARM!!!! ALARM!!!!");
	doBuzzerOn(buzzerPin);
}

// modules
void initModules(){
	initLED(greenLED);
	initUltraSonic(uhTrigPin,uhEchoPin);
	initDigital(lightBlocking);
	initDigital(hallMagnet);
	initDigital(linearMagnet);
	initDigital(reedSwitch);
	initDigital(PIR);
}
void checkModules(){
	uhDistance = checkUltraSonic(uhTrigPin,uhEchoPin);
	if(uhDistance <= uhThreshold){
		setAlarm = HIGH;
	}
	
	if(setAlarm == LOW){
		systat = checkDigital(lightBlocking);
		Serial.print("Light Blocking: ");
		Serial.println(systat);
		if(systat == lbAlarm){
			setAlarm = HIGH;
		}
	}
	
	if(setAlarm == LOW){
		systat = checkDigital(hallMagnet);
		Serial.print("Hall Magnet: ");
		Serial.println(systat);
		if(systat == hallAlarm){
			setAlarm = HIGH;
		}
	}
	
	if(setAlarm == LOW){
		systat = checkDigital(linearMagnet);
		Serial.print("Linear Magnet: ");
		Serial.println(systat);
		if(systat == lmAlarm){
			setAlarm = HIGH;
		}
	}
	
	if(setAlarm == LOW){
		systat = checkDigital(reedSwitch);
		Serial.print("Reed Switch: ");
		Serial.println(systat);
		if(systat == reedAlarm){
			setAlarm = HIGH;
		}
	}
	
	if(setAlarm == LOW){
		systat = checkDigital(PIR);
		Serial.print("Passive Infrared: ");
		Serial.println(systat);
		if(systat == HIGH){ // movement @ HIGH
			setAlarm = HIGH;
		}
	}
	doLED(greenLED,LOW);
	
}
////////////////////////////////////////////////////
// main functions
void setup(){
	Serial.begin(9600);
	initAlarm();
	initModules();
}
void loop(){
	doLED(greenLED,HIGH);
	if(setAlarm == LOW){
		if(alarmCounter > 0){
			delay(1000);
			Serial.print("delaying ");
			Serial.println(alarmCounter);
			uhDistance = checkUltraSonic(uhTrigPin,uhEchoPin);
			if(uhDistance > 3){
				alarmCounter--; // give time for system to warm up if needed
			}
		}else{
			Serial.println("checking modules");
			checkModules();
			delay(500);
		}
	}
	else{
		doAlarm();
	}
	doLED(greenLED,LOW);
	delay(500);
}
