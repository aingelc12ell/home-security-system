
unsigned long tempTimer ;
int tempPin = 1; //analog
float tempThreshold = 75;
int tempDelayMS = 5000;

void initTempSensor(){
	
}

void checkTempSensor(){
	int tempval;               
    double data;
	if(millis() - tempTimer > tempDelayMS){
		tempTimer = millis();
		tempval = analogRead(tempPin);  
		data = (double) tempval * (5/10.24);  // convert the voltage to temperture
		Serial.print("Temperature : ");
		Serial.println(data);
		if(data > tempThreshold && data > 0){
			setAlarm = HIGH;
			Serial.println("[[[[[[  Temperature ]]]]]");
			codeShow(8); // code registry
		}
		else{
			setAlarm = LOW;
		}
	}
}