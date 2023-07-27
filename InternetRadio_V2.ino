

#include "FS.h"
#include "SPIFFS.h"  // For ESP32 only
#define   FS_NO_GLOBALS

//____________________________________________________________________________ 
#include <SPI.h>
#include <TFT_eSPI.h>
          TFT_eSPI tft = TFT_eSPI();

//____________________________________________________________________________ 
#define   nbrBoutons 4
          TFT_eSPI_Button bouton[nbrBoutons];
          uint16_t calData[5] = { 351, 3476, 310, 3384, 7 };
          uint8_t calDataOK = 0;
          int numero, numeroChoix = 99;
          int listeLigne, listePointeur;
          int choixLigne, pointeur;
          bool initialListe = true;
          String stationListe[12] = { "Vinilo The 80", "Unsung 80's Radio", "113fm Awesome 80's", "Radio Porcuna 80",
                                      "Love 80's Manchester", "0nlineradio CINEMA HITS", "Epic Tones", "Auckland 80's", 
                                      "100/100 Hits 90's", "Cleansing 90's", "La Rocka 90's", "70 Mix Radio" };  
          const char* streamStation[12] = { "http://vip2.fastcast4u.com/proxy/easyhitsmiamisfl?mp=/1",
                                            "http://unsung80s.out.airtime.pro:8000/unsung80s_a?_ga=2.268344966.909605021.1515170054-2043058025.1514757130&amp;_gac=1.95458670.1514757130.Cj0KCQiAsqLSBRCmARIsAL4Pa9QSUMCRf22lsRWwo9Nlu2k1GOYhnSTMrVbrFnSrXGqtUpFoto3jgoMaAshuEALw_wcB",
                                            "http://113fm.cdnstream1.com/1719_128",
                                            "http://stream-149.zeno.fm/33nh3knb1eruv?zs=QNp_zOicS1quqPxAJe3N-A",
                                            "https://stream1.themediasite.co.uk:7018/;",
                                            "https://stream.0nlineradio.com/cinema-hits?ref",
                                            "https://s4.radio.co/s35c414576/listen",
                                            "http://192.111.140.11:8524/stream",
                                            "https://streamer.radio.co/s81fc850fd/listen",
                                            "http://pureplay.cdnstream1.com/6056_128.mp3",
                                            "http://hemnos.cdnstream.com/1468_128",
                                            "http://pureplay.cdnstream1.com/6052_128.mp3" };
          const char* streamLogo[12] = { "/vinilo80.bmp", "/unsung80.bmp", "/avesome80.bmp", "/.bmp", "/love80.bmp", "/cinemahits.bmp", "/epictones.bmp"

};
   
   String stationOrg, station, morceau, interpreteOrg, interprete, titreOrg, titre, streamFormat;
      int longStation, pixStation, posStation, longMorceau, tiret, cesure;
      int longInterprete, pixInterprete, posInterprete;
      int longTitre, pixTitre, posTitre;
                                      
//____________________________________________________________________________
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
    const char *ssid     = "@@@@@@@@@@";
    const char *password = "@@@@@@@@@@";
          WiFiMulti WiFiMulti; 
      int TryNum = 0;

//____________________________________________________________________________      
#include <ESP32_VS1053_Stream.h>
          ESP32_VS1053_Stream stream;

#include <VS1053.h>           
#define   VS1053_CS     5
#define   VS1053_DCS    16
#define   VS1053_DREQ   4

#define BUFFSIZE 128  //32, 64 ou 128
uint8_t mp3buff[BUFFSIZE];
 
//____________________________________________________________________________      


void connectWifi() {
  
     Serial.print("Connection ...");
     tft.drawRightString("Connection WiFi", 460, 200, 4); 
     WiFiMulti.addAP(ssid, password);
     while (WiFiMulti.run() != WL_CONNECTED) {
            Serial.print ( "." );
            delay ( 50 );
            TryNum++;
            if (TryNum > 20) {
                Serial.print("\nConnection impossible !\n");
                tft.drawRightString("Erreur connection !", 460, 230, 4);
                delay(5000); 
                if (WiFi.status() != WL_CONNECTED) {
                    ESP.restart();
                   }
                delay(50);
                for (;;);
               }
           }
     Serial.print("\nconnecte a "); Serial.println(ssid);
     tft.drawRightString("WiFi connecte ", 460, 230, 4); 
     
} 


//____________________________________________________________________________ 


