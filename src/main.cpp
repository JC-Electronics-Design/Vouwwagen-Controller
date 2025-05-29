#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     18
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    300

#define BRIGHTNESS  255


CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);

  Serial.println("\n\nStart Vouwwagen Contoller");

  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);

  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

}

void loop() {
  digitalWrite(4, HIGH);
  digitalWrite(13, HIGH);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  delay(1000);
  digitalWrite(4, LOW);
  digitalWrite(13, LOW);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000);
  

}
