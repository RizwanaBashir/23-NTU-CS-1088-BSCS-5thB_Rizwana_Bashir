/****************************************************
 * MQTT SUBSCRIBER 2
 * Receives Temperature + Humidity
 ****************************************************/
//Rizwana Bashir
//23-NTU-CS-1088
#include <WiFi.h>
#include <PubSubClient.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

const char* mqtt_server = "192.168.209.1";
const int mqtt_port = 1883;

const char* TOPIC_TEMP = "home/lab2/temp";
const char* TOPIC_HUM  = "home/lab2/hum";

WiFiClient espClient;
PubSubClient mqtt(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  if (String(topic) == TOPIC_TEMP)
    Serial.println("SUB-2 Temp: " + msg);
  else if (String(topic) == TOPIC_HUM)
    Serial.println("SUB-2 Hum: " + msg);
}

void connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (mqtt.connect("SUB_2")) {
      mqtt.subscribe(TOPIC_TEMP);
      mqtt.subscribe(TOPIC_HUM);
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
