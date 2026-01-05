//Rizwana Bashir 
//23-NTU-CS-FL-1088
#define BLYNK_TEMPLATE_ID "TMPL6goxVvccF"
#define BLYNK_TEMPLATE_NAME "Water Quality Monitoring System"
#define BLYNK_AUTH_TOKEN "BFyPRkW9rJvpwED9fN6k4azePBpIjwhi"

#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi credentials
char ssid[] = "NTU WiFi";
char pass[] = "";

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define TDS_PIN 34
#define GREEN_LED 19
#define YELLOW_LED 17
#define RED_LED 18
#define BUZZER 5

// Buzzer PWM settings
#define BUZZER_CHANNEL 0
#define BUZZER_FREQ 2000
#define BUZZER_RESOLUTION 8

BlynkTimer timer;

// Forward declaration
void readAndDisplayAndSend();

// Optional: send periodically to Blynk
void periodicSend() {
  readAndDisplayAndSend();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Water Quality + OLED + Blynk starting...");

  // LEDs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Buzzer
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER, BUZZER_CHANNEL);
  ledcWrite(BUZZER_CHANNEL, 0);

  // OLED
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not detected");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(12, 25);
  display.println("Water Quality");
  display.setCursor(18, 40);
  display.println("Monitoring...");
  display.display();
  delay(2000);

  // Connect to Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Periodic send every 5 seconds
  timer.setInterval(5000L, periodicSend);
}

void readAndDisplayAndSend() {
  int analogValue = analogRead(TDS_PIN);

  // Convert ADC reading to voltage
  float voltage = analogValue * (3.3 / 4095.0);

  // Approximate TDS (ppm)
  float tds = voltage * 1000;

  // Calculate Electrical Conductivity (EC)
  float ec = tds * 2; // µS/cm approximation

  // Turn OFF all outputs first
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  ledcWrite(BUZZER_CHANNEL, 0);

  String status;

  // LED and buzzer logic
  if (tds <= 300) {
    digitalWrite(GREEN_LED, HIGH);
    status = "SAFE";
  }
  else if (tds > 300 && tds <= 500) {
    digitalWrite(YELLOW_LED, HIGH);
    status = "MODERATE";
  }
  else {
    digitalWrite(RED_LED, HIGH);
    ledcWrite(BUZZER_CHANNEL, 128); // buzzer ON
    status = "UNSAFE";
  }

  // OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Water Quality System");
  display.setCursor(0, 18);
  display.print("TDS: "); display.print(tds); display.println(" ppm");
  display.setCursor(0, 32);
  display.print("EC : "); display.print(ec); display.println(" uS/cm");
  display.setCursor(0, 48);
  display.print("Status: "); display.println(status);
  display.display();

  // Serial Monitor
  Serial.print("TDS: "); Serial.print(tds); Serial.print(" ppm, ");
  Serial.print("EC: "); Serial.print(ec); Serial.print(" uS/cm, ");
  Serial.println("Status: " + status);

  // Send to Blynk (Virtual Pins)
  Blynk.virtualWrite(V0, tds);
  Blynk.virtualWrite(V1, ec);
  Blynk.virtualWrite(V2, status);
}

void loop() {
  Blynk.run();
  timer.run();
}
