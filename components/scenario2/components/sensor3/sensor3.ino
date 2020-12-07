// sensor array #3: 

// libraries
#include <Wire.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking
#define i2cAdd  30 // i2c address

// pin registry
const int reedPin = 3;
const int mercPin = 6;

// component registry
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// alarm Protocol
void initAlarm(){

}
void doAlarm(){
	Serial.println("On alarm !!!");
}

// modules
void initModules(){
	initDigital(reedPin);
	initDigital(mercPin);
}
void checkModules(){
	
	systat = checkDigital(reedPin);
	Serial.print("Reed Switch: ");
	Serial.print(systat);
	if(systat == HIGH){
		Serial.print(" on alarm");
		setAlarm = 31;
	}else{
    setAlarm = 0;
	}
	Serial.println(" ");
	if(setAlarm == 0){
  	systat = checkDigital(mercPin);
  	Serial.print("Mercury Tilt: ");
  	Serial.print(systat);
  	if(systat == HIGH){
  		Serial.print(" on alarm");
  		setAlarm = 32;
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
	//if(setAlarm == LOW){
		if(alarmCounter > 0){
			Serial.print("delaying ");
			Serial.println(alarmCounter);
			
			systat = checkDigital(reedPin);
			systat = checkDigital(mercPin);
			alarmCounter--;
		}else{
			Serial.println("checking modules");
			checkModules();
		}
	//}
	delay(1000);
}
