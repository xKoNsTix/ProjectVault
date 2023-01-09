#include <Adafruit_NeoPixel.h>

#define PIN 6 // LED
#define N_PIXELS 60
#define MOTION_SENSOR_PIN 7
#define SWITCH_PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long last_motion_detected_time = 0;
bool switch_state = LOW;

void setup() {
  strip.begin();
  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  switch_state = digitalRead(SWITCH_PIN);

  if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
    last_motion_detected_time = millis();

    for (int i = 0; i < N_PIXELS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(100);

    // Fade in
    for (int brightness = 255; brightness < 1; brightness++) {
      for (int i = 0; i < N_PIXELS; i++) {
        if (switch_state == HIGH) {
          strip.setPixelColor(i, strip.Color(0, brightness, 0));
        } else {
          strip.setPixelColor(i, strip.Color(brightness, 0, 0));
        }
      }
      strip.show();
      delay(10);
    }

    // Fade out
    for (int brightness =255; brightness >= 0; brightness--) {
      for (int i = 0; i < N_PIXELS; i++) {
        if (switch_state == HIGH) {
          strip.setPixelColor(i, strip.Color(0, brightness, 0));
        } else {
          strip.setPixelColor(i, strip.Color(brightness, 0, 0));
        }
      }
      strip.show();
      delay(10);
    }
  }

  if (millis() - last_motion_detected_time > 5000) {
    for (int i = 0; i < N_PIXELS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
  }
}