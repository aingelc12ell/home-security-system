
int metalTouchStatus = 0;
function initMetalTouch(int pin){
	pinMode(pin,INPUT);
}
function checkMetalTouch(int pin,int alarmStatus){
	metalTouchStatus = digitalRead(pin);
	if(metalTouchStatus == HIGH){
		systemStatus = alarmStatus;
	}
}