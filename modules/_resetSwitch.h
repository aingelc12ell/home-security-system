
int  resetButton = 11;

void initResetButton(){
	pinMode(resetButton,INPUT);
}

void checkResetButton(){
	int state = digitalRead(resetButton);
	if(state == HIGH){
		Serial.print("...switching");
		Serial.print("..changing state from ");
		Serial.print(setAlarm == HIGH ? "HIGH" : "LOW");
		
		/*
		systemUp = systemUp == HIGH ? LOW : HIGH;
		if(systemUp == HIGH){ //low to high
			codeShow(1);
		}
		else{
			codeShow(0);
		}
		*/
		
		setAlarm = setAlarm == HIGH ? LOW : HIGH;
		
		Serial.print(" to ");
		Serial.println(setAlarm == HIGH ? "HIGH" : "LOW");
		if(setAlarm == HIGH){ //low to high
			Serial.println("[[[[[[  SWITCH ]]]]]");
			codeShow(1);
		}
		else{
			codeShow(0);
		}
	}
}