#include "Adafruit_FONA.h"

#define FONA_RX 8
#define FONA_TX 7
#define FONA_RST 10

#define NETWORK_SETTINGS "http.globe.com.ph" //change this if you'll use non-globe simcard

#define SIMDUINO_KEY A5 //comment this line out if you want the GSM module to be turned on manually

#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST); 

void setupFona() {
  #ifdef SIMDUINO_KEY
    pinMode(SIMDUINO_KEY, INPUT);
    delay(1000);
    pinMode(SIMDUINO_KEY, OUTPUT);
    digitalWrite(SIMDUINO_KEY, LOW);
    delay(3500);
    pinMode(SIMDUINO_KEY, INPUT);
  #endif
  
  fonaSerial->begin(4800);
  while(!fona.begin(*fonaSerial));
  
  while(!fona.enableGPS(true));
  Serial.println("GPS on");

  fona.setGPRSNetworkSettings(F(NETWORK_SETTINGS));
  fona.enableGPRS(true);

  deleteMessages();

  Serial.println("Setup Fona done");
}

boolean sendSMS(String number, String message) {
  return fona.sendSMS(number.c_str(), message.c_str()) ;
}

boolean getGPS(float *latitude, float *longitude, float *speed_kph, float *heading, float *altitude) {
  return fona.getGPS(latitude, longitude, speed_kph, heading, altitude);
}

boolean getGSMLoc(float *latitude, float *longitude) {
  return fona.getGSMLoc(latitude, longitude);
}

void deleteMessages() {
  int slot = 15;
  while(slot > 0) {
    fona.deleteSMS(slot);
    slot--;
  }

  Serial.println(F("Deleting all messages"));
}

String readSMS(String number) {
  uint16_t smslen;
  char replybuffer[255];
  char sender[32];
  bool isAuthorized = true;
  
  if(fona.readSMS(1, replybuffer, 250, &smslen)) {
    Serial.println(F("Read SMS!"));
    
    if(fona.getSMSSender(1, sender, 31)) {
      Serial.println(sender);
      
      if(!number.equals(String(sender))) {
        isAuthorized = false;
      }
    }
    
    fona.deleteSMS(1);

    if(isAuthorized) return String(replybuffer);

    return "unauthorized," + String(sender);
  }

  return "";
}
