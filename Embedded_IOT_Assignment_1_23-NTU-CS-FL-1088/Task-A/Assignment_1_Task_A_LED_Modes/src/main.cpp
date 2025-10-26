//Rizwana Bashir
//23-NTU-CS-1088
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED Configuration ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Pin Definitions ---
#define BUTTON1 34
#define BUTTON2 35
#define RED_LED 19
#define BLUE_LED 18
#define PURPLE_LED 17

// --- Global Variables ---
int mode = 1;
bool lastButton1 = HIGH;
bool lastButton2 = HIGH;
unsigned long lastButtonTime = 0;

// Variables for blinking/fading
unsigned long lastBlinkTime = 0;
int blinkState = 0;
int fadeValue = 0;
int fadeDirection = 1;

// --- Function Prototype (required for PlatformIO) ---
void showMode();

void setup() {
  Serial.begin(115200);
  Wire.begin();  // I2C start for OLED

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED initialization failed!"));
    while (true); // Stop if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Set pin modes
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(PURPLE_LED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  // Show initial mode
  showMode();
}

void loop() {
  bool button1State = digitalRead(BUTTON1);
  bool button2State = digitalRead(BUTTON2);

  // --- Mode Button ---
  if (button1State == LOW && lastButton1 == HIGH && millis() - lastButtonTime > 300) {
    mode++;
    if (mode > 4) mode = 1;
    showMode();
    lastButtonTime = millis();
  }

  // --- Reset Button ---
  if (button2State == LOW && lastButton2 == HIGH && millis() - lastButtonTime > 300) {
    mode = 1;
    showMode();
    lastButtonTime = millis();
  }

  lastButton1 = button1State;
  lastButton2 = button2State;

  // --- Mode Functions ---
  switch (mode) {
    case 1: // All OFF
      analogWrite(RED_LED, 0);
      analogWrite(BLUE_LED, 0);
      analogWrite(PURPLE_LED, 0);
      break;

    case 2: // All LEDs alternate blink together
      if (millis() - lastBlinkTime >= 500) {
        blinkState = !blinkState;
        analogWrite(RED_LED, blinkState ? 255 : 0);
        analogWrite(BLUE_LED, blinkState ? 255 : 0);
        analogWrite(PURPLE_LED, blinkState ? 255 : 0);
        lastBlinkTime = millis();
      }
      break;

    case 3: // All ON
      analogWrite(RED_LED, 255);
      analogWrite(BLUE_LED, 255);
      analogWrite(PURPLE_LED, 255);
      break;

    case 4: // PWM fade (non-blocking)
      if (millis() - lastBlinkTime >= 10) {
        fadeValue += fadeDirection * 5;
        if (fadeValue >= 255 || fadeValue <= 0) fadeDirection *= -1;

        analogWrite(RED_LED, fadeValue);
        analogWrite(BLUE_LED, 255 - fadeValue);
        analogWrite(PURPLE_LED, (fadeValue / 2) + 50);

        lastBlinkTime = millis();
      }
      break;
  }
}

// --- OLED Display Function ---
void showMode() {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.print("Mode ");
  display.print(mode);
  display.setTextSize(1);
  display.setCursor(0, 40);

  switch (mode) {
    case 1: display.print("All LEDs OFF"); break;
    case 2: display.print("All Blink Alt"); break;
    case 3: display.print("All LEDs ON"); break;
    case 4: display.print("PWM Fade All"); break;
  }

  display.display();
}
