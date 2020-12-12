// sensor array #3: Component 56
// + Shock Sensor
// + Hall Switch 
// + Light-blocking Switch
// + analog hall Switch
// + Passive Infrared

// libraries
#include <Wire.h>

// setup system
int systat, setAlarm = 0,alarmCounter = 5; // cycles to delay checking
int alarmCounterCP = alarmCounter;

#define i2cAdd  56 // i2c address

// pin registry
const int shock1 = 2, s1Threshold = LOW;
const int hallPin = 3, hallThreshold = LOW;
const int shock2 = 4, s2Threshold = HIGH;
const int shock3 = 5, s3Threshold = HIGH;
const int shock4 = 6, s4Threshold = HIGH;
const int reedSwitch = 7, reedThreshold = HIGH;

const int relaySwitchpin = 8, relaySignal = HIGH;
const int buzzerPin = 10;
const int greenLED = 11;
const int redLED = 12;


// component registry
#include "./modules/led.h"
#include "./modules/buzzer2.h"
#include "./modules/relayswitch.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// alarm Protocol
void initAlarm(){
	initBuzzer(buzzerPin);
	initRelaySwitch(relaySwitchpin);
	initLED(redLED);
}
void doAlarm(){
	if(setAlarm > 0){
		Serial.println("On alarm !!!");
		doBuzzerOn(buzzerPin);
		doLED(redLED,HIGH);
	}
 else{
  doLED(redLED,LOW);
 }
}

// modules
void initModules(){
	initDigital(shock1);
	initDigital(hallPin);
	initDigital(shock2);
	initDigital(shock3);
	initDigital(shock4);
	initDigital(reedSwitch);
	initDigital(greenLED);
}
void checkModules(){
	
	systat = checkDigital(shock1);
	Serial.print("Shock Sensor 1: ");
	Serial.print(systat);
	if(systat == s1Threshold){
		setAlarm = 20;
		Serial.print("  on alarm");
	}
	else{
		setAlarm = 0;
	}
	Serial.println("");
	
	if(setAlarm == 0){
		systat = checkDigital(shock2);
		Serial.print("Shock Sensor 2: ");
		Serial.print(systat);
		if(systat == s2Threshold){
			setAlarm = 21;
			Serial.print("  on alarm");
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(shock3);
		Serial.print("Shock Sensor 3: ");
		Serial.print(systat);
		if(systat == s3Threshold){
			setAlarm = 22;
			Serial.print("  on alarm");
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(shock4);
		Serial.print("Shock Sensor 4: ");
		Serial.print(systat);
		if(systat == s4Threshold){
			setAlarm = 23;
			Serial.print("  on alarm");
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		//systat = checkDigital(hallPin);
		Serial.print("Hall Magenetic Switch: ");
		Serial.print(systat);
		if(systat == HIGH){
			Serial.print(" on alarm");
			setAlarm = 5;
		}
		Serial.println(" ");
	}
	
	if(setAlarm == 0){
		systat = checkDigital(reedSwitch);
		Serial.print("Reed Switch: ");
		Serial.print(systat);
		if(systat == reedThreshold){
			Serial.print(" on alarm");
			setAlarm = 3;
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
	doLED(greenLED,HIGH);
	if(alarmCounter > 0){
		doLED(redLED,HIGH);
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		systat = checkDigital(shock1);
		systat = checkDigital(shock2);
		systat = checkDigital(shock3);
		systat = checkDigital(shock4);
		systat = checkDigital(hallPin);
		systat = checkDigital(reedSwitch);
		alarmCounter--;
		delay(1000);
		doLED(redLED,LOW);
	}else{
		Serial.println("checking modules");
		checkModules();
		doAlarm();
		delay(500);
	}
	doLED(greenLED,LOW);
	delay(500);
}
