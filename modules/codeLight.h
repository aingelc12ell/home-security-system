
int codeFirstPin = 46;
int codeLastPin = 53;
unsigned long changeLightTime;

int codeArray[10][8] =
{
  {0,0,0,1,0,0,0,1},//0
  {0,1,1,1,1,1,0,1},//1
  {0,0,1,0,0,0,1,1},//2
  {0,0,1,0,1,0,0,1},//3
  {0,1,0,0,1,1,0,1},//4
  {1,0,0,0,1,0,0,1},//5
  {1,0,0,0,0,0,0,1},//6
  {0,0,1,1,1,1,0,1},//7
  {0,0,0,0,0,0,0,1},//8
  {0,0,0,0,1,1,0,1} //9
};

void codeShow(int i) {
	changeLightTime = millis();
	for(int pin = codeFirstPin; pin <= codeLastPin ; pin++){
		digitalWrite(pin, codeArray[i][pin - codeFirstPin]);
	}
}

void initCodeLights(){
	for(int pin = codeFirstPin; pin <= codeLastPin ; pin++){
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}
}

void doCodeLight(){
	if((millis() - changeLightTime) > 60000){
		codeShow(0);
	}
}