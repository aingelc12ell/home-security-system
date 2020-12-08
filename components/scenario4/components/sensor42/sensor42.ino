// include libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking
const int relayAlarm = HIGH; // at which state the relay should be on alarm: HIGH=switch on; LOW=switch off

// pin registry
const int redLED = 3;
const int greenLED = 4;
const int buzzerPin = 5;


// component registry
#include "./modules/led.h"
#include "./modules/buzzer2.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// MQ - digital pins
#define MQ3pin 6
#define MQisOn LOW

// NRF
RF24 NRFradio(8, 9); // CE, CSN   
const byte NRFaddress[6] = "AABBC";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
#include "./modules/nrf24l01.h"

// alarm Protocol
void initAlarm(){
	initLED(redLED);
  initBuzzer(buzzerPin);
}
void doAlarm(){
	if(setAlarm > 0){
		//Serial.println("ALARM!!!! ALARM!!!!");
		Serial.print("!!! Sending status: ");
		Serial.println(setAlarm);
    doLED(redLED,HIGH);
    doBuzzerOn(buzzerPin);
		NRFradio.write(&setAlarm,sizeof(setAlarm));
	}
	else{
		doLED(redLED,LOW);
	}
}

// modules
void initModules(){
	initLED(greenLED);
	initDigital(MQ3pin);
}
void checkModules(){
	
	int stat = digitalRead(MQ3pin);
	Serial.print("MQ-3 Digital: ");
	Serial.println(stat);
	if(stat == MQisOn){
		setAlarm = 16;
	}
	else{
		setAlarm = 0;
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
		doAlarm();
		delay(1000);
	}
	doLED(greenLED,LOW);
	delay(1000);
}
