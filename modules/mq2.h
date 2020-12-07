
#include <MQ135.h>
const int airThreshold = 700;
int airAlarm=0;
int airDelayCounter = 5;
const int ANALOGPIN=2;
MQ135 gasSensor = MQ135(ANALOGPIN);

void initMQ135(){
  
}
void checkMQ135(){
  float rzero = gasSensor.getRZero();
  Serial.print("Air quality: ");
  Serial.println(rzero);
  
  if(rzero > airThreshold){
	Serial.println("[[[[[[  AIR QUALITY ]]]]]");
	systemStatus = 2;
	airAlarm = 1;
  }
  else{
	  if(airAlarm > 0){
			if(airDelayCounter > 0){
				airDelayCounter--;
			}else{
				airAlarm = 0;
				systemStatus = 0;
				airDelayCounter = 5;
			}
	  }
  }
}

/*
void setup(){
	Serial.begin(9600);
	initMQ135();
}
void loop(){
	checkMQ135();
	delay(1000);
}*/