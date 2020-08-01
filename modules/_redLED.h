int redLED = 12;

void initRedLed(){
	pinMode(redLED,OUTPUT);
	digitalWrite(redLED,LOW);
}

void redLight(){
	if(setAlarm == HIGH){
		digitalWrite(redLED,HIGH);
		delay(50);
		digitalWrite(redLED,HIGH);
		delay(150);
		digitalWrite(redLED,HIGH);
		delay(250);
		digitalWrite(redLED,HIGH);
		delay(350);
	}
	else{
		digitalWrite(redLED,LOW);
	}
}
