/****************************************************
 * ESP32 + DHT22 + MQTT
 * SINGLE PUBLISHER
 * Topic: home/lab1/temp
 ****************************************************/
// Rizwana Bashir 
//23-NTU-CS-FL-1088
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ---------- WiFi ----------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------- MQTT ----------
const char* mqtt_server = "192.168.209.1";
const int mqtt_port = 1883;
const char* TOPIC_TEMP = "home/lab1/temp";

// ---------- DHT ----------
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------- MQTT Client ----------
WiFiClient espClient;
PubSubClient mqtt(espClient);

// ---------- WiFi ----------
void connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

// ---------- MQTT ----------
void connectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Connecting MQTT...");
    if (mqtt.connect("ESP32_Publisher")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectWiFi();

  mqtt.setServer(mqtt_server, mqtt_port);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  float temp = dht.readTemperature();
  if (isnan(temp)) return;

  char tempBuf[8];
  dtostrf(temp, 4, 2, tempBuf);

  mqtt.publish(TOPIC_TEMP, tempBuf);

  Serial.print("Published Temp: ");
  Serial.println(tempBuf);

  delay(5000);
}
