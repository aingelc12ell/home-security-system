dht DHT;
int dht11Pin = 7;
float dhTempThreshold = 75;
float dhHumidThreshold = 85;

void initDHT11() {
  pinMode(dht11Pin,INPUT);
}

void checkDHT11() {
  // put your main code here, to run repeatedly:
  int chk = DHT.read11(dht11Pin);
  float dhttemp = DHT.temperature;
  float dhthumid = DHT.humidity;
  if(dhttemp > -999 && dhthumid > -999){
    Serial.print("DHT Temp = ");
    Serial.println(dhttemp);
    Serial.print("DHT Humid = ");
    Serial.println(dhthumid);
	if(dhttemp >= dhTempThreshold
		|| dhthumid >= dhHumidThreshold
	){
		Serial.println("[[[[[[  DHT ]]]]]");
		codeShow(2);
		setAlarm = HIGH;
	}
  }
  //delay(1000);
}