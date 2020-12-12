// Sensor Array #41 : Component 53
// Gas + Relay + 2.4Ghz

// include libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking : delays upon triggering the alarm
int alarmCounterCP = alarmCounter; // mirror the settings; need to refer later
const int relayAlarm = HIGH; // at which state the relay should be on alarm: HIGH=switch on; LOW=switch off
float gasAnalog;

// pin registry
const int buzzerPin = 6;
const int greenLED = 3;
const int relayPin = 2;


// component registry
#include "./modules/led.h"
#include "./modules/buzzer2.h"
#include "./modules/relaySwitch.h"
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// MQ - digital pins
#define MQ3pin 4
#define MQ4pin 5
#define MQ3Analog A1
#define MQ4Analog A0
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
	initDigital(MQ3pin);
}
void checkModules(){
	int stat = digitalRead(MQ3pin);
  float gasAnalog = analogRead(MQ3Analog);
	Serial.print("MQ3 : ");
	Serial.print(stat);
  Serial.print(" ");
  Serial.print(gasAnalog);
	if(stat == MQisOn){
		Serial.println("..triggered");
		setAlarm = 17;
		alarmCounter = alarmCounterCP; // allow system to be on alarm status during this time
	}
	else{
		setAlarm = 0;
	}
	if(setAlarm == 0){
		int stat = digitalRead(MQ4pin);
		
  float gasAnalog = analogRead(MQ3Analog);
  Serial.print("MQ4 : ");
  Serial.print(stat);
  Serial.print(" ");
  Serial.print(gasAnalog);
		if(stat == MQisOn){
			Serial.println("..triggered");
			setAlarm = 17;
			alarmCounter = alarmCounterCP; // allow system to be on alarm status during this time
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
		delay(500);
	}
	doAlarm();
	doLED(greenLED,LOW);
	delay(500);
}
