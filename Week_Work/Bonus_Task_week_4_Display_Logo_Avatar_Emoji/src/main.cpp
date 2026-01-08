#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Function Prototypes ---
void drawSmiley(int x, int y, int r);
void drawAvatar(int x, int y);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // --- Step 1: Display Google Logo ---
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(20, 20);
  display.print("Google");
  display.display();
  delay(2000);

  // --- Step 2: Display Enhanced Smiley Emoji ---
  display.clearDisplay();
  drawSmiley(64, 32, 20);
  display.display();
  delay(2000);

  // --- Step 3: Display Avatar ---
  display.clearDisplay();
  drawAvatar(64, 32);
  display.display();
  delay(2000);
}

// --- Function to draw Smiley Face ---
void drawSmiley(int x, int y, int r) {
  display.drawCircle(x, y, r, SSD1306_WHITE);
  display.drawCircle(x, y, r - 1, SSD1306_WHITE);
  display.fillCircle(x - 7, y - 5, 2, SSD1306_WHITE);
  display.fillCircle(x + 7, y - 5, 2, SSD1306_WHITE);
  for (int i = -8; i <= 8; i++) {
    int smileY = y + 7 + (i * i) / 16;
    display.drawPixel(x + i, smileY, SSD1306_WHITE);
  }
}

// --- Function to draw Avatar ---
void drawAvatar(int x, int y) {
  // Head
  display.drawCircle(x, y - 10, 8, SSD1306_WHITE);
  display.fillCircle(x, y - 10, 7, SSD1306_WHITE);

  // Body
  display.drawRoundRect(x - 15, y, 30, 20, 8, SSD1306_WHITE);
  display.fillRect(x - 10, y + 5, 20, 10, SSD1306_WHITE);
}
