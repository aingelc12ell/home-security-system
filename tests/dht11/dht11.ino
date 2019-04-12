#include <dht.h>
dht DHT;
int dht11Pin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(dht11Pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = DHT.read11(dht11Pin);
  if(DHT.temperature > -999 && DHT.humidity > -999){
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
  }
  delay(1000);
}
