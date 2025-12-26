/****************************************************
 * ESP32 MQTT SUBSCRIBER 1
 * Client ID: ESP32_Sub_1
 ****************************************************/
// Rizwana Bashir 
//23-NTU-CS-FL-1088
#include <WiFi.h>
#include <PubSubClient.h>

// ---------- WiFi ----------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------- MQTT ----------
const char* mqtt_server = "192.168.209.1";
const int mqtt_port = 1883;
const char* TOPIC_TEMP = "home/lab1/temp";

WiFiClient espClient;
PubSubClient mqtt(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  Serial.print("Subscriber-1 Temp: ");
  Serial.println(msg);
}

void connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (mqtt.connect("ESP32_Sub_1")) {
      mqtt.subscribe(TOPIC_TEMP);
    } else delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  mqtt.setServer(mqtt_server, mqtt_port);
  mqtt.setCallback(callback);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();
}
