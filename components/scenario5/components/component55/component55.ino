// Component 55: I2C Master + 2.4Ghz relay

// include libraries
#include <Wire.h> 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// setup system
int systat = 0, setAlarm = LOW, intdata;
int alarmCounter = 5; // cycles to delay checking

// pin registry
const int greenLED = 4;
const int redLED = 3;
const int buzzerPin = 5;

// NRF
RF24 NRFradio(8, 9); // CE, CSN
const byte NRFaddress[6] = "AABBC";

// i2c
#define i2cAdd 55 //address of this component

// i2c slave addresses
#define i2cComponent56 56
#define i2cComponent54 54
//#define i2cSensor3 30
#include "./modules/i2c.h"

// component registry
#include "./modules/buzzer2.h"
#include "./modules/led.h"

// alarm Protocol
void initAlarm(){
	initLED(redLED);
	
	initBuzzer(buzzerPin);
	delay(1000);
}

void i2cRequest(){
	Serial.print("Sending : ");
	Serial.println(systat);
	Wire.write(systat);
}

void doAlarm(){
	if(setAlarm > 0){
		Serial.println("ALARM!!!! ALARM!!!!");
		doLED(redLED,HIGH);
		doBuzzerOn(buzzerPin);
    NRFradio.write(&setAlarm,sizeof(setAlarm));
	}
}

// modules
void initModules(){
  NRFradio.begin();                  //Starting the Wireless communication
  NRFradio.openWritingPipe(NRFaddress); //Setting the address where we will send the data
  NRFradio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  NRFradio.stopListening();          //This sets the module as transmitter
	initLED(greenLED);
}
void checkModules(){
  
  Serial.print("......reading Component 56 : ");
  systat = i2cRead(i2cComponent56);
  Serial.println(systat);
  if(systat > 0){
    Serial.println("ALARM from Component56");
    setAlarm = systat;
  }
  if(systat == 0){
    Serial.print("......reading Component 54 : ");
    systat = i2cRead(i2cComponent54);
    Serial.println(systat);
    if(systat > 0){
      Serial.println("      ALARM from Component54");
      setAlarm = systat;
    }
  }
}
////////////////////////////////////////////////////
// main functions
void setup(){
	Serial.begin(9600);
	
	Wire.begin(i2cAdd); 
	Wire.onRequest(i2cRequest);
	
	initAlarm();
	initModules();
}
void loop(){
	doLED(greenLED,HIGH);
	if(alarmCounter > 0){
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		alarmCounter--; // give time for system to warm up if needed
		doLED(redLED,HIGH);
		delay(1000);
	}else{
    setAlarm=0;
		Serial.println("checking modules");
		checkModules();
	}
	doAlarm();
	delay(500);
	doLED(greenLED,LOW);
	doLED(redLED,LOW);
	delay(500);
}
