//////////////////////////////////////////
// buzzer v2
float sinVal;
int toneVal;
void doBuzzerOn(int pin){
	//for(int i=3;i<=11;i+=2){
		for(int hz = 440; hz < 1000; hz++){
			tone(pin, hz, 50);
			delay(5);
		}
		for(int hz = 1000; hz > 440; hz--){
			tone(pin, hz, 50);
			delay(5);
		}
    //}
    noTone(pin);
	delay(500);
}
void doBuzzerOff(int pin){
	noTone(pin);
}

void initBuzzer(int pin){
	pinMode(pin,OUTPUT);
}
