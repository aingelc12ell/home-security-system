
//int flameDPin = 22; //digital
int flameAPin = 2; //analog
int flameThreshold = 120;

void initFlame(){
	//pinMode(flameDPin,INPUT);
}

void checkFlame(){
	//int flameDVal = digitalRead(flameDPin);
	int flameAVal = analogRead(flameAPin);
	
	Serial.print("Flame = (A): ");
	Serial.println(flameAVal);
	//Serial.print(" (D): ");
	//Serial.println(flameDVal);
	
	//if(flameDVal == HIGH){
		
	//}
	if(flameAVal < flameThreshold){
		Serial.println("[[[[[[  FLAME ]]]]]");
		systemStatus = 15;
	}
	else{
		systemStatus = systemStatus > 12 ? systemStatus : 0;
	}
}