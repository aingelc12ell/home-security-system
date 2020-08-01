int shockPin = 3; //Pin for the shock sensor

int shocked; //Variable to store the shk reading

void initShock() 
{
  Serial.begin(9600); //Start the serial connection to the computer
  pinMode(shockPin, INPUT); //Make the pin you used an input on the Arduino
}

void checkShock() 
{
  shocked = digitalRead(shockPin);
  Serial.print("Shock status: ");
  Serial.println(shocked);
  delay(2000); 
  /*
  if(digitalRead(shockPin) == HIGH) //Read the shock sensor
  {
    Serial.println("Shock Detected"); //Print out that we have been shaken
    Serial.println("Resetting...");
    delay(500); //Wait half a second before reading again
  }
  */
}

////////////////////////////////////
void setup(){
	initShock();
}

void loop(){
	checkShock();
}
