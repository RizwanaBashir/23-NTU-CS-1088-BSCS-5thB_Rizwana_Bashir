//Rizwana Bashir
//23-NTU-CS-1088
//StaticIP_setup
#include <WiFi.h>
const char* ssid     = "vivoY28";
const char* password = "nimra10810004";

// Static IP configuration
IPAddress local_IP(192,168,204,5);  // ESP32 IP
IPAddress gateway(192,168,204,1);     // Router IP
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);      // Optional
IPAddress secondaryDNS(8, 8, 4, 4);    // Optional

void setup() {
    Serial.begin(115200);

    // Set Static IP
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("Static IP Failed!");
    }

    WiFi.begin(ssid, password);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
}