void setup() {

     Serial.begin(115200); Serial.println(); Serial.println();

     tft.init();
     tft.setRotation(3);
     tft.fillScreen(TFT_BLACK);
     tft.setTextColor(TFT_WHITE); 
     tft.drawRightString("Internet Radio Stream", 450, 35, 4);
     tft.drawRightString("Esp 32  &  VS1053", 450, 65, 4);  

     if (!SPIFFS.begin()) {
         Serial.println("SPIFFS initialisation failed!");
         tft.drawRightString("Erreur SPIFFS !", 450, 110, 4);
         while (1) yield();
        }
     Serial.println("\r\nSPIFFS Ok");
     drawBmp("/initialisation.bmp", 0, 0);

     tft.drawRightString("Internet Radio Stream", 450, 35, 4);
     tft.drawRightString("Esp 32  &  VS1053", 450, 65, 4);  
     tft.drawRightString("SPIFFS OK", 450, 110, 4);      
     tft.drawRightString("Initialisation", 450, 140, 4);   

     while (WiFi.status() != WL_CONNECTED) {
            connectWifi();
           }   

     bouton[0].initButton(&tft, 400, 297, 40, 40, TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT, "", 2);
     drawBmp("/b_down.bmp", 53, 281);
     bouton[1].initButton(&tft, 315, 297, 40, 40, TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT, "", 2);
     drawBmp("/b_up.bmp", 144, 281); 
     bouton[2].initButton(&tft, 162, 297, 40, 40, TFT_TRANSPARENT, TFT_TRANSPARENT, TFT_TRANSPARENT, "", 2);
     drawBmp("/b_list.bmp", 292, 281);
     bouton[3].initButton(&tft, 75, 297, 40, 40, TFT_TRANSPARENT, TFT_BLACK, TFT_TRANSPARENT, "", 2);
     drawBmp("/b_valide.bmp", 383, 281);

     SPI.begin();  /* start SPI before starting decoder */    
     stream.startDecoder(VS1053_CS, VS1053_DCS, VS1053_DREQ);
     
}


void loop() {

     if (WiFi.status() != WL_CONNECTED) {
         ESP.restart();
        }
     delay(50);

     stream.loop();

//   On vérifie si la position du contact correspond à celle d'un bouton

     uint16_t t_x = 0, t_y = 0;                  // coordonnées touchées par l'utilisateur
     boolean pressed = tft.getTouch(&t_y, &t_x); // vrai si contact avec l'écran !!! INVERSE !!!
     
     for (numero = 0; numero < nbrBoutons; numero++) {
          if (pressed && bouton[numero].contains(t_y, t_x)) {
              bouton[numero].press(true);
              Serial.print("Bouton nr: "); Serial.println(numero);
              numeroChoix = numero;

             } else {
              bouton[numero].press(false);
             }
         }
//     delay(100); // anti-rebond       

     if (numeroChoix == 2) {
         drawBmp("/b_press.bmp", 292, 281);
         Affiche_Liste();      
        }

     if (numeroChoix == 0) {
         drawBmp("/b_press.bmp", 53, 281);
         Choix_Down_Liste();      
        }

     if (numeroChoix == 1) {
         drawBmp("/b_press.bmp", 144, 281);
         Choix_Up_Liste();      
        }

     if (numeroChoix == 3) {
         drawBmp("/b_press.bmp", 383, 281);
         Choix_Valide_Stream();      
        }
              
}


//   STREAM DATAS INFOS
//   ------------------


void audio_showstation(const char* info) { 
 
     tft.fillRect(30, 25, 420, 245, TFT_BLACK);
     tft.drawString(String(stationListe[pointeur]), 75, 25, 4);
Serial.printf("showstation: %s\n", info);
     stationOrg = ("showstation: %s\n", info);
Serial.println("-------------------------------------- Station " + String(stationOrg)); 
     drawBmp("/station.bmp", 20, 30);
     tft.drawString(String(stationOrg), 75, 70, 2);         
     station = stationOrg.substring(0, 15);   
     drawBmp(streamLogo[pointeur], 370, 25);
                            
}


void audio_showstreamtitle(const char* info) { 

     tft.fillRect(30, 100, 420, 170, TFT_BLACK);

Serial.printf("streamtitle: %s\n", info);
     morceau = ("streamtitle: %s\n", info);
Serial.println("-------------------------------------- Data " + String(morceau));
     longMorceau = morceau.length();
     for (tiret = 0; tiret <= longMorceau; tiret ++) {
          String lettre = String (morceau.charAt(tiret));
          if (lettre == "-") {
              cesure = tiret;
              tiret = longMorceau;      
             } 
         }

     interpreteOrg = String (morceau.substring(0, cesure));
Serial.println("-------------------------------------- Interprete " + String(interpreteOrg));
     drawBmp("/artiste.bmp", 20, 135);
     tft.drawString(String(interpreteOrg), 75, 150, 4);
     interprete = interpreteOrg.substring(0, 20);
     
     titreOrg = String (morceau.substring(cesure + 2, longMorceau)); 
Serial.println("-------------------------------------- Titre " + String(titreOrg));
     drawBmp("/titre.bmp", 20, 200);
     tft.drawString(String(titreOrg), 75, 215, 4);
     titre = titreOrg.substring(0, 26);
     
     String txtCodec = stream.currentCodec();
     int txtBitrate = stream.bitrate();
Serial.println("-------------------------------------- Stream " +  ((String (txtCodec)) + "/" 
               + (String (txtBitrate)) + "kbps"));
     tft.drawString(String (txtCodec) + "/" 
               + String (txtBitrate) + "kbps", 75, 50, 4);
Serial.println();
     drawBmp("/overlay.bmp", 450, 0);
     
}


void audio_eof_stream(const char* info) { 

//Serial.printf("eof_stream: %s\n", info);
   
}
