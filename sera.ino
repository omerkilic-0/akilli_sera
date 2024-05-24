#include <LiquidCrystal.h>
#include <DHT.h>

// LCD pins
const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Soil moisture sensor pins
const int soilMoisturePin1 = A0;
const int soilMoisturePin2 = A1;

// Push button pins
const int greenButtonPin = A3;
const int blueButtonPin = A5;

// Switch button pins
const int switch1Pin = 12;
const int switch2Pin = 11;

// Buzzer pin
const int buzzerPin = 13;

// Motors pin
const int fanPin = 2;
const int suPin = 9;

// Light Pin
const int ledPin = 10;

// DHT11 sensor pin
const int dht11Pin = A4;
DHT dht11(dht11Pin, DHT11);

// LDR pin
const int ldrPin = A2;

// Threshold Values for Plant Mode
int soilMoistureThreshold1 = 35;
int soilMoistureThreshold2 = 45;
int temperatureThreshold = 26;
int humidityThreshold = 60;

// Night Irrigation
int nightIrrigation = 1;

unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(greenButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(fanPin, OUTPUT);
  pinMode(suPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  dht11.begin();

  digitalWrite(suPin, HIGH);
  digitalWrite(ledPin, HIGH);
  digitalWrite(fanPin, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  int waterTankLevel = map(analogRead(soilMoisturePin1), 990, 505, 0, 99);
  int soilMoisture = map(analogRead(soilMoisturePin2), 990, 505, 0, 99);
  float temperature = dht11.readTemperature();
  float humidity = dht11.readHumidity();
  int sunlight = map(analogRead(ldrPin), 0, 1000, 0, 99);

  // Her 5 saniyede bir serial monitore yaz
  if (currentMillis - sendDataPrevMillis >= 3000) {
    sendDataPrevMillis = currentMillis;

    if (digitalRead(greenButtonPin) == HIGH) {
      Serial.print("A0");
      Serial.print("0");

      if (digitalRead(switch1Pin) == HIGH) {
        Serial.print("A1");
        Serial.print("0");
      } else {
        Serial.print("A1");
        Serial.print("1");
      }

      if (digitalRead(switch2Pin) == HIGH) {
        Serial.print("A2");
        Serial.print("0");
      } else {
        Serial.print("A2");
        Serial.print("1");
      }
    } else {
      Serial.print("A0");
      Serial.print("1");

      if (digitalRead(switch1Pin) == HIGH) {
        Serial.print("A1");
        Serial.print("0");
      } else {
        Serial.print("A1");
        Serial.print("1");
      }

      if (digitalRead(switch2Pin) == HIGH) {
        Serial.print("A2");
        Serial.print("0");
      } else {
        Serial.print("A2");
        Serial.print("1");
      }
    }

    Serial.print("A3");
    if (waterTankLevel < 10) {
      Serial.print("0");
    }
    Serial.print(waterTankLevel);
    Serial.print("A4");
    if (soilMoisture < 10) {
      Serial.print("0");
    }
    Serial.print(soilMoisture);
    Serial.print("A5");
    Serial.print(temperature);
    Serial.print("A6");
    Serial.print(humidity);
    Serial.print("A7");
    Serial.print(sunlight);
    Serial.println("A8");
  }

  if (digitalRead(greenButtonPin) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kontrol Serada");
    delay(1000);

    if (digitalRead(switch1Pin) == HIGH) {
      soilMoistureThreshold1 = 35;
      soilMoistureThreshold2 = 45;
      temperatureThreshold = 26;
      humidityThreshold = 60;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kuru bitki Modu");
    } else {
      soilMoistureThreshold1 = 55;
      soilMoistureThreshold2 = 65;
      temperatureThreshold = 46;
      humidityThreshold = 80;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sulak Bitki Modu");
    }

    if (digitalRead(switch2Pin) == HIGH) {
      nightIrrigation = 1;

      lcd.setCursor(0, 1);
      lcd.print("Gunduz Sulamasi");
      delay(1000);
    } else {
      nightIrrigation = 2;

      lcd.setCursor(0, 1);
      lcd.print("Gece Sulamasi");
      delay(1000);
    }

    if (digitalRead(blueButtonPin) == HIGH) {
      digitalWrite(ledPin, LOW);
      delay(1500);
      digitalWrite(ledPin, HIGH);
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kontrol");

    lcd.setCursor(0, 1);
    lcd.print("       Telefonda");
    delay(1000);
  }

  if (waterTankLevel != 0 && soilMoisture != 0 && temperature > 0 && humidity > 0 && sunlight != 0) {
    if (waterTankLevel <= 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Uyari");

      lcd.setCursor(0, 1);
      lcd.print("Depo Bosaldi");
      delay(1000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Doluluk Orani:");

      lcd.setCursor(0, 1);
      lcd.print("%");
      lcd.print(waterTankLevel);
      delay(1000);

      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
    } else if (waterTankLevel <= 15) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Uyari");

      lcd.setCursor(0, 1);
      lcd.print("Depo Azaldi");
      delay(1000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Doluluk Orani:");

      lcd.setCursor(0, 1);
      lcd.print("%");
      lcd.print(waterTankLevel);
      delay(1000);
    } else {
      if (soilMoisture < soilMoistureThreshold1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Uyari");

        lcd.setCursor(0, 1);
        lcd.print("Toprak Nemi Dusuk");
        for (int i = 0; i < 17; i++) {
          lcd.scrollDisplayLeft();
          delay(500);
        }

        if (nightIrrigation == 2) {
          if (sunlight <= 13) {
            digitalWrite(suPin, LOW);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Sulama Basladi");

            lcd.setCursor(0, 1);
            lcd.print("Toprak Nemi: %");
            lcd.print(soilMoisture);
            delay(1000);

            while (soilMoisture < soilMoistureThreshold1) {
              int soilMoisture = map(analogRead(soilMoisturePin2), 990, 505, 0, 99);

              if (soilMoisture > soilMoistureThreshold1) {
                digitalWrite(suPin, HIGH);

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Sulama Tamamlandi");

                lcd.setCursor(0, 1);
                lcd.print("Toprak Nemi: %");
                lcd.print(soilMoisture);
                delay(1000);
                break;
              }
            }
          } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Uyari");

            lcd.setCursor(0, 1);
            lcd.print("Gece olmasi bekleniyor");
            for (int i = 0; i < 22; i++) {
              lcd.scrollDisplayLeft();
              delay(500);
            }
          }
        } else if (nightIrrigation == 1) {
          digitalWrite(suPin, LOW);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Sulama Basladi");

          lcd.setCursor(0, 1);
          lcd.print("Toprak Nemi: %");
          lcd.print(soilMoisture);

          while (soilMoisture < soilMoistureThreshold1) {
            int soilMoisture = map(analogRead(soilMoisturePin2), 990, 505, 0, 99);

            if (soilMoisture > soilMoistureThreshold1) {
              digitalWrite(suPin, HIGH);

              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Sulama Tamamlandı");

              lcd.setCursor(0, 1);
              lcd.print("Toprak Nemi: %");
              lcd.print(soilMoisture);
              break;
              delay(1000);
            }
          }
        }
      } else if (soilMoisture > soilMoistureThreshold2) {
        digitalWrite(fanPin, LOW);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   Uyari");

        lcd.setCursor(0, 1);
        lcd.print("Toprak Nemi Yuksek");
        for (int i = 0; i < 18; i++) {
          lcd.scrollDisplayLeft();
          delay(500);
        }

        while (soilMoisture > soilMoistureThreshold2) {
          int soilMoisture = map(analogRead(soilMoisturePin2), 990, 505, 0, 99);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Havalandiriliyor!");

          lcd.setCursor(0, 1);
          lcd.print("Nem: %");
          lcd.print(soilMoisture);
          delay(1000);

          if (soilMoisture < soilMoistureThreshold2) {
            digitalWrite(fanPin, HIGH);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   Uyari");

            lcd.setCursor(0, 1);
            lcd.print("Toprak Ideal Seviyede");
            for (int i = 0; i < 21; i++) {
              lcd.scrollDisplayLeft();
              delay(500);
            }

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Nem: %");
            lcd.print(humidity);
            delay(1000);

            break;
          }
        }
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Su Deposu: %");
        lcd.print(waterTankLevel);

        lcd.setCursor(0, 1);
        lcd.print("Toprak Nemi: %");
        lcd.print(soilMoisture);
        delay(1000);

        if (temperature > temperatureThreshold) {
          digitalWrite(fanPin, LOW);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("   Uyari");

          lcd.setCursor(0, 1);
          lcd.print("Sicaklik Yuksek");
          delay(1000);

          while (temperature > temperatureThreshold) {
            float temperature = dht11.readTemperature();

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Havalandiriliyor");

            lcd.setCursor(0, 1);
            lcd.print("Sicaklik: ");
            lcd.print(temperature);
            delay(200);

            if (temperature < temperatureThreshold) {
              digitalWrite(fanPin, HIGH);

              break;

              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Hava Isisi Ideal Seviyede");
              for (int i = 0; i < 25; i++) {
                lcd.scrollDisplayLeft();
                delay(500);
              }
            }
          }
        } else {
          if (humidity > humidityThreshold) {
            digitalWrite(fanPin, LOW);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Hava Nemi Yuksek");
            for (int i = 0; i < 16; i++) {
              lcd.scrollDisplayLeft();
              delay(500);
            }

            while (humidity > humidityThreshold) {
              float humidity = dht11.readHumidity();

              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Hava Nemi: %");
              lcd.print(humidity);
              delay(500);

              if (humidity < humidityThreshold) {
                digitalWrite(fanPin, HIGH);

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Hava Nemi Ideal Seviyede");
                for (int i = 0; i < 24; i++) {
                  lcd.scrollDisplayLeft();
                  delay(500);
                }

                lcd.setCursor(0, 1);
                lcd.print("Hava Nemi: %");
                lcd.print(humidity);

                break;
                delay(1000);
              }
            }
          } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Sicaklik: ");
            lcd.print(temperature);

            lcd.setCursor(0, 1);
            lcd.print("Hava Nemi: %");
            lcd.print(humidity);
            delay(1000);
          }
        }
      }
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Uyari:");

    lcd.setCursor(0, 1);
    lcd.print("Sensorlere Erisilemiyor!!!");
    for (int i = 0; i < 26; i++) {
      lcd.scrollDisplayLeft();
      delay(500);
    }

    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }
}
