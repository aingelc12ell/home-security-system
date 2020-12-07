
int ballSwitch = 5;
int onSwitch = 0;

void initballSwitch(){
    pinMode(ballSwitch,INPUT);
}
 void checkballSwitch(){
	if(onSwitch == 0 || nrfMessage == 0){
		onSwitch = 0;
      bool val = digitalRead(ballSwitch);
      if(val == HIGH){
        nrfMessage = 3; 
        //nrfMessage = "Ball Switched! ";
        onSwitch = 5;
      }
	  else{
		  //nrfMessage = "";
		  
	  }
    }
    else{
      onSwitch--;
    }
 }