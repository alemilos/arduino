#pragma once
#include <stdint.h>   


#pragma once
#include <stdint.h>

// ── Timing ──────────────────────────────────────────────
static constexpr uint16_t TASK_PERIOD_SENSORS_MS   = 20;
static constexpr uint16_t TASK_PERIOD_INPUT_MS      = 20;
static constexpr uint16_t TASK_PERIOD_DISPLAY_MS    = 100;
static constexpr uint16_t TASK_PERIOD_SERIAL_LOG_MS = 500;

// ── Limiti fisici ────────────────────────────────────────
static constexpr uint8_t  SPEED_MAX_KMH    = 50;
static constexpr uint16_t RPM_MAX          = 4000;
static constexpr float    VOLTAGE_MIN      = 11.5f;
static constexpr float    VOLTAGE_MAX      = 14.5f;

// ── Display — dimensioni fisiche ─────────────────────────
static constexpr uint16_t LCD_WIDTH        = 480;
static constexpr uint16_t LCD_HEIGHT       = 320;

// ── Display — colori (RGB565) ────────────────────────────
static constexpr uint16_t COLOR_BG         = 0x0000;  // black
static constexpr uint16_t COLOR_ACCENT     = 0x07FF;  // cyan
static constexpr uint16_t COLOR_TEXT       = 0xFFFF;  // white
static constexpr uint16_t COLOR_WARN       = 0xF800;  // red
static constexpr uint16_t COLOR_OK         = 0x07E0;  // green
static constexpr uint16_t COLOR_LABEL      = 0x8410;  // grey
static constexpr uint16_t COLOR_ORANGE     = 0xFD20;

// ── Display — layout zone ────────────────────────────────
//
//  ┌────────────────────────────────────────────────┐
//  │  SPEED          │        RPM                   │  row 0 (y: 0–159)
//  ├─────────────────┴──────────────────────────────┤
//  │  VOLT  │  CURR  │  EFF                         │  row 1 (y: 160–239)
//  ├────────────────────────────────────────────────┤
//  │  STATUS BAR                                    │  row 2 (y: 240–319)
//  └────────────────────────────────────────────────┘
static constexpr uint16_t ZONE_TOP_H       = 160;
static constexpr uint16_t ZONE_MID_Y       = 160;
static constexpr uint16_t ZONE_MID_H       = 80;
static constexpr uint16_t ZONE_STATUS_Y    = 240;
static constexpr uint16_t ZONE_STATUS_H    = 80;

// Speed zone (left)
static constexpr uint16_t SPD_X            = 10;
static constexpr uint16_t SPD_Y            = 20;
static constexpr uint16_t SPD_VAL_X        = 10;
static constexpr uint16_t SPD_VAL_Y        = 55;
static constexpr uint16_t SPD_CLEAR_W      = 220;
static constexpr uint16_t SPD_CLEAR_H      = 90;

// Middle row values
static constexpr uint16_t VOLT_VAL_X       = 10;
static constexpr uint16_t VOLT_VAL_Y       = 195;
static constexpr uint16_t CURR_VAL_X       = 170;
static constexpr uint16_t CURR_VAL_Y       = 195;
static constexpr uint16_t EFF_VAL_X        = 330;
static constexpr uint16_t EFF_VAL_Y        = 195;
static constexpr uint16_t MID_CLEAR_W      = 140;
static constexpr uint16_t MID_CLEAR_H      = 35;

// ── Serial ──────────────────────────────────────────────
static constexpr uint32_t SERIAL_BAUD_DEBUG = 115200;
static constexpr uint32_t SERIAL_BAUD_ECU   = 9600;
static constexpr uint8_t  SERIAL_FRAME_SOF  = 0xAA;
static constexpr uint8_t  SERIAL_FRAME_LEN  = 8;

// ── Pin mapping ──────────────────────────────────────────
static constexpr uint8_t PIN_BTN_UP        = 2;
static constexpr uint8_t PIN_BTN_DOWN      = 3;
static constexpr uint8_t PIN_BTN_LEFT      = 4;
static constexpr uint8_t PIN_BTN_RIGHT     = 5;
static constexpr uint8_t PIN_BTN_SELECT    = 6;
static constexpr uint8_t PIN_BTN_BACK      = 7;
static constexpr uint8_t PIN_BTN_MODE      = 8;
static constexpr uint8_t PIN_BTN_EXTRA     = 9;