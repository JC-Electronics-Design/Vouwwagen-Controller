/**
 * @file main.cpp
 * @author Jonathan Caes
 * @brief This piece of code is used to control the light of my vouwwagen
 * @version 1.0
 * @date 2025-05-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <Arduino.h>
#include <OneButton.h>
#include <FastLED.h>
#include "config.h"

// Notes: LED output 2 is currently not supported for control!

/* Current button control configuration:
 * Relay 1-4 on/off             -> Short press button 1-4
 * LED output 1 on/off          -> Long press button 1
 * LED change color in steps    -> Long press button 2
 * LED brightness decrement     -> Long press button 3
 * LED brightness increment     -> Long press button 4
 * LED back to white            -> Double press button 2
 * All lights off               -> Double press button 4
 * */

// Variable declaration
// Relay output status
bool relay1_status = false;
bool relay2_status = false;
bool relay3_status = false;
bool relay4_status = false;

// LED color and brightness values
uint8_t led_out_1_hue = 0;
uint8_t led_out_1_sat = 0;
uint8_t led_out_1_val = 0; // value aka brightness
uint8_t last_led_out_1_val = LED_MAX_BRIGHTNESS;

//LED color changing parameters
uint32_t last_color_change_time = 0;
uint32_t last_brightness_change_time = 0;

// Setup OneButton instances
OneButton button1(BUTTON_1, ACTIVE_LOW);
OneButton button2(BUTTON_2, ACTIVE_LOW);
OneButton button3(BUTTON_3, ACTIVE_LOW);
OneButton button4(BUTTON_4, ACTIVE_LOW);

// Setup FastLED instances
CRGB led_out_1[LED_OUT_1_NUM_LEDS];
CRGB led_out_2[LED_OUT_2_NUM_LEDS];


void setLEDvalueOut1(uint16_t hue, uint8_t sat, uint8_t val) {
  for(int i = 0; i < LED_OUT_1_NUM_LEDS; i++) {
    led_out_1[i] = CHSV(led_out_1_hue, led_out_1_sat, led_out_1_val);
  }
  FastLED.show();
}

void button1_click() {
  if(relay1_status) {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 1 Off");
    #endif
    digitalWrite(RELAY_1, HIGH);
    relay1_status = false;
  }
  else {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 1 On");
    #endif
    digitalWrite(RELAY_1, LOW);
    relay1_status = true;
  }
}
void button1_doubleClick() {
  // TBD
}
void button1_longPressStart() {
  if(led_out_1_val) {
    #ifdef DEBUG_EN
      Serial.println("Turn LED output 1 Off");
    #endif
    last_led_out_1_val = led_out_1_val;
    led_out_1_val = 0;
    setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
  }
  else {
    #ifdef DEBUG_EN
      Serial.println("Turn LED output 1 On");
    #endif
    led_out_1_val = last_led_out_1_val;
    setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
  }  
}
void button1_duringLongPress() {
  // TBD
}
void button2_click() {
  if(relay2_status) {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 2 Off");
    #endif
    digitalWrite(RELAY_2, HIGH);
    relay2_status = false;
  }
  else {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 2 On");
    #endif
    digitalWrite(RELAY_2, LOW);
    relay2_status = true;
  }
}
void button2_doubleClick() {
  if(led_out_1_val) {
    #ifdef DEBUG_EN
      Serial.println("Change LED output 1 Color to White and show");
    #endif
    led_out_1_sat = WHITE_SAT;
    setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
  }
  else {
    #ifdef DEBUG_EN
      Serial.println("Change LED output 1 Color to White");
    #endif
    led_out_1_sat = WHITE_SAT;
  } 
}
void button2_longPressStart() {
  // TBD
}
void button2_duringLongPress() {
  // Only change color when LEDs are on
  if(led_out_1_val) {
    if((millis() - last_color_change_time) > COLOR_CHANGE_DELAY) {
      led_out_1_hue += COLOR_CHANGE_HUE_STEPS;
      if(led_out_1_hue >= 255) {
        led_out_1_hue = 0;
      }
      led_out_1_sat = LED_MAX_SATURATION;
      #ifdef DEBUG_EN
        Serial.print("Current hue value = "); Serial.println(led_out_1_hue);
      #endif
      setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
      last_color_change_time = millis();
    }
  }
}
void button3_click() {
  if(relay3_status) {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 3 Off");
    #endif
    digitalWrite(RELAY_3, HIGH);
    relay3_status = false;
  }
  else {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 3 On");
    #endif
    digitalWrite(RELAY_3, LOW);
    relay3_status = true;
  }
}
void button3_doubleClick() {
  // TBD
}
void button3_longPressStart() {
  // TBD
}
void button3_duringLongPress() {
  // Only change brightness when LEDs are on
  if(led_out_1_val > LED_MIN_BRIGHTNESS) {
    if((millis() - last_brightness_change_time) > BRIGHTNESS_CHANGE_DELAY) {   
      if(led_out_1_val > (LED_MIN_BRIGHTNESS+BRIGHTNESS_CHANGE_STEPS-1)) {
        led_out_1_val -= BRIGHTNESS_CHANGE_STEPS; 
      }
      else {
        led_out_1_val = LED_MIN_BRIGHTNESS;
      }
      #ifdef DEBUG_EN
        Serial.print("Current brightness value = "); Serial.println(led_out_1_val);
      #endif
      setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
      last_brightness_change_time = millis();
    }
  }
}
void button4_click() {
  if(relay4_status) {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 4 Off");
    #endif
    digitalWrite(RELAY_4, HIGH);
    relay4_status = false;
  }
  else {
    #ifdef DEBUG_EN
      Serial.println("Turn Relay 4 On");
    #endif
    digitalWrite(RELAY_4, LOW);
    relay4_status = true;
  }
}
void button4_doubleClick() {
  #ifdef DEBUG_EN
    Serial.println("Turn all lights Off");
  #endif
  digitalWrite(RELAY_1, HIGH);
  relay1_status = false;
  digitalWrite(RELAY_2, HIGH);
  relay2_status = false;
  digitalWrite(RELAY_3, HIGH);
  relay3_status = false;
  digitalWrite(RELAY_4, HIGH);
  relay4_status = false;
  led_out_1_val = 0;
  setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
}
void button4_longPressStart() {
  // TBD
}
void button4_duringLongPress() {
  // Only change brightness when LEDs are on
  if(led_out_1_val < LED_MAX_BRIGHTNESS) {
    if((millis() - last_brightness_change_time) > BRIGHTNESS_CHANGE_DELAY) {   
      if(led_out_1_val < (LED_MAX_BRIGHTNESS-BRIGHTNESS_CHANGE_STEPS+1)) {
        if(led_out_1_val < LED_MIN_BRIGHTNESS) {
          led_out_1_val = LED_MIN_BRIGHTNESS;
        }
        else {
          led_out_1_val += BRIGHTNESS_CHANGE_STEPS; 
        }
      }
      else {
        led_out_1_val = LED_MAX_BRIGHTNESS;
      }
      #ifdef DEBUG_EN
        Serial.print("Current brightness value = "); Serial.println(led_out_1_val);
      #endif
      setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
      last_brightness_change_time = millis();
    }
  }
}

