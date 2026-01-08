// Rizwana Bashir
// 23-NTU-CS-1088

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin definitions
#define BUTTON_PIN 35     // Push button pin
#define GREEN_LED 19
#define BLUE_LED 18
#define PURPLE_LED 17
#define BUZZER_PIN 5

// Variables for press detection
unsigned long pressStartTime = 0;
bool buttonPressed = false;
bool ledsOn = false;

// Function declaration (important for VS Code)
void showMessage(String msg);

void setup() {
    Serial.begin(115200);

    // Pin modes
    pinMode(BUTTON_PIN, INPUT_PULLUP); // internal pull-up
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(PURPLE_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Initialize LEDs and buzzer off
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(PURPLE_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED init failed!");
        while (true); // stop execution
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println("System Ready...");
    display.display();
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);

    // Button pressed (active LOW)
    if (buttonState == LOW && !buttonPressed) {
        buttonPressed = true;
        pressStartTime = millis();
    }

    // Button released
    if (buttonState == HIGH && buttonPressed) {
        buttonPressed = false;
        unsigned long pressDuration = millis() - pressStartTime;

        if (pressDuration < 1500) {
            // SHORT PRESS → Toggle LEDs
            ledsOn = !ledsOn;
            digitalWrite(GREEN_LED, ledsOn);
            digitalWrite(BLUE_LED, ledsOn);
            digitalWrite(PURPLE_LED, ledsOn);
            showMessage(ledsOn ? "Short Press: LEDs ON" : "Short Press: LEDs OFF");
            Serial.println(ledsOn ? "LEDs turned ON" : "LEDs turned OFF");
        } else {
            // LONG PRESS → Play buzzer tone
            showMessage("Long Press: Buzzer!");
            Serial.println("Buzzer Tone Playing...");
            tone(BUZZER_PIN, 1000); // 1kHz tone
            unsigned long buzzerStart = millis();
            while (millis() - buzzerStart < 800) {
                // (keep tone playing)
            }
            noTone(BUZZER_PIN);
        }
    }
}

void showMessage(String msg) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println(msg);
    display.display();
}
