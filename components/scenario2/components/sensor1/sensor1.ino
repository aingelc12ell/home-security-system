// sensor array #1: orientation sensors

// libraries
#include <Wire.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking
#define i2cAdd  10 // i2c address

// pin registry
const int tiltPin = 3;
const int shockPin = 5;


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
	initDigital(tiltPin);
	initDigital(shockPin);
}
void checkModules(){
	systat = checkDigital(tiltPin);
	Serial.print("Level Tilt Switch: ");
	Serial.print(systat);
	if(systat == HIGH){
		Serial.print(" on alarm");
		setAlarm = 11;
	}else{
    setAlarm = 0;
	}
	Serial.println(" ");
	
	if(setAlarm == 0){
	  systat = checkDigital(shockPin);
	  Serial.print("Coil Shock: ");
	  Serial.print(systat);
	  if(systat == HIGH){
		  Serial.print(" on alarm");
		  setAlarm = 12;
		  //doAlarm();
	  }else{
      setAlarm = 0;
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
			
			systat = checkDigital(tiltPin);
			systat = checkDigital(shockPin);
			alarmCounter--;
		}else{
			Serial.println("checking modules");
			checkModules();
		}
	//}
	delay(1000);
}
