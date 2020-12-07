//////////////////////////////////////////
// buzzer
float sinVal;
int toneVal;
int buzzer = 12;
void soundBuzzerOn(){
	/*for(int x=0; x<180; x++){
        sinVal = (sin(x*(3.1412/180)));
        toneVal = 2000+(int(sinVal*1000));
        tone(buzzer, toneVal);
        delay(20); 
    }
    */
	
	//for(int i=3;i<=11;i+=2){
		for(int hz = 440; hz < 1000; hz++){
			tone(buzzer, hz, 50);
			delay(5);
		}
		for(int hz = 1000; hz > 440; hz--){
			tone(buzzer, hz, 50);
			delay(5);
		}
    //}
    noTone(buzzer);
	delay(500);
}
void soundBuzzerOff(){
	noTone(buzzer);
}
void initBuzzer(){
	pinMode(buzzer,OUTPUT);
}