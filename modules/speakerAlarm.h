
int speakerPin = 9;
float sinVal;
int toneVal;

void initSpeaker(){
	pinMode(speakerPin,OUTPUT);
}

void doSpeaker(){
	if(setAlarm == HIGH){
		for(int x=0; x<180; x++){
			sinVal = (sin(x*(3.1412/180)));
			toneVal = 2000+(int(sinVal*1000));
			tone(speakerPin, toneVal);
			delay(2); 
		}
	}
	noTone(speakerPin);
}