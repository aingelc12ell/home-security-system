
int flameDPin = 50; //digital
int flameAPin = 2; //analog
int flameThreshold = 120;
int flameDelayCounter = 5;
int flameAlarm = 0;

void initFlame(){
	//pinMode(flameDPin,INPUT);
}

void checkFlame(){
	int flameDVal = digitalRead(flameDPin);
	/*int flameAVal = analogRead(flameAPin);*/
	
	/*Serial.print("Flame = (A): ");
	Serial.println(flameAVal);*/
	Serial.print("Flame (D): ");
	Serial.println(flameDVal);
	
	if(flameDVal == HIGH){
		Serial.println("[[[[[[  FLAME ]]]]]");
		systemStatus = 1; //bound code for relay
		flameAlarm = 1;
	}
	else{
		if(flameAlarm > 0){
			if(flameDelayCounter > 0){
				flameDelayCounter--;
			}else{
				flameAlarm = 0;
				systemStatus = 0;
				flameDelayCounter = 5;
			}
		}
	}
	/*if(flameAVal < flameThreshold){
		Serial.println("[[[[[[  FLAME ]]]]]");
		systemStatus = 1; //bound code for relay
	}
	else{
		systemStatus = systemStatus > 0 ? systemStatus : 0;
	}
	*/
}