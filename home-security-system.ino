
#include <LiquidCrystal_I2C.h>
//#include <MQ135.h>
#include <Wire.h>


int systemStatus = 0; // status to be reflected in the sequence
int i2cID = 9; //slave address
int buttonPin = 7;
int signalInterval = 10;
int signalIntervalDefault = 10;

//LiquidCrystal_I2C lcd(0x22, 16, 2);
//LiquidCrystal_I2C lcd2(0x26, 16, 2);

const char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"Air Quality Alarm" //2
  ,"Reed Switched" //3
  ,"Ultrasonic On" //4
  ,"Hall Magnetized" //5
  ,"Linear Hall" //6
  ,"Sensor Touched" //7
  ,"Alarm # 8" //8
  ,"Mercury Switched" //9
  ,"Alarm # 10" //10
  ,"Alarm: Ultrasonic" //11
  ,"Alarm: Laser Tripwire" //12
  ,"Alarm: Reed Switch" // 13
  ,"Alarm # 14" // 14
  ,"Alarm # 15" //15
  ,"Alarm" //16
};

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
void initLCD(){
	TCA9548A(0);
  lcd.begin();
  lcd.backlight();
  TCA9548A(1);
  lcd2.begin();
  lcd2.backlight();
}
void showLCD(int i){
	TCA9548A(0);
  lcd.clear();
  lcd.print(i);
  lcd.setCursor (0,1);
  lcd.print(lcdMessage[i]);
  
  TCA9548A(1);
  lcd2.clear();
  lcd2.print(i);
  lcd2.setCursor (0,1);
  lcd2.print(lcdMessage[i]);
  
  Serial.print(lcdMessage[i]);
}
/*
ACTUATOR MODULES
 */
 #include "modules/led.h"
#include "modules/buzzer2.h"
//#include "modules/segmentLED.h"
// #include "modules/relaySwitch.h"
//#include "modules/ethernetRelay.h"

const int redLED = 10;
const int greenLED = 11;
const int buzzer = 9;
////////////////////////////////////////// alarm status
void setAlarmOn(int x){
	Serial.println("Alarm|Alarm|Alarm|Alarm|Alarm|Alarm");
	doBuzzerOn(buzzer);
  // relaySwitchOn();
  //sendEthernetSignal(x);
  
}
void setAlarmOff(){
  Serial.println("Alarm Off");
  doBuzzerOff(buzzer);
  //relaySwitchOff();
  //sendEthernetSignal(0);
}

void statusReceiver(int bytes){
  if(systemStatus > 0){
    Serial.println("system is on alarm");
    setStatus(systemStatus);
  }
  else{
    int x = Wire.read();    // read one character from the I2C
    Serial.print("........................reading wire : ");
    Serial.println(x);
    systemStatus = x;
    setStatus(x);
  }
  delay(100);
}
void initI2CSlave(){
  Serial.println("I2CSlave Set");
  Wire.begin(i2cID); 
  Wire.onReceive(statusReceiver);
}

void initAlarm(){
	initLED(redLED);
	initLED(greenLED);
  //initLCD();
  //initCodeLights();
  initBuzzer(buzzer);
  //initI2CSlave();
  //initRelaySwitch();
  //initEthernetRelay();
}
void setStatus(int x){
	//int i = x % 16;
	Serial.print("at status: ");
	Serial.println(x);
	showLCD(x);
	setLEDStatus(x);
  if(x > 0){
    setAlarmOn(x);
    delay(1000);
  }
}

/**
SENSOR MODULES: 
	attached to the Arduino Mega
	defined and configured on /modules/
	requires an init<Module>() and check<Module>() 
		to be included in the initModules() and checkModules() below
*/
//#include "modules/flame.h"
//#include "modules/MQ135.h"
#include "modules/metaltouch.h"
////////////////////////////////////////////////////////
void initModules(){
  // initialize modules here
  //initFlame();
  //initMQ135();
  initMetalTouch(6); // define pin used by metaltouch module
}
void checkModules(){
  // series of checks
  //checkFlame();
  //checkMQ135();
  if(systemStatus == 0){
	systemStatus = checkMetalTouch(6,7);
  }
}
////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);  
  initAlarm();
  initModules();
}

void loop() {
    delay(1000);
    if(systemStatus > 0 && digitalRead(buttonPin) == HIGH){
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
