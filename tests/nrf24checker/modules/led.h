

void doLED(int pin, int signal){
	digitalWrite(pin,signal);
}

void initLED(int Pin){
	pinMode(Pin,OUTPUT);
	doLED(Pin,HIGH);
	delay(10);
	doLED(Pin,LOW);
}
