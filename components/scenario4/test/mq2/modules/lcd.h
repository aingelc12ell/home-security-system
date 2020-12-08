
void initLCD(){
  lcd.begin();
  lcd.backlight();
}

void displayLCD(int lstart,int lline,char *message){
	lcd.setCursor(lstart,lline);
	lcd.print(message);
}
	
void doLCD(char *message){
	lcd.clear();
	Serial.print(" Message: ");
	Serial.println(message);
	displayLCD(0,0,message);
}