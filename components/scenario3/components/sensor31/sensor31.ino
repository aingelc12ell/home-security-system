// sensor Array #31
// include libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking

const int reedAlarm = HIGH; // reed switch; HIGH-no contact; LOW-contact
const int mercAlarm = LOW;

// pin registry
const int greenLED = 3;
const int mercPin = 6;
const int reedSwitch = 5;

// component registry
#include "./modules/led.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// NRF
RF24 NRFradio(8, 9); // CE, CSN   
const byte NRFaddress[6] = "AABBC";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
#include "./modules/nrf24l01.h"

// KY-001 temperature sensor
#define KY001pin 2 //digital pin

OneWire oneWireKY001(KY001pin);
DallasTemperature KY001(&oneWireKY001);

#include "./modules/KY-001-temperature.h"

// alarm Protocol
void initAlarm(){

}
void doAlarm(){
	if(setAlarm > 0){
    Serial.print("!!! Sending status: ");
    Serial.println(setAlarm);
    NRFradio.write(&setAlarm,sizeof(setAlarm));
  }
}

// modules
void initModules(){
	initNRF();
	initKY001();
	initLED(greenLED);
	initDigital(reedSwitch);
	initDigital(mercPin);
}
void checkModules(){
	
	float tempC = checkKY001();
	if(tempC > 30){
		setAlarm = 8;
	}else{
    setAlarm = 0;
	}
 
	if(setAlarm == 0 ){
  	systat = checkDigital(reedSwitch);
  	Serial.print("Reed Switch: ");
  	Serial.println(systat);
  	if(systat == reedAlarm){
  		setAlarm = 3;
  	}
	}

  if(setAlarm == 0){
  	systat = checkDigital(mercPin);
  	Serial.print("Mercury Tilt: ");
  	Serial.println(systat);
  	if(systat == mercAlarm){ 
  		setAlarm = 9;
  	}
  }
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
	if(alarmCounter > 0){
		delay(1000);
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		alarmCounter--; // give time for system to warm up if needed
	}else{
		Serial.println("checking modules");
		checkModules();
		delay(1000);
		doAlarm();
	}
	doLED(greenLED,LOW);
}
