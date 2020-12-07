// this sketch will use I2C bus and house the system's alarm module from the sensor array
#include <Wire.h>
// include libraries

// setup system
int systat, setAlarm = LOW;
int alarmCounter = 5; // cycles to delay checking
const int relayAlarm = HIGH; // at which state the relay should be on alarm: HIGH=switch on; LOW=switch off



// pin registry
const int relayPin = 6;
const int greenLED = 13;
const int redLED = 12;
const int buzzerPin = 11;


// component registry
#include "./modules/led.h"
#include "./modules/buzzer2.h"
#include "./modules/relaySwitch.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin


// i2c
// i2c slave addresses
#define i2cSensor1 10
#define i2cSensor2 20
#define i2cSensor3 30
//#define i2cSensor4 40
#include "./modules/i2c.h"

// alarm Protocol
void initAlarm(){
	initLED(redLED);
	initBuzzer(buzzerPin);
	initRelaySwitch(relayPin);
}
void doAlarm(){
	Serial.println("ALARM!!!! ALARM!!!!");
	doLED(redLED,HIGH);
	doBuzzerOn(buzzerPin);
	relaySwitch(relayPin,relayAlarm);
}

// modules
void initModules(){
	initLED(greenLED);
}

void checkModules(){
	delay(500);
	doLED(redLED,LOW);
	doLED(greenLED,HIGH);
	// i2C listener
	
	Serial.print("......reading SensorArray 1 : ");
	systat = i2cRead(i2cSensor1);
	Serial.println(systat);
	if(systat > 10){
		Serial.println("ALARM from SensorArray1");
		//setAlarm = HIGH;
	}
	
	Serial.print(".......reading SensorArray 2 : ");
	systat = i2cRead(i2cSensor2);
	Serial.println(systat);
	if(systat > 20){
		Serial.println("ALARM from SensorArray2");
		//setAlarm = HIGH;
	}
	
	Serial.print("........reading SensorArray 3 : ");
	systat = i2cRead(i2cSensor3);
	Serial.println(systat);
	if(systat > 30){
		Serial.println("ALARM from SensorArray3");
		//setAlarm = HIGH;
	}
}
////////////////////////////////////////////////////
// main functions
void setup(){
	Wire.begin(); 
	Serial.begin(9600);
	initAlarm();
	initModules();
}
void loop(){
	if(setAlarm == LOW){
		if(alarmCounter > 0){
			delay(1000);
			Serial.print("delaying ");
			Serial.println(alarmCounter);
			alarmCounter--;
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
