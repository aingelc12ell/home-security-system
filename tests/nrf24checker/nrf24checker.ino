/**
 * Simulates NRF24 transmission with modules attached
 */


char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"Air Quality Alarm" //2
  ,"Reed Switched" //3
  ,"Ultrasonic On" //4
  ,"Hall Magnetized" //5
  ,"Linear Hall" //6
  ,"Mercury Tilted  " //7
  ,"Alarm # 8" //8
  ,"Alarm # 9" //9
  ,"Alarm # 10" //10
  ,"Alarm: Ultrasonic" //11
  ,"Alarm: Laser Tripwire" //12
  ,"Alarm: Reed Switch" // 13
  ,"Alarm # 14" // 14
  ,"Alarm # 15" //15
  ,"Alarm" //16
};
// status to be reflected in the sequence
int systemStatus = 0; 
// number of cycles before the alarm is turned on and give way to initializations
int systemDelay = 5;
//number of cycles before the alarm is turned off and give way to checking; set 0 to check always
int alarmCounter,defAlarmCounter = 10; 

////////////////////////////////////

int LEDgreen = 5;
int LEDred = 6;
int MercuryTiltPin = 4;

#include "modules/led.h"
#include "modules/nrf24transmitter.h"
#include "modules/mercury-tilt.h"

void doAlarm(int stat){
  doLED(LEDred,stat);
  doRF24Tx();
}

void setup() {
  Serial.begin(9600);
  initLED(LEDgreen);
  initLED(LEDred);
  initRF24Tx();
  initMercuryTilt(MercuryTiltPin);
}

void checkModules() {
  if(systemStatus == 0){
    Serial.println("Checking Mercury Tilt Switch");
    checkMercuryTilt(MercuryTiltPin);
  }
}

void loop(){
  doLED(LEDgreen,HIGH);
  delay(500);
  doLED(LEDgreen,LOW);
  Serial.print("alarm counter : ");
  Serial.print(alarmCounter);
  Serial.print("  default : ");
  Serial.println(defAlarmCounter);
  
  if(alarmCounter == defAlarmCounter){
    checkModules();
  }
  if(systemStatus > 0){
    Serial.println(" !!!! ALARM !!!!");
    Serial.print("               ");
    Serial.println(lcdMessage[systemStatus]);
    doAlarm(HIGH);
    delay(1000);
  }
  else{
    systemStatus = 0; // in case the status is set to negative;
    alarmCounter--;
    doAlarm(LOW);
    if(alarmCounter < 1){
      Serial.println("Resetting...");
      alarmCounter = defAlarmCounter; //restart checking 
    }
  }
 systemDelay--;
 if(systemDelay < 0){
  systemDelay = 0;
 }

  delay(500);
}
