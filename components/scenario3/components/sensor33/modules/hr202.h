int oms0G[] = { 10000, 10000, 6400, 2900, 1400, 700, 370, 190, 105, 62, 38, 23,15, 10, 7 };
int oms5G[] = { 10000, 10000, 4600, 2100, 1000, 500,260, 140, 80, 48, 30, 18,12, 8, 5 };
int oms10G[] = { 10000, 7000, 3200, 1500, 750, 380, 200, 110, 62, 37, 24, 15,10, 7, 5 };
int oms15G[] = { 10000, 5000, 2300, 1100, 540, 280, 150, 84, 50, 30, 19, 12, 8,6, 4 };
int oms20G[] = { 6700, 3400, 1750, 850, 420, 210, 115, 64, 39, 24, 15, 10, 7, 5,3 };
int oms25G[] = { 5000, 2600, 1300, 630, 310, 160, 87, 49, 31, 19, 13, 8, 6, 4, 3 };
int oms30G[] = { 3900, 1900, 970, 460, 235, 125, 69, 39, 25, 16, 10, 7, 5, 3, 2 };
int oms35G[] = { 3000, 1500, 740, 380, 190, 100, 56, 33, 20, 13, 9, 6, 4, 3, 2 };
int humedad[] = { 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90 };
float getHumidity(int HUMEDAD,float degreesCelsius) {
   // read the value from the sensor:
   int HIH4030_Value = analogRead(HUMEDAD);
   float trueRH = 0;
   int* arrayOMS;
   if (degreesCelsius >= 35) {
      arrayOMS = oms35G;
   } else if (degreesCelsius >= 30) {
      arrayOMS = oms30G;
   } else if (degreesCelsius >= 25) {
      arrayOMS = oms25G;
   } else if (degreesCelsius >= 20) {
      arrayOMS = oms20G;
   } else if (degreesCelsius >= 15) {
      arrayOMS = oms15G;
   } else if (degreesCelsius >= 10) {
      arrayOMS = oms10G;
   } else if (degreesCelsius >= 5) {
      arrayOMS = oms5G;
   } else if (degreesCelsius >= 0) {
      arrayOMS = oms0G;
   }
   for (int i = 0; i < 15; i++) {
      if (HIH4030_Value > arrayOMS[i]) {
         if (i > 0) { //Aproximamos el resultado (Si no es ni el primero, ni el último)
            //HIH4030_Value //Ohmios actuales
            int ohmsRM = arrayOMS[i - 1];
            int humRM = humedad[i - 1];
            int ohmsRm = arrayOMS[i];
            int humRm = humedad[i];
            int intervaloOHMS = ohmsRM - ohmsRm;
            int valIOMS = HIH4030_Value - ohmsRm;
            float mult = (float) valIOMS * 100;
            float porcOhms = ((float) mult) / intervaloOHMS; //Porcentaje del rango de ohms;
            int intervaloR = humRM - humRm;
            trueRH = ((porcOhms * intervaloR) / 100) + humRm;
         } else {
            int ohmsRM = arrayOMS[i];
            int humRM = humedad[i];
            int ohmsRm = arrayOMS[i + 1];
            int humRm = humedad[i + 1];
            int intervaloOHMS = ohmsRM - ohmsRm;
            int valIOMS = HIH4030_Value - ohmsRm;
            float mult = (float) valIOMS * 100;
            float porcOhms = ((float) mult) / intervaloOHMS; //Porcentaje del rango de ohms;
            int intervaloR = humRM - humRm;
            trueRH = ((porcOhms * intervaloR) / 100) + humRm;
         }
         break;
      }
   }
   return trueRH;
}