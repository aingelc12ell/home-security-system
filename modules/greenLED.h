int greenLED = 13;

void initGreenLed(){
	pinMode(greenLED,OUTPUT);
}

void greenLightOn(){
	digitalWrite(greenLED,HIGH);
	delay(1000);
	digitalWrite(greenLED,LOW);
	delay(1000); 
}