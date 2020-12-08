// include libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <MQUnifiedsensor.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking
const int relayAlarm = HIGH; // at which state the relay should be on alarm: HIGH=switch on; LOW=switch off

// pin registry
const int buzzerPin = 6;
const int greenLED = 3;
const int relayPin = 2;


// component registry
#include "./modules/led.h"
#include "./modules/buzzer2.h"
#include "./modules/relaySwitch.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

//MQ - gas sensors :: MQUnifiedsensor
//#define MQ9pin    A0
//#include "./modules/mq9.h"
//#define MQ2pin 		A1
//#include "./modules/mq2.h"

// MQ - digital pins
#define MQ9pin 5
#define MQ2pin 4
#define MQisOn LOW

// NRF
RF24 NRFradio(8, 9); // CE, CSN   
const byte NRFaddress[6] = "AABBC";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
#include "./modules/nrf24l01.h"

// alarm Protocol
void initAlarm(){
	initBuzzer(buzzerPin);
	initRelaySwitch(relayPin);
	digitalWrite(relayPin,LOW);
}
void doAlarm(){
	if(setAlarm > 0){
		//Serial.println("ALARM!!!! ALARM!!!!");
		Serial.print("!!! Sending status: ");
		Serial.println(setAlarm);
		relaySwitch(relayPin,HIGH);
		doBuzzerOn(buzzerPin);
		NRFradio.write(&setAlarm,sizeof(setAlarm));
		delay(1000);
	}
	else{
		digitalWrite(relayPin,LOW);
	}
}

// modules
void initModules(){
	initLED(greenLED);
	initDigital(MQ9pin);
	initDigital(MQ2pin);
}
void checkModules(){
	int stat = digitalRead(MQ9pin);
	Serial.print("MQ9 : ");
	Serial.println(stat);
	if(stat == HIGH){
		Serial.println("..triggered");
		setAlarm = 16;
	}
	else{
		setAlarm = 0;
	}

	if(setAlarm == 0){
		int stat = digitalRead(MQ2pin);
		Serial.print("MQ2 : ");
		Serial.println(stat);
		if(stat == MQisOn){
			Serial.println("..triggered");
			setAlarm = 15;
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
		doAlarm();
		delay(500);
	}
	doLED(greenLED,LOW);
	delay(500);
}
