#include <Arduino.h>

// --- LED setup ---
#define LED1_PIN 18
#define LED2_PIN 19
#define PWM_LED1 0
#define PWM_LED2 1
#define LED_FREQ 5000
#define LED_RES 8

// --- Buzzer setup ---
#define BUZZER_PIN 27
#define PWM_BUZZ 2          // Use a separate channel
#define BUZZ_FREQ 2000
#define BUZZ_RES 10

void setup() {
  // --- Setup LEDs ---
  ledcSetup(PWM_LED1, LED_FREQ, LED_RES);
  ledcSetup(PWM_LED2, LED_FREQ, LED_RES);
  ledcAttachPin(LED1_PIN, PWM_LED1);
  ledcAttachPin(LED2_PIN, PWM_LED2);

  // --- Setup Buzzer ---
  ledcSetup(PWM_BUZZ, BUZZ_FREQ, BUZZ_RES);
  ledcAttachPin(BUZZER_PIN, PWM_BUZZ);
}

void loop() {
  // --- 1. Fade LEDs IN + Buzzer sweep ---
  for (int d = 0; d <= 255; d++) {
    ledcWrite(PWM_LED1, d);
    ledcWrite(PWM_LED2, d);
    int freq = map(d, 0, 255, 400, 2000);   // map brightness to frequency
    ledcWriteTone(PWM_BUZZ, freq);
    delay(8);
  }

  // Pause tone
  ledcWrite(PWM_BUZZ, 0);
  delay(200);

  // --- 2. Fade LEDs OUT + Buzzer melody ---
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int d = 255; d >= 0; d--) {
    ledcWrite(PWM_LED1, d);
    ledcWrite(PWM_LED2, d);
    int index = map(d, 255, 0, 0, 7);
    ledcWriteTone(PWM_BUZZ, melody[index]);
    delay(8);
  }

  // Stop buzzer
  ledcWrite(PWM_BUZZ, 0);
  delay(500);
}
