int redLED = 13;
int greenLED = 12;


void initLights(){
	pinMode(redLED,OUTPUT);
	pinMode(greenLED,OUTPUT);
	digitalWrite(redLED,LOW);
	digitalWrite(greenLED,HIGH);
}

void doLights(){
	if(setAlarm == HIGH){
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
	}
}