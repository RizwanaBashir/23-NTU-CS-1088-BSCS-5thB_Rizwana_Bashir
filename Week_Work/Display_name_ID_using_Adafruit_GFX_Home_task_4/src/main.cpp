#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---- OLED setup ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(21, 22); // ESP32 default I2C pins (SDA=21, SCL=22)

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;); // Halt if OLED not found
  }

  display.clearDisplay();

  // ---- Text setup ----
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1); // Keep small so text fits

  // ---- Coordinates for text ----
  int16_t x = 10;   // left margin
  int16_t y = 20;   // top position

  // ---- Print name and ID ----
  display.setCursor(x, y);
  display.println("Name:RizwanaBashir");
  display.setCursor(x, y + 12);  // move down one line
  display.println("ID:23-NTU-CS-1088");

  // ---- Draw a rectangle around both lines ----
  // x, y, width, height
  display.drawRect(2, 10, 124, 35, SSD1306_WHITE);


  display.display();
}

void loop() {
  // Nothing here
}
