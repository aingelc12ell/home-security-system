#include <Wire.h>

int systemStatus = 0; // status to be reflected in the sequence
int i2cID = 9; //slave address
int buttonPin = 7;
int signalInterval = 10;
int signalIntervalDefault = 10;

/*
ACTUATOR MODULES
 */
#include "modules/buzzer.h"
#include "modules/segmentLED.h"
#include "modules/relaySwitch.h"
#include "modules/ethernetRelay.h"
////////////////////////////////////////// alarm status
void setAlarmOn(int x){
	Serial.println("Alarm|Alarm|Alarm|Alarm|Alarm|Alarm");
	// soundBuzzerOn();
  // relaySwitchOn();
  sendEthernetSignal(x);
}
void setAlarmOff(){
  Serial.println("Alarm Off");
  soundBuzzerOff();
  relaySwitchOff();
  sendEthernetSignal(0);
}
void initAlarm(){
  initCodeLights();
  //initBuzzer();
  initI2CSlave();
  //initRelaySwitch();
  initEthernetRelay();
}
void setStatus(int x){
	int i = x % 16;
	Serial.print("at status: ");
	Serial.println(i);
	setLEDStatus(i);
	if(i == 15){
		setAlarmOn(i);
   delay(1000);
	}
}

void initI2CSlave(){
  Wire.begin(i2cID); 
  Wire.onReceive(statusReceiver);
}
void statusReceiver(int bytes){
  if(systemStatus < 15){
  	int x = Wire.read();    // read one character from the I2C
  	Serial.print("........................reading wire : ");
  	Serial.println(x);
  	systemStatus = x;
  	setStatus(x);
  }
  else{
    Serial.println("system is on alarm");
    setAlarmOn(15);
  }
	delay(100);
}
/**
SENSOR MODULES: 
	attached to the Arduino Mega
	defined and configured on /modules/
	requires an init<Module>() and check<Module>() 
		to be included in the initModules() and checkModules() below
*/
#include "modules/flame.h"

////////////////////////////////////////////////////////
void initModules(){
  // initialize modules here
  initFlame();
}
void checkModules(){
  // series of checks
  checkFlame();
}
////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);  
  initAlarm();
  initModules();
}

void loop() {
    delay(1000);
    if(systemStatus == 15 && digitalRead(buttonPin) == HIGH){
        // can only reset if had already been running in signalInterval iteration
        Serial.println("button is High, resetting..");
        systemStatus = 0;
        setStatus(systemStatus);
        setAlarmOff();
        statusReceiver(0);
        signalInterval = signalIntervalDefault;
    }
    
    // SYSTEM STATUS TEST
    /*systemStatus = systemStatus % 16;
    if(systemStatus < 15){
      setStatus(systemStatus);
      systemStatus++;
    }*/
    
    // main checker
    checkModules();
	  systemStatus = systemStatus < 1 ? 0 : systemStatus;
    Serial.print("systemStatus: ");
    Serial.println(systemStatus);
    
    setStatus(systemStatus);
    
    // counter
    signalInterval--;
    signalInterval = signalInterval < 0 ? 0 : signalInterval;
    Serial.print("Interval: ");
    Serial.println(signalInterval);
}
