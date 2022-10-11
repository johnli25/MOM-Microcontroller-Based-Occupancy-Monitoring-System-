#include "WiFi.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("Setup done.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Scan start");
  int n = WiFi.scanNetworks();
  Serial.print("Scan done. Found ");
  Serial.print(n);
  Serial.println(" networks.");
  delay(1000);
}
