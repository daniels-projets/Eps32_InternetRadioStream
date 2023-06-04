
void Choix_Down_Liste() {

     numeroChoix = 99;
     drawBmp("/b_down.bmp", 53, 281);

     if (pointeur < 11) {
         tft.setTextColor(TFT_DARKGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);      
         pointeur += 1; choixLigne += 20;
         tft.setTextColor(TFT_LIGHTGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);      
        } else {
         tft.setTextColor(TFT_DARKGREY);       
         tft.drawString(stationListe[11], 40, 245, 4);      
         pointeur = 0; choixLigne = 25;
         tft.setTextColor(TFT_LIGHTGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);           
        }    
Serial.println(stationListe[pointeur]);    
}     
