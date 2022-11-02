#include "WiFi.h"

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
}

void loop() {
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  Serial.println(WiFi.macAddress());
  delay(1000);
}
