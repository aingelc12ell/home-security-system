#include <Wire.h>
int laserPin = 4;
int ldrPin = A2;
int ledPin = 13;
int alarmCycle = 0;
int alarmDefault = 500; // n/100 seconds before next alarm
int alarmThreshold = 200;

void initTripWire() {
  pinMode(laserPin,OUTPUT);
  pinMode(ldrPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Wire.begin();
}
void relayTripWireAlarm(){
  Wire.beginTransmission(9); //send to mega
  Wire.write(12); //bound with lcd message
  Wire.endTransmission();
  delay(500);
}
void checkTripWire() {
    digitalWrite(laserPin,HIGH);
    delay(10);
    int sensorValue = analogRead(3);
    /*digitalWrite(ledPin, HIGH);
    delay(sensorValue);
    digitalWrite(ledPin, LOW);
    delay(sensorValue);*/
    Serial.print("Light: ");
    Serial.println(sensorValue, DEC);
    //delay(1000);
    if(sensorValue < alarmThreshold){
      if(alarmCycle % alarmDefault == 0){
        Serial.println("Alarm Alarm Alarm Alarm Alarm Alarm Alarm Alarm Alarm");
        relayTripWireAlarm();
      }
      alarmCycle++;
    }
    else{
      alarmCycle--;
    }
    alarmCycle = alarmCycle < 1 ? 0 : alarmCycle;
    Serial.print("ct : ");
    Serial.println(alarmCycle);
}

/////////////////
void setup(){
  Serial.begin(9600);
  initTripWire();
}
void loop(){
  checkTripWire();
}
