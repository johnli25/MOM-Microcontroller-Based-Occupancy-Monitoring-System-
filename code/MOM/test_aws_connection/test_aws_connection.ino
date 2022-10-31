#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "ESP32Ping.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);
hw_timer_t * ping_timer = NULL;
uint64_t connect_time;

void pingTest() {
  bool ret = Ping.ping("a3368omdfuonoa-ats.iot.us-east-1.amazonaws.com", 10);
  float avg_time_ms = Ping.averageTime();
  Serial.print("Ping test finished. Average time ");
  Serial.print(avg_time_ms);
  Serial.println(" milliseconds.");
}

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");
  ping_timer = timerBegin(0, 80, true);

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(10);
  }
  connect_time = timerReadMilis(ping_timer);
  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }
  Serial.println("Connected in ");
  Serial.print(connect_time);
  Serial.print(" milliseconds.");

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["time"] = millis();
  doc["sensor_a0"] = analogRead(0);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

//  StaticJsonDocument<200> doc;
//  deserializeJson(doc, payload);
//  const char* message = doc["message"];
}

void setup() {
  Serial.begin(9600);
  //connectAWS();
}

void loop() {
  pingTest();
  //publishMessage();
  client.loop();
  delay(1000);
}