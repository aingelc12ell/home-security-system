int setAlarm = LOW;

#include "vibration.h"

void setup() {
  Serial.begin(9600);
  initVibration();
}

void loop() {
  Serial.print("Vibrating? ");
  Serial.println(setAlarm==HIGH ? " YES" : " NO");
  delay(500);
  if(setAlarm==HIGH){
    delay(1000);
    Serial.println("Resetting from HIGH state");
    setAlarm=LOW; // revert
  }
}
