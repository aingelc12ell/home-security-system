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
  {1,1,1}, //0
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
  if(x==0){
	  delay(1000);
	  for(int pin = 0; pin < 3; pin++){
		digitalWrite(gyrbPin[pin],LOW);
	  }
  }
}
