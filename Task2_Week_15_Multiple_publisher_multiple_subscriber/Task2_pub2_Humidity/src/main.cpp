/****************************************************
 * ESP32 MQTT PUBLISHER - HUMIDITY
 * Topic: home/lab2/hum
 ****************************************************/
//Rizwana Bashir
//23-NTU-CS-1088
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// WiFi
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// MQTT
const char* mqtt_server = "192.168.209.1";
const int mqtt_port = 1883;
const char* TOPIC_HUM = "home/lab2/hum";

// DHT
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient mqtt(espClient);

void connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (mqtt.connect("PUB_HUM_ESP32")) break;
    delay(2000);
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

  float hum = dht.readHumidity();
  if (isnan(hum)) return;

  char buf[8];
  dtostrf(hum, 4, 2, buf);

  mqtt.publish(TOPIC_HUM, buf);
  Serial.print("Humidity Published: ");
  Serial.println(buf);

  delay(5000);
}
