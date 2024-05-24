#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "..."
#define WIFI_PASSWORD "..."
#define API_KEY "..."
#define DATABASE_URL "..."

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
unsigned long lastConnectionTime = 0;
const unsigned long connectionInterval = 15000;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) {
    signupOK = true;
  } else {
    Serial.printf("Firebase SignUp Error: %s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastConnectionTime >= connectionInterval) {
    lastConnectionTime = currentMillis;
    if (!Firebase.ready() || !signupOK) {
      Firebase.begin(&config, &auth);
      Firebase.reconnectWiFi(true);
    }
  }

  if (Serial.available()) {
    String message = Serial.readString();
    int startPos = 0;
    int endPos = message.indexOf("A", startPos + 1);

    while (endPos != -1) {
      String subMessage = message.substring(startPos, endPos);
      String key;
      String valueStr;

      if (subMessage.startsWith("A0")) {
        key = "kontrol";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A1")) {
        key = "bMod";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A2")) {
        key = "sDurumu";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A3")) {
        key = "dDOrani";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A4")) {
        key = "tNOrani";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A5")) {
        key = "hIsisi";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A6")) {
        key = "hNem";
        valueStr = subMessage.substring(2);
      } else if (subMessage.startsWith("A7")) {
        key = "gMiktari";
        valueStr = subMessage.substring(2);
      }

      if (key.length() > 0) {
        int valueInt = valueStr.toInt();  // Convert to integer to remove leading zeros
        String path = "/realValue/" + key;
        if (!Firebase.RTDB.setInt(&fbdo, path.c_str(), valueInt)) {
          Serial.printf("Error setting %s: %s\n", key.c_str(), fbdo.errorReason().c_str());
        }
      }
      startPos = endPos;
      endPos = message.indexOf("A", startPos + 1);
    }
  }
}
