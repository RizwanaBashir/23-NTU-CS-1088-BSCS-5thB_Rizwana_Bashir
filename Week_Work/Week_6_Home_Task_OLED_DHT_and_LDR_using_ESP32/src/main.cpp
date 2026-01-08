#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin Configuration ---
#define DHTPIN 21        // DHT data pin
#define DHTTYPE DHT11    // or DHT22

#define LDR_PIN 34       // Analog pin for LDR
#define SDA_PIN 14       // I2C SDA
#define SCL_PIN 22       // I2C SCL

// --- OLED Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- DHT Sensor Setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- Setup Function ---
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 DHT + LDR + OLED Project Starting...");

  // Initialize I2C for OLED
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // Initialize DHT Sensor
  dht.begin();

  delay(1500);
}

// --- Main Loop ---
void loop() {
  // --- Read DHT Sensor ---
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // --- Read LDR ---
  int adcValue = analogRead(LDR_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;

  // --- Check for DHT Errors ---
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT sensor!");
    return;
  }

  // --- Print Data on Serial Monitor ---
  Serial.println("===========================");
  Serial.printf("Temperature: %.2f °C\n", temperature);
  Serial.printf("Humidity: %.2f %%\n", humidity);
  Serial.printf("LDR ADC: %d | Voltage: %.2f V\n", adcValue, voltage);

  // --- Display on OLED ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hello IoT Project");
  
  display.setCursor(0, 16);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 28);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 40);
  display.print("LDR ADC: ");
  display.println(adcValue);

  display.setCursor(0, 52);
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");

  display.display();

  delay(2000); // Update every 2 seconds
}
