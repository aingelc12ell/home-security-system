// sensor array #2: shock magnetic

// libraries
#include <Wire.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking
#define i2cAdd  20 // i2c address

// pin registry
const int knockPin = 5;
const int hallPin = A0;
const int button1 = 3;
const int button2 = 6;

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
	initDigital(knockPin);
	initDigital(hallPin);
}
void checkModules(){
	setAlarm = 0;
	systat = checkDigital(knockPin);
	Serial.print("Knock/Shock: ");
	Serial.print(systat);
	if(systat == HIGH){
		Serial.print(" on alarm");
		setAlarm = 21;
	}
	Serial.println(" ");
	
	
	systat = analogRead(hallPin);
	Serial.print("Analog Hall Magnet: ");
	float voltage = systat * (5.0/1023);
	Serial.print(systat, DEC);
	Serial.print(" @ ");
	Serial.print(voltage, DEC);
	
	if(voltage > 2.6){
		Serial.print(" on alarm");
		setAlarm = 22;
	}
	Serial.println(" ");
	
if(setAlarm < 20){
    setAlarm = 0;
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
			
			systat = checkDigital(knockPin);
			systat = checkDigital(hallPin);
			systat = checkDigital(button1);
			systat = checkDigital(button2);
			alarmCounter--;
		}else{
			Serial.println("checking modules");
			checkModules();
		}
	//}
	delay(1000);
}
