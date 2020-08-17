
#include <LiquidCrystal_I2C.h>
int codeFirstPin = 2;
int codeLastPin = 9;
unsigned long changeLightTime;
/*
 *    a
 * f     b
 *    g
 * e     c
 *    d    p
 */
//int codeArray[8] = {0,0,0,0,0,0,0}; //using dec2bin
int msgCount = 16; // count for both codeArray and Message
int codeArray[16][8] ={
  {1,1,1,1,1,1,0,0}//0
  ,{0,1,1,0,0,0,0,0}//1
  ,{1,1,0,1,1,0,1,0}//2
  ,{1,1,1,1,0,0,1,0}//3
  ,{0,1,1,0,0,1,1,0}//4
  ,{1,0,1,1,0,1,1,0}//5
  ,{1,0,1,1,1,1,1,0}//6
  ,{1,1,1,0,0,0,0,0}//7
  ,{1,1,1,1,1,1,1,0}//8
  ,{1,1,1,1,0,1,1,0}//9
  ,{1,1,1,0,1,1,1,0}//A
  ,{0,0,1,1,1,1,1,0}//b
  ,{1,0,0,1,1,1,0,0}//C
  ,{0,1,1,1,1,0,1,0}//d
  ,{1,0,0,1,1,1,1,0}//E
  ,{1,0,0,0,1,1,1,0}//F
};
char *Message[] = {
  "System Normal"
  ,"Fire Alarm"
  ,"A#2"
  ,"A#3"
  ,"A#4"
  ,"A#5"
  ,"A#6"
  ,"A#7"
  ,"Alarm # 8"
  ,"Alarm # 9"
  ,"Alarm # 10"
  ,"Alarm # 11"
  ,"Alarm # 12"
  ,"Alarm # 13"
  ,"Alarm # 14"
  ,"Alarm # 15"
};
/* //dec2bin
void convertDecToBinRev(int Dec) {
  for(int i = 7 ; i >= 0 ; i--) {
    if(pow(2, i)<=Dec) {
      Dec = Dec - pow(2, i);
      codeArray[8-(i+1)] = 0;
    } else {
      codeArray[8-(i+1)] = 1;
    }
  }
}
void convertDecToBin(int Dec) {
  // Dec = Dec % 2 > 0 ? Dec - 1 : Dec;
  for(int i = 7 ; i >= 0 ; i--) {
    if(pow(2, i)<=Dec) {
      Dec = Dec - pow(2, i);
      codeArray[8-(i+1)] = 1;
    } else {
      codeArray[8-(i+1)] = 0;
    }
  }
}*/
LiquidCrystal_I2C lcd(0x27, 16, 2);
void initLCD(){
  lcd.begin();
  lcd.backlight();
}
void showLCD(int i){
  lcd.clear();
  lcd.print(i);
  lcd.setCursor (0,1);
  lcd.print(Message[i]);
}
void codeShow(int i) {
  showLCD(i);
	//convertDecToBin(i);
	for(int pin = codeFirstPin; pin <= codeLastPin ; pin++){
		digitalWrite(pin, 1 - codeArray[i][pin - codeFirstPin]);
    // digitalWrite(pin, codeArray[pin - codeFirstPin]); //using dec2bin
	}
}

void initCodeLights(){
	for(int pin = codeFirstPin; pin <= codeLastPin ; pin++){
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}
}

void doCodeLight(){
	/*if((millis() - changeLightTime) > 60000){
		codeShow(0);
	}*/
}

void setup(){
  Serial.begin(9600);
  initCodeLights();
  initLCD();
}

void loop(){
  for(int i=0; i < msgCount; i++){
    Serial.println(i);
    codeShow(i);
    delay(1000);
  }
}
