
int flameDPin = 22; //digital
int flameAPin = 2; //analog
int flameThreshold = 100;

void initFlame(){
	pinMode(flameDPin,INPUT);
}

void checkFlame(){
	int flameDVal = digitalRead(flameDPin);
	int flameAVal = analogRead(flameAPin);
	
	Serial.print("Flame = (A): ");
	Serial.print(flameAVal);
	Serial.print(" (D): ");
	Serial.println(flameDVal);
	
	if(flameDVal == HIGH){
		
	}
	if(flameAVal < flameThreshold){
		Serial.println("[[[[[[  FLAME ]]]]]");
		codeShow(3);
		setAlarm = HIGH;
	}
}