void init_inputs() {
  // Configure pins as inputs
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);

  // Setup OneButton parameters 
  button1.setDebounceMs(DEBOUNCE_MS);
  button2.setDebounceMs(DEBOUNCE_MS);
  button3.setDebounceMs(DEBOUNCE_MS);
  button4.setDebounceMs(DEBOUNCE_MS);
  button1.setClickMs(CLICK_MS);
  button2.setClickMs(CLICK_MS);
  button3.setClickMs(CLICK_MS);
  button4.setClickMs(CLICK_MS);
  button1.setPressMs(LONG_PRESS_MS);
  button2.setPressMs(LONG_PRESS_MS);
  button3.setPressMs(LONG_PRESS_MS);
  button4.setPressMs(LONG_PRESS_MS);
  button1.setLongPressIntervalMs(LONG_PRESS_INTERVAL_MS);
  button2.setLongPressIntervalMs(LONG_PRESS_INTERVAL_MS);
  button3.setLongPressIntervalMs(LONG_PRESS_INTERVAL_MS);
  button4.setLongPressIntervalMs(LONG_PRESS_INTERVAL_MS);

  // Setup button 1 callback functions
  button1.attachClick(button1_click);
  button1.attachDoubleClick(button1_doubleClick);
  button1.attachLongPressStart(button1_longPressStart);
  button1.attachDuringLongPress(button1_duringLongPress);

  // Setup button 2 callback functions
  button2.attachClick(button2_click);
  button2.attachDoubleClick(button2_doubleClick);
  button2.attachLongPressStart(button2_longPressStart);
  button2.attachDuringLongPress(button2_duringLongPress);

  // Setup button 3 callback functions
  button3.attachClick(button3_click);
  button3.attachDoubleClick(button3_doubleClick);
  button3.attachLongPressStart(button3_longPressStart);
  button3.attachDuringLongPress(button3_duringLongPress);

  // Setup button 4 callback functions
  button4.attachClick(button4_click);
  button4.attachDoubleClick(button4_doubleClick);
  button4.attachLongPressStart(button4_longPressStart);
  button4.attachDuringLongPress(button4_duringLongPress);
}
void init_outputs() {
  // Configure pins as outputs
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Set outputs high at startup, relay outputs are active low
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
}
void init_led_outputs() {
  // Configure instance for led output 1 and led output 2
  FastLED.addLeds<LED_OUT_1_CHIPSET, LED_OUT_1, LED_OUT_1_COLOR_ORDER>(led_out_1, LED_OUT_1_NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_OUT_2_CHIPSET, LED_OUT_2, LED_OUT_2_COLOR_ORDER>(led_out_2, LED_OUT_2_NUM_LEDS).setCorrection( TypicalLEDStrip );
  // FastLED.setBrightness(LED_MAX_BRIGHTNESS);

  // Turn off LEDs at startup
  setLEDvalueOut1(led_out_1_hue, led_out_1_sat, led_out_1_val);
}

void setup() {
  #ifdef DEBUG_EN
    Serial.begin(115200);
    delay(100);
    Serial.println("\n\nStart Vouwwagen Contoller");
  #endif

  // Initialize peripherals
  init_inputs();
  init_outputs();
  init_led_outputs();

}

void loop() {
  // keep watching the push buttons:
  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();

  delay(10);
}
