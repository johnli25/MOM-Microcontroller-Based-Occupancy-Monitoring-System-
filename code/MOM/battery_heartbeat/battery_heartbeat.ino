#include "secrets.h"
#include "WiFi.h"

#include <ArduinoJson.h>
#include <MQTTClient.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
#include <WiFiClientSecure.h>

#define AWS_IOT_PUBLISH_TOPIC       "esp32/pub"
#define LED_GPIO_PIN                13

uint64_t last_transmission_to_aws, sequence, blink_timer;
SFE_MAX1704X lipo;
WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

bool connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  printf("Connecting to Wi-Fi.");
  uint64_t connect_time_start = esp_timer_get_time() / 1000000; // Seconds since boot
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    printf(".");
    // Enforce 5-second timeout
    if (esp_timer_get_time() / 1000000 - connect_time_start > 5) {
      printf("Timed out while connecting to %s!\n", WIFI_SSID);
      WiFi.disconnect();
      return false;
    }
  }
  printf(" Connected!\n");
  return true;
}

bool connectAWS() {
  // Set creds to connect to AWS IoT
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  printf("Connecting to AWS IoT.");

  while (!client.connect(THINGNAME)) {
    printf(".");
    delay(10);
  }

  if (!client.connected()) {
    printf("\nTimed out while connecting to AWS IoT Core!");
    return false;
  }

  printf(" Connected!\n");
  return true;
}

void publishMessage() {
  if (connectAWS()) {
    StaticJsonDocument<200> doc;
    doc["sequence"] = sequence++;
    doc["sender_mac"] = WiFi.macAddress();
    doc["voltage"] = lipo.getVoltage();
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer); // print to client

    client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
    client.disconnect();
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  connectWiFi();
  pinMode(LED_GPIO_PIN, OUTPUT);
  Wire.begin(3, 4);
  lipo.begin();
  lipo.quickStart();
  sequence = 0;
  publishMessage();
  last_transmission_to_aws = esp_timer_get_time() / 1000;
  blink_timer = last_transmission_to_aws;
}

void loop() {
  if (esp_timer_get_time() / 1000 - blink_timer >= 1000) {
    if (digitalRead(LED_GPIO_PIN) == HIGH) {
      digitalWrite(LED_GPIO_PIN, LOW);
    }
    else {
      digitalWrite(LED_GPIO_PIN, HIGH);
    }
    blink_timer = esp_timer_get_time() / 1000;
    printf("Battery voltage: %f\n", lipo.getVoltage());
  }
  // if (esp_timer_get_time() / 1000 - last_transmission_to_aws >= 60000) {
  //   publishMessage();
  //   last_transmission_to_aws = esp_timer_get_time() / 1000;
  // }
}
