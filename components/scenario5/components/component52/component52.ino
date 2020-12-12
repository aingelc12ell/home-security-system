// sensor Array #32 :: Component 52
// DHT + Fire + Water + Smoke + NRFL01
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

dht DHT11;

// setup system
int systat, setAlarm = 0;
int alarmCounter = 5; // cycles to delay checking
const int smokeThreshold = 450; // sensor reading value
const int tempThreshold = 30;
const int humidThreshold = 96;
const int reedAlarm = LOW;

// pin registry
const int smokePin = A3;
const int flamePin = 5;
const int dhtPin = 6;
const int buttonPin = 3;

// component registry
#include "./modules/singleDigitalPin.h" // a generic way to add sensors that uses a single digital pin

// NRF
RF24 NRFradio(8, 9); // CE, CSN   
const byte NRFaddress[6] = "AABBC";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
#include "./modules/nrf24l01.h"

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

	initDigital(smokePin); //analog
	initDigital(flamePin);
	initDigital(buttonPin);
}
void checkModules(){
	
  systat = checkDigital(flamePin);
  Serial.print("Fire Sensor: ");
  Serial.println(systat);
  if(systat == HIGH){
    setAlarm = 1;
  }else{
    setAlarm = 0;
  }
  
  if(setAlarm == 0){
  	systat = analogRead(smokePin);
  	Serial.print("Smoke Reading: ");
  	Serial.println(systat);
  	if(systat >= smokeThreshold){
  		setAlarm = 2;
  	}
  }
  if(setAlarm == 0){
  	delay(1000);
  	int chk = DHT11.read11(dhtPin);
  	Serial.print("Temperature: ");
  	systat = DHT11.temperature;
  	Serial.println(systat);
  	if(systat >= tempThreshold){
  		setAlarm = 8;
  	}
  	Serial.print("Humidity: ");
  	systat = DHT11.humidity;
  	Serial.println(systat);
  	if(systat >= humidThreshold){
  		//setAlarm = 14;
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
	if(alarmCounter > 0){
		delay(1000);
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		systat = analogRead(smokePin);
		Serial.print("Smoke reading: ");
		Serial.println(systat);
		alarmCounter--; // give time for system to warm up if needed
	}else{
		Serial.println("checking modules");
		checkModules();
		delay(1000);
		doAlarm();
	}
}
