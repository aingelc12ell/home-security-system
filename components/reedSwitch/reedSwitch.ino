#include <Wire.h>

int reedPin = 2;
int reed;
int reedCounter;
int reedCounterDefault = 2; //number of iterations to send trigger
int relaySent = 0;


void initMiniReed() 
{
  Serial.begin(9600);
  pinMode(reedPin, INPUT);
  reedCounter = reedCounterDefault;
  Wire.begin();
}

void checkMiniReed() 
{
  delay(500); 
  reed = digitalRead(reedPin);
  Serial.print("Switch status: ");
  Serial.println(reed);
  Serial.print("counter : ");
  Serial.println(reedCounter);
  if(reed == HIGH) //magnet is away from switch
  {
    if(reedCounter <= 0){
      if(relaySent == 0){
        Serial.println(".........Sending ALARM");
        Wire.beginTransmission(9);
        Wire.write(15);
        Wire.endTransmission();
        relaySent = 1;
      }
      else{
        Serial.println("........in Alarm Status");
      }
    }
    else{
      Serial.print("WARNING countdown : ");
      Serial.println(reedCounter);
      reedCounter--;
    }
  }
  else{
    reedCounter++;
    if(reedCounter >= reedCounterDefault){
      if(relaySent > 0){
        relaySent = 0;
        Serial.println("....Resetting NORMAL");
      }
    }
    Serial.println("normal");
  }
  reedCounter = reedCounter < 0 ? 0 : reedCounter;
  reedCounter = reedCounter > reedCounterDefault ? reedCounterDefault : reedCounter;
}

////////////////////////////////////
void setup(){
  initMiniReed();
}

void loop(){
  checkMiniReed();
  delay(1000);
}
