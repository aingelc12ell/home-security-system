

void doLights(){
/*	if(setAlarm == HIGH){
		digitalWrite(greenLED,LOW);
		digitalWrite(redLED,HIGH);
		delay(50);
		digitalWrite(redLED,LOW);
		delay(150);
		digitalWrite(redLED,HIGH);
		delay(250);
		digitalWrite(redLED,LOW);
		delay(350);
	}
	else{
		digitalWrite(redLED,LOW);
		digitalWrite(greenLED,HIGH);
		delay(500);
		digitalWrite(greenLED,LOW);
		delay(500);
	}*/
}

void doLED(int pin, int signal){
	digitalWrite(pin,signal);
}

void initLED(int Pin){
	pinMode(Pin,OUTPUT);
	doLED(Pin,HIGH);
	delay(10);
	doLED(Pin,LOW);
}