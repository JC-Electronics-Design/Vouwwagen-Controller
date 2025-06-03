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
#define BAUD 115200

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

#define MIN_LOOP_LENGTH_MS 10

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

// BLE configuration
#define BLE_NAME "VW-Controller"
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID                    "8c113600-3ec3-452c-868c-7d6b5a3afe1c"
#define RELAY_SW1_CHARACTERISTIC_UUID   "8c113601-3ec3-452c-868c-7d6b5a3afe1c"
#define RELAY_SW2_CHARACTERISTIC_UUID   "8c113602-3ec3-452c-868c-7d6b5a3afe1c"
#define RELAY_SW3_CHARACTERISTIC_UUID   "8c113603-3ec3-452c-868c-7d6b5a3afe1c"
#define RELAY_SW4_CHARACTERISTIC_UUID   "8c113604-3ec3-452c-868c-7d6b5a3afe1c"
#define LED_SW1_CHARACTERISTIC_UUID     "8c113605-3ec3-452c-868c-7d6b5a3afe1c"
#define LED_COLOR1_CHARACTERISTIC_UUID  "8c113606-3ec3-452c-868c-7d6b5a3afe1c"

#endif