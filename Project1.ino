#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define buzzer 26
#define ledMerah 25
#define ledHijau 33
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(buzzer, OUTPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  lcd.clear();

  if (isnan(h) || isnan (t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.setCursor(0, 0);
    lcd.print("Failed");
    return;
  } else {
    Serial.print(h);
    Serial.print(" ");
    Serial.println(t);
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.setCursor(0,1);
    lcd.print("Humi: ");
    lcd.print(h);
  }

  if (t >= 34 ) {
    digitalWrite(ledHijau, 0);
    digitalWrite(ledMerah, 1);
    digitalWrite(buzzer, 1);
    delay(2000);
  } else {
    digitalWrite(ledHijau, 1);
    digitalWrite(buzzer, 0);
    digitalWrite(ledMerah, 0);
  }
}
