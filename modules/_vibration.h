int vibratePin = 20;


void isVibrating(){
	Serial.println("[[[[[[  VIBRATION ]]]]]");
	setAlarm = HIGH;
	codeShow(6);
}

void initVibration(){
	pinMode(vibratePin, INPUT);
	attachInterrupt(digitalPinToInterrupt(vibratePin),isVibrating,RISING);
}

void checkVibration(){
	
	/* int isVibrating = digitalRead(vibratePin);
	if(isVibrating == LOW){
		Serial.println("vibration switched to LOW");
	}
	else{
		Serial.println("vibration switched to HIGH");
	} */
	
}