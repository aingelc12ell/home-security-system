
//int laserPin = 7; //digital
int photoPin = 0; //analog

void setup() {
  Serial.begin(9600);
  //pinMode(laserPin,OUTPUT);
  //pinMode(photoPin,INPUT);
}

void loop() {
  //digitalWrite(laserPin,HIGH);
  int lightVar = analogRead(photoPin);
  Serial.print("Light read: ");
  Serial.println(lightVar);
  delay(1000);
}
