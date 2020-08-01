// replace Reed with id name
int openReedPin = 45;

void initReedSwitch(){
	pinMode(openReedPin,INPUT);
}

void checkReedSwitch(){
	int openCheck = digitalRead(openReedPin);
	if(openCheck == LOW){ //low: circuit is closed; HIGH: open
		Serial.println("[[[[[[  REED ]]]]]");
		setAlarm = HIGH; //do what?
		codeShow(7);
	}
}