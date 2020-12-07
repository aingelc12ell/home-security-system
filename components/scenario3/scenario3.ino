// Scenario 3: Living Spaces Security with Wireless communication
// include libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// setup system
int systat = 0, setAlarm = LOW, intdata;
int alarmCounter = 5; // cycles to delay checking

// pin registry
const int buzzerPin = 6;
const int greenLED = 3;
const int redLED = 5;

// NRF
RF24 RF24Rx(8, 9); // CE, CSN
const byte address[6] = "AABBC";

// i2c slave addresses
#define i2cEthernet 40 //address of this component
#include "./modules/i2c.h"

LiquidCrystal_I2C lcd(0x26, 16, 2);

const char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"Air Quality Alarm" //2
  ,"Reed Switched" //3
  ,"Ultrasonic On" //4
  ,"Hall Magnetized" //5
  ,"Linear Hall" //6
  ,"Sensor Touched" //7
  ,"High Temperature" //8
  ,"Mercury Tilted" //9
  ,"Alarm # 10" //10
  ,"Alarm: Ultrasonic" //11
  ,"Alarm: Laser Tripwire" //12
  ,"Alarm: Reed Switch" // 13
  ,"Humid Environment" // 14
  ,"Alarm # 15" //15
  ,"Alarm" //16
};

// component registry
#include "./modules/buzzer2.h"
#include "./modules/led.h"
#include "./modules/lcd.h"

// alarm Protocol
void initAlarm(){
	initLED(redLED);
	
	RF24Rx.begin();
	RF24Rx.openReadingPipe(0, address);   //Setting the address at which we will receive the data
	RF24Rx.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
	RF24Rx.startListening();              //This sets the module as receiver
	
	initLCD();
	
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
		int systat = intdata;
		doLCD(lcdMessage[systat]);
		if(systat > 0){
			setAlarm = HIGH;
		}
   else{
    setAlarm = LOW;
   }
	}
	 else{
		doLCD(lcdMessage[0]);
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
