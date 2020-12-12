// include libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// setup components
int setAlarm = 0, systat;
int alarmCounter = 5; // cycles to delay checking
float uhDistance,temperature,humidity,airquality;

// thresholds
long uhThreshold = 10; // in centimeters; distance to trigger alarm
long mqThreshold = 400; // air quality
long humidThreshold = 950; // humidity
long tempThreshold = 35; //temperature

// pin registry
#define buzzerPin 3
#define greenLED 7
#define redLED 6
#define usTrigPin 5
#define usEchoPin 4
#define MQApin A1
#define MQDpin 2
#define HT202Apin A0
#define HT202Dpin 8

// KY-001 temperature sensor
#define KY001pin 9

OneWire oneWireKY001(KY001pin);
DallasTemperature KY001(&oneWireKY001);

// component registry
#include "./modules/buzzer2.h"
#include "./modules/led.h"
#include "./modules/ultrasonic.h"
#include "./modules/singleDigitalPin.h"
#include "./modules/KY-001-temperature.h"
#include "./modules/hr202.h"

// alarm Protocol
void initAlarm(){
	initLED(redLED);
	initBuzzer(buzzerPin);
}
void doAlarm(){
	Serial.print("Status : ");
	Serial.println(setAlarm);
	if(setAlarm > 0){
		Serial.println("ALARM!!!! ALARM!!!!");
		doLED(redLED,HIGH);
		//doBuzzerOn(buzzerPin);
	}
}

// modules
void initModules(){
	initLED(greenLED);
	initUltraSonic(usTrigPin,usEchoPin);
	initKY001();
	
	pinMode(HT202Apin, INPUT);
	pinMode(HT202Dpin, INPUT);
	
	pinMode(MQApin, INPUT);
	pinMode(MQDpin, INPUT);
}
void calibrateModules(){
 
	temperature = checkKY001();
  
	humidity = getHumidity(HT202Apin,temperature);
	Serial.print("Humidity: ");
    Serial.println(humidity);
    
	airquality = analogRead(MQApin);
	Serial.print("Air Quality: ");
    Serial.println(airquality);
    
	uhDistance = checkUltraSonic(usTrigPin,usEchoPin);
}
void checkModules(){
	uhDistance = checkUltraSonic(usTrigPin,usEchoPin);
	if(uhDistance <= uhThreshold){
		setAlarm = 4;
	}
	else{
		setAlarm = 0;
	}
	
	//if(setAlarm == 0)
	{
		temperature = checkKY001();
		if(temperature >= tempThreshold){
			setAlarm = 8;
		}
	}
	if(setAlarm == 0 && temperature > 10)
	{
		humidity = getHumidity(HT202Apin,temperature);
		systat = digitalRead(HT202Dpin);
		Serial.print("Humidity: ");
		Serial.println(humidity);
		if(humidity >= humidThreshold){
			setAlarm = 14;
		}
	}
	//if(setAlarm == 0)
	{
		airquality = analogRead(MQApin);
		systat = digitalRead(MQDpin);
		Serial.print("Air Quality: ");
		Serial.println(airquality);
		if(airquality >= mqThreshold){
			setAlarm = 2;
		}
	}

}

// main functions
void setup(){
  Serial.begin(9600);
	initAlarm();
	initModules();
}
void loop(){
	doLED(greenLED,HIGH);
	if(alarmCounter > 0){
		doLED(redLED,HIGH);
		Serial.print("calibrating ");
		Serial.println(alarmCounter);
		calibrateModules();
		alarmCounter--; // give time for system to warm up if needed
		delay(1000);
	}else{
		doLED(redLED,LOW);
		//Serial.println("checking modules");
		checkModules();
		doAlarm();
		delay(500);
	}
	doLED(greenLED,LOW);
    delay(500);
}
