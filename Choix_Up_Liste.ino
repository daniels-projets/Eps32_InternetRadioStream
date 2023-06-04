
void Choix_Up_Liste() {

     numeroChoix = 99;
     drawBmp("/b_up.bmp", 144, 281);

     if (pointeur > 0) {
         tft.setTextColor(TFT_DARKGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);      
         pointeur -= 1; choixLigne -= 20;
         tft.setTextColor(TFT_LIGHTGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);      
        } else {
         tft.setTextColor(TFT_DARKGREY);       
         tft.drawString(stationListe[0], 40, 25, 4);      
         pointeur = 11; choixLigne = 245;
         tft.setTextColor(TFT_LIGHTGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);           
        }    
Serial.println(stationListe[pointeur]); 
   
} 
