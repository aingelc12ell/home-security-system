int vibratePin = 3;


void isVibrating(){
	setAlarm = HIGH;
	//codeShow(6);
}

void initVibration(){
	pinMode(vibratePin, INPUT);
	attachInterrupt(digitalPinToInterrupt(vibratePin),isVibrating,RISING);
}