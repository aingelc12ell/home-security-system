//KY017 Mercury open optical module

void initMercuryTilt(int pin){
	pinMode(pin,INPUT);
}
void checkMercuryTilt(int pin, int alarmStatus){
  int val = digitalRead (pin) ;// read the values assigned to the digital interface 3 val
  if (val == HIGH) // When the mercury tilt switch sensor detects a signal, LED flashes
  {
	systemStatus = alarmStatus;
  }
  Serial.print("Mercury tilt: ");
  Serial.println(val);
}
