char phoneNumber[] = "+639XXXXXXXXX";
float latitude, longitude, speed_kph, heading, altitude;

void setup() {
  Serial.begin(115200);
  setupFona();
}

void loop() {
  String response =  readSMS(phoneNumber);

  if (!response.equals("")) {
    if(response.equals("!@gps")) {
      sendGPS();
    } else if (response.equals("unauthorized")) {
      Serial.println("Unauthorized usage of the system");
      sendSMS(phoneNumber, "You are not authorized to use the system");
    } else {
      Serial.print("Message: "); Serial.println(response);
    }
  }
}

void sendGPS() {
  String message;
  if(getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude)) {
    Serial.println("Got GPS fix");
    message = "Latitude: " + String(latitude, 6) + ", Longitude: " + String(longitude, 6);
    sendSMS(phoneNumber, message.c_str());
  } else {
    Serial.println("Cannot get GPS fix");
    sendSMS(phoneNumber, "Cannot get GPS fix");
  }
}
