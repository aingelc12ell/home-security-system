// replace <-> with id name
int open<->Pin = 0;

void init<->Switch(){
	pinMode(open<->Pin,INPUT_PULLUP);
}

void check<->Switch(){
	if(digitalRead(open<->Pin) == LOW){ //circuit is closed
		setAlarm = HIGH; //do what?
	}
}