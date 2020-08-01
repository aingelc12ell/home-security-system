/**
Singular Ultrasonic Sensor
*/
#include <Wire.h>

int ledPin = 10;
int usEcho = 9;
int usTrigger = 8;
int cmThresholdRed = 10; // trigger when close to distance in centimeters
int cmThresholdGreen = 2000;
int setInterval = 5;
int slaveI2C = 9;
int systemStatus = 0;

void blinkLED(){
	for(int i=0; i < 10; i++){
		digitalWrite(ledPin,HIGH);
		delay(10);
		digitalWrite(ledPin,LOW);
		delay(10);
	}
}

void setup(){
	Serial.begin(9600);
	pinMode(ledPin,OUTPUT);
	pinMode(usEcho,INPUT);
	pinMode(usTrigger,OUTPUT);
	Wire.begin();
}

void relayStatus(int x){
  Serial.print("sending: ");
  Serial.println(x);
	delay(200);
 if(x==15){
  blinkLED();
  Serial.println("relaying signal......");
	Wire.beginTransmission(slaveI2C);
	Wire.write(15);
	Wire.endTransmission();
 delay(3000);
 }
}

void loop(){
	long duration, cm;
	digitalWrite(usTrigger,HIGH);
	delayMicroseconds(1000);
	digitalWrite(usTrigger,LOW);

	duration = pulseIn(usEcho, HIGH);

	cm = (duration/2) / 29.1;
	//inches = (duration/2) / 74; 
	Serial.print("Distance: ");
	Serial.print(cm);
	Serial.println(" cm");
	
	cm = cm > cmThresholdGreen ? cmThresholdGreen : cm;
  cm = cm < cmThresholdRed ? cmThresholdRed : cm;
	systemStatus = map(cm,cmThresholdGreen,cmThresholdRed,0,15);
	
	relayStatus(systemStatus);
	
	delay(1000);	
}
