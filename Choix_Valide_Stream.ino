
void Choix_Valide_Stream() {

     numeroChoix = 99;
     tft.fillRect(20, 20, 440, 250, TFT_BLACK);
     drawBmp("/b_valide.bmp", 383, 281);

     stream.stopSong();
Serial.println(pointeur);
Serial.println(stationListe[pointeur]); Serial.println("--------------------------------");

      drawBmp("/station.bmp", 20, 30);
      tft.drawString(String(stationListe[pointeur]), 75, 25, 4);
//      drawBmp(streamLogo[pointeur], 390, 25);
      stream.connecttohost(streamStation[pointeur]);    
  
}
