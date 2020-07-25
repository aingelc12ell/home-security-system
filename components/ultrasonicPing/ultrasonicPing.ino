/**
Singular Ultrasonic Sensor
*/
// #include <Wire.h>
#include <NewPing.h>

int ledPin = 10;
#define usEcho  9
#define usTrigger  8
int cmThresholdRed = 10; // trigger when close to distance in centimeters
int cmThresholdGreen = 200;
#define cmMaxDistance 400
int setInterval = 5;
int slaveI2C = 9;
int systemStatus = 0;
float cmDistance;

NewPing ucSensor1(usTrigger,usEcho,cmMaxDistance);

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
	// pinMode(usEcho,INPUT);
	// pinMode(usTrigger,OUTPUT);
	// Wire.begin();
}

void relayStatus(int x){
  Serial.print("sending: ");
  Serial.println(x);
	delay(200);
	/*Wire.beginTransmission(slaveI2C);
	Wire.write(x);
	Wire.endTransmission();*/
 if(x > 14){
    blinkLED();
 }
}

void loop(){
  delay(20);
	cmDistance = ucSensor1.ping_cm();
	Serial.print("cm : ");
  Serial.println(cmDistance);
  
	cmDistance = cmDistance > cmThresholdGreen ? cmThresholdGreen : cmDistance;
	cmDistance = cmDistance < cmThresholdRed ? cmThresholdRed : cmDistance;
	
	 systemStatus = map(cmDistance,cmThresholdGreen,cmThresholdRed,0,15);
	
	 relayStatus(systemStatus);
	
	delay(1000);	
}
