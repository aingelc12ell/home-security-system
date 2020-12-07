
int tapShock = 3;
int shocking = 0;
char *tapMsg;

void initTapShock(){
    pinMode(tapShock,INPUT);
}
 void checkTapShock(){
	if(shocking == 0){
      val = digitalRead(tapShock);
      if(val == HIGH){
        tapMsg = "Shock! shaking!";
        shocking = 10;
      }
      else{
        tapMsg = ""; //nothing
      }
    }
    else{
      shocking--;
    }
	return tapMsg;
 }