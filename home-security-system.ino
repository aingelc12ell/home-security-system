#include <Wire.h>

int systemStatus = 0; // status to be reflected in the sequence
int i2cID = 9;
int buttonPin = 7;
int signalInterval = 10;
int signalIntervalDefault = 10;

//////////////////////////////////////////
// lights
int codeFirstPin = 26;
int codeLastPin = 33;
int codeArray[16][8] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,0,0,1,1}, //9
  {1,1,1,0,1,1,1}, //A
  {0,0,1,1,1,1,1}, //B
  {1,0,0,1,1,1,0}, //C
  {0,1,1,1,1,0,1}, //D
  {1,0,0,1,1,1,1}, //E
  {1,0,0,0,1,1,1}, //F
};
int gyrbPin[3] = {10,9,11}; //pin series for green,yellow,red
int gyrLED[16][3] = {
  {0,0,0}, //0
  {1,0,0}, //1
  {1,0,0}, //2
  {1,1,0}, //3
  {1,1,0}, //4
  {1,1,0}, //5
  {0,1,0}, //6
  {0,1,0}, //7
  {0,1,0}, //8
  {0,1,0}, //9
  {0,1,1}, //10
  {0,1,1}, //a
  {0,1,1}, //b
  {0,1,1}, //c
  {0,1,1}, //e
  {0,0,1}, //f
};
void initCodeLights(){
  for(int pin = codeFirstPin; pin <= codeLastPin ; pin++){
    pinMode(pin, OUTPUT);
  }
  for(int pin = 0; pin < 3; pin++){
    pinMode(gyrbPin[pin],OUTPUT);
  }
}
void setLEDStatus(int x) {
  for(int pin = codeFirstPin; pin <= codeLastPin ; pin++){
    digitalWrite(pin, 1 - codeArray[x][pin - codeFirstPin]);
  }
  for(int pin = 0; pin < 3; pin++){
    digitalWrite(gyrbPin[pin],gyrLED[x][pin]);
  }
}

//////////////////////////////////////////
// buzzer
float sinVal;
int toneVal;
int buzzer = 12;
void soundBuzzer(){
	for(int x=0; x<180; x++){
        sinVal = (sin(x*(3.1412/180)));
        toneVal = 2000+(int(sinVal*1000));
        tone(buzzer, toneVal);
        delay(20); 
    }
    delay(1000);
    noTone(buzzer);
}
void initBuzzer(){
	pinMode(buzzer,OUTPUT);
}

////////////////////////////////////////// alarm status
void setAlarm(){
  Serial.println("Alarm|Alarm|Alarm|Alarm|Alarm|Alarm");
	soundBuzzer();
}
void setStatus(int x){
	int i = x % 16;
  Serial.print("at status: ");
  Serial.println(i);
	setLEDStatus(i);
	if(i == 15){
		setAlarm();
	}
}

void initI2CSlave(){
  Wire.begin(i2cID); 
  Wire.onReceive(statusReceiver);
}
void statusReceiver(int bytes){
  if(systemStatus < 15){
  	int x = Wire.read();    // read one character from the I2C
  	Serial.print("reading wire : ");
  	Serial.println(x);
  	systemStatus = x;
  	setStatus(x);
  }
  else{
    Serial.println("system is on alarm");
    setAlarm();
  }
	delay(100);
}
//////////MODULES//////////////////////////////////////////////

////////////////////////////////////////////////////////
void initModules(){
  // initialize modules here
}
void checkModules(){
  // series of checks
}
////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);  
  initCodeLights();
  initBuzzer();
  initI2CSlave();
  initModules();
}

void loop() {
    delay(1000);
    if(systemStatus == 15 && digitalRead(buttonPin) == HIGH){
        // can only reset if had already been running in signalInterval iteration
        Serial.println("button is High, resetting..");
        systemStatus = 0;
        setStatus(systemStatus);
        statusReceiver(0);
        signalInterval = signalIntervalDefault;
    }
    
    // SYSTEM STATUS TEST
    /*systemStatus = systemStatus % 16;
    if(systemStatus < 15){
      setStatus(systemStatus);
      systemStatus++;
    }*/
    Serial.print("systemStatus: ");
    Serial.println(systemStatus);
    
    // main checker
    checkModules();
    
    // counter
    signalInterval--;
    signalInterval = signalInterval < 0 ? 0 : signalInterval;
    Serial.print("Interval: ");
    Serial.println(signalInterval);
}
