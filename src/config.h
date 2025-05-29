/**
 * @file config.h
 * @author Jonathan Caes
 * @brief This file contains the configuration parameters for the Vouwwagen Controller code
 * @version 1.0
 * @date 2025-05-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef CONFIG_H
#define CONFIG_H

/*** DEBUGGING ***/
#define DEBUG_EN    // Uncomment to enable debugging via Serial

/*** Input configuration ***/
// Pin configuration
#define BUTTON_1  21
#define BUTTON_2  22
#define BUTTON_3  23
#define BUTTON_4  25

// OneButton configuration
#define ACTIVE_LOW  false
#define DEBOUNCE_MS 20
#define CLICK_MS  250
#define LONG_PRESS_MS 600
#define LONG_PRESS_INTERVAL_MS  100

/*** Output configuration ***/
// Pin configuration, info: relays are active low
#define RELAY_1 4
#define RELAY_2 13
#define RELAY_3 16
#define RELAY_4 17

/*** LED configuration ***/
// Pin configuration
#define LED_OUT_1 18
#define LED_OUT_2 19

// FastLED configuration
// LED output 1
#define LED_OUT_1_COLOR_ORDER   GRB
#define LED_OUT_1_CHIPSET       WS2812B
#define LED_OUT_1_NUM_LEDS      300

// LED output 2
#define LED_OUT_2_COLOR_ORDER   GRB
#define LED_OUT_2_CHIPSET       WS2812B
#define LED_OUT_2_NUM_LEDS      300

// Visual configuration
#define LED_MIN_BRIGHTNESS 25
#define LED_MAX_BRIGHTNESS 255
#define LED_MAX_SATURATION 255
#define WHITE_SAT 0
#define COLOR_CHANGE_DELAY 100
#define COLOR_CHANGE_HUE_STEPS 1
#define BRIGHTNESS_CHANGE_DELAY 50
#define BRIGHTNESS_CHANGE_STEPS 5

#endif