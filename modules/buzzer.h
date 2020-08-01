//////////////////////////////////////////
// buzzer
float sinVal;
int toneVal;
int buzzer = 12;
void soundBuzzerOn(){
	for(int x=0; x<180; x++){
        sinVal = (sin(x*(3.1412/180)));
        toneVal = 2000+(int(sinVal*1000));
        tone(buzzer, toneVal);
        delay(20); 
    }
    delay(1000);
    noTone(buzzer);
}
void soundBuzzerOff(){
	noTone(buzzer);
}
void initBuzzer(){
	pinMode(buzzer,OUTPUT);
}