/**
Implementation Option 5: Integrating all implementation options into one Home Security System

Subcomponents:
- Component51 - Independent Gas Sensor
- Component52 - Kitchen Safety: Fire, Water, Temperature, Gas, 2.4Ghz
- Component53 - Kitchen Safety: Gas Sensors, Relay Switch, 2.4Ghz
- Component54 - Perimeter Security: Reed Switch, Magnetic Switches, Ultrasonic Sensor, Infrared Sensor
- Component55 - I2C+2.4Ghz Relay: Relay Signals from Component54, Component56, Component57
- Component56 - Living Space Security: Shock Sensors, Magnetic Switches, Relay Switch + I2C
- Component57 - Living Space Safety: Infrared, Gas, Temperature, Humidity
- Component58 - 
- Component59 - Ethernet/Web Relay
**/

// include libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// setup system
int systat = 0, setAlarm = LOW, intdata;
int alarmCounter = 10; // cycles to delay checking

// pin registry
const int buzzerPin = 6;
const int greenLED = 4;
const int redLED = 5;

// NRF
RF24 RF24Rx(8, 9); // CE, CSN
const byte address[6] = "AABBC";

// i2c slave addresses
#define i2cEthernet 50 //address of this component
#include "./modules/i2c.h"
/*
// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x26;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
const char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"Air Quality Alarm" //2 //MQ135
  ,"Reed Switched" //3
  ,"Ultrasonic On" //4
  ,"Hall Magnetized" //5
  ,"Linear Hall" //6
  ,"Sensor Touched" //7
  ,"High Temperature" //8
  ,"Mercury Tilted" //9
  ,"Alarm # 10" //10
  ,"Alarm: Ultrasonic" //11
  ,"Alarm: Light Tripwire" //12
  ,"Alarm: Analog Hall" // 13
  ,"Humid Environment" // 14
  ,"Gas Alarm MQ2" //15
  ,"Gas Alarm MQ9" //16
  ,"Gas Alarm MQ3" //17
  ,"Gas Alarm MQ4" //18
  ,"Movement via PIR" //19
  ,"Shock @Loc1" //20
  ,"Shock @Loc2" //21
  ,"Shock @Loc3" //22
  ,"Shock @Loc4" //23
};*/

// component registry
#include "./modules/buzzer2.h"
#include "./modules/led.h"

// alarm Protocol
void initAlarm(){
	initLED(redLED);
	
	RF24Rx.begin();
	RF24Rx.openReadingPipe(0, address);   //Setting the address at which we will receive the data
	RF24Rx.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
	RF24Rx.startListening();              //This sets the module as receiver
	
	//lcd.begin(16,2);
	//lcd.backlight();
	
	initBuzzer(buzzerPin);
	delay(1000);
}

void i2cRequest(){
	Serial.print("          Sending : ");
	Serial.println(systat);
	Wire.write(systat);
}

void doAlarm(){
	if(setAlarm > 0){
		Serial.println("ALARM!!!! ALARM!!!!");
		doLED(redLED,HIGH);
		//doBuzzerOn(buzzerPin);
		
		//lcd.setCursor(0,1);
		//lcd.print("ALARM!!! alarm!!!");
		//delay(500);
	}
	else{
		doLED(redLED,LOW);
	}
}

// modules
void initModules(){
	initLED(greenLED);
}
void checkModules(){
	
	//fetch signals from NRF
	if (RF24Rx.available())              //Looking for the data.
	{
        //Saving the incoming data
		RF24Rx.read(&intdata, sizeof(intdata));    //Reading the data
		Serial.print("Received data: ");
		Serial.println(intdata);
		systat = intdata;
		
		//lcd.clear();
		//lcd.setCursor(0,0);
		//lcd.print(lcdMessage[systat]);
		
		if(systat > 0){
			setAlarm = HIGH;
		}else{
			setAlarm = LOW;
		}
	}
	 else{
		//lcd.clear();
		//lcd.setCursor(0,0);
		//lcd.print(lcdMessage[0]);
		Serial.println("Awaiting Data");
		setAlarm = LOW;
	 }
}
////////////////////////////////////////////////////
// main functions
void setup(){
	Serial.begin(9600);
	
	Wire.begin(i2cEthernet); 
	Wire.onRequest(i2cRequest);
	
	initAlarm();
	initModules();
}
void loop(){
  systat = 0;
	doLED(greenLED,HIGH);
	if(alarmCounter > 0){
		delay(1000);
		Serial.print("delaying ");
		Serial.println(alarmCounter);
		alarmCounter--; // give time for system to warm up if needed
	}else{
		Serial.println("checking modules");
		checkModules();
	}
	doAlarm();
	doLED(greenLED,LOW);
	delay(500);
}
