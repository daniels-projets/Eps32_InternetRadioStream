
void Affiche_Liste() {

     numeroChoix = 99;
     tft.fillRect(20, 20, 440, 250, TFT_BLACK);
     drawBmp("/b_list.bmp", 292, 281);
     listePointeur = 0;
     for (listeLigne = 25; listeLigne <= 245; listeLigne += 20) {
          tft.setTextColor(TFT_DARKGREY);       
          tft.drawString(stationListe[listePointeur], 40, listeLigne, 4); listePointeur += 1;
         }

     if (initialListe == true) {
         initialListe = false,
         pointeur = 0; choixLigne = 25;
         tft.setTextColor(TFT_LIGHTGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);      
        } else {
         tft.setTextColor(TFT_LIGHTGREY);       
         tft.drawString(stationListe[pointeur], 40, choixLigne, 4);                
        }
Serial.println(stationListe[pointeur]);
   
}
