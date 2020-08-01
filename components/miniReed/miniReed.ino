int mReedPin = 2;

int mReed;

void initMiniReed() 
{
  Serial.begin(9600);
  pinMode(mReedPin, INPUT);
}

void checkMiniReed() 
{
  delay(2000); 
  mReed = digitalRead(mReedPin);
  Serial.print("Switch status: ");
  Serial.println(mReed);
  /*
  if(digitalRead(mReedPin) == HIGH) //Read the shock sensor
  {
    Serial.println("Switch Activated"); //Print out that we have been shaken
    Serial.println("Resetting...");
    delay(500); //Wait half a second before reading again
  }
  */
}

////////////////////////////////////
void setup(){
  initMiniReed();
}

void loop(){
  checkMiniReed();
}
