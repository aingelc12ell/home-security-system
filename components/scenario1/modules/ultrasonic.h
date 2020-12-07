
// int uhTrigPin = 6;
// int uhEchoPin = 5;
long duration, cm, inches;
// int distanceThreshold = 3; // cm

void initUltraSonic(int uhTrigPin,int uhEchoPin){
	pinMode(uhTrigPin,OUTPUT);
	pinMode(uhEchoPin,INPUT);
}

long checkUltraSonic(int uhTrigPin,int uhEchoPin){
	digitalWrite(uhTrigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(uhTrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(uhTrigPin, LOW);

	pinMode(uhEchoPin, INPUT);
	duration = pulseIn(uhEchoPin, HIGH);

	cm = (duration/2) / 29.1;
	inches = (duration/2) / 74; 
	
	Serial.print("Ultrasonic reading: ");
	Serial.print(inches);
	Serial.print("in, ");
	Serial.print(cm);
	Serial.print("cm, ");
	Serial.print(cm/100);
	Serial.print("m");
	Serial.println();
	
	return cm;
	/*if(cm <= distanceThreshold && cm > 0){
		Serial.println("[[[[[[  ULTRASONIC ]]]]]");
		codeShow(9);
		setAlarm = HIGH;
	}
	duration = 0;
	*/
}