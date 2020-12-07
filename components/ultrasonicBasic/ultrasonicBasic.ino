// include libraries

// setup components
int setAlarm = LOW;
int alarmCounter = 5; // cycles to delay checking
long uhThreshold = 10; // in centimeters; distance to trigger alarm
long uhDistance;
// pin registry
const int buzzerPin = 10;
const int greenLED = 11;
const int redLED = 12;
const int uhTrigPin = 9;
const int uhEchoPin = 8;

// component registry
#include "./modules/buzzer2.h"
#include "./modules/led.h"
#include "./modules/ultrasonic.h"

// alarm Protocol
void initAlarm(){
  initLED(redLED);
	initBuzzer(buzzerPin);
}
void doAlarm(){
  Serial.println("ALARM!!!! ALARM!!!!");
  doLED(redLED,HIGH);
	doBuzzerOn(buzzerPin);
}

// modules
void initModules(){
  initLED(greenLED);
	initUltraSonic(uhTrigPin,uhEchoPin);
}
void checkModules(){
	uhDistance = checkUltraSonic(uhTrigPin,uhEchoPin);
	if(uhDistance <= uhThreshold){
		setAlarm = HIGH;
	}
  // doLED(greenLED,LOW);
}

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
			alarmCounter--; // give time for system to warm up if needed
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
