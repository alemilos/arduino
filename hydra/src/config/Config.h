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
//  ┌──────────────┬──────────────┬──────────────┐
//  │ LOGO │FUEL   │ CABIN TEMP   │              │  row 0 (y: 0–79)
//  │      │CELL   │              │              │
//  ├──────────────┴──────────────┴──────────────┤
//  │                                            │
//  │              SPEED (CENTER)                │  row 1 (y: 80–219)
//  │                                            │
//  ├──────────────┬──────────────┬──────────────┤
//  │ H₂ CONSUMP   │ CUSTOM       │ MOTOR CURR   │  row 2 (y: 220–319)
//  └──────────────┴──────────────┴──────────────┘

// ── Row zones
static constexpr uint16_t ZONE_TOP_Y       = 0;
static constexpr uint16_t ZONE_TOP_H       = 80;
static constexpr uint16_t ZONE_CENTER_Y    = 80;
static constexpr uint16_t ZONE_CENTER_H    = 140;
static constexpr uint16_t ZONE_BOTTOM_Y    = 220;
static constexpr uint16_t ZONE_BOTTOM_H    = 100;

// ── Top row: Logo, Fuel Cell, Cabin Temp (for backward compatibility)
static constexpr uint16_t ZONE_MID_Y       = ZONE_BOTTOM_Y;
static constexpr uint16_t ZONE_MID_H       = ZONE_BOTTOM_H;
static constexpr uint16_t ZONE_STATUS_Y    = ZONE_BOTTOM_Y;
static constexpr uint16_t ZONE_STATUS_H    = ZONE_BOTTOM_H;

// Top row sections (horizontal thirds)
static constexpr uint16_t LOGO_X           = 10;
static constexpr uint16_t LOGO_Y           = 10;
static constexpr uint16_t LOGO_W           = 70;
static constexpr uint16_t LOGO_H           = 60;

static constexpr uint16_t FUELCELL_X       = 90;
static constexpr uint16_t FUELCELL_Y       = 10;
static constexpr uint16_t FUELCELL_LABEL_Y = 15;
static constexpr uint16_t FUELCELL_VAL_Y   = 40;

static constexpr uint16_t CABIN_X          = 300;
static constexpr uint16_t CABIN_Y          = 10;
static constexpr uint16_t CABIN_LABEL_Y    = 15;
static constexpr uint16_t CABIN_VAL_Y      = 40;

// Center zone: Speed (full width, centered)
static constexpr uint16_t SPD_X            = 90;
static constexpr uint16_t SPD_Y            = 100;
static constexpr uint16_t SPD_VAL_X        = 120;
static constexpr uint16_t SPD_VAL_Y        = 130;
static constexpr uint16_t SPD_CLEAR_W      = 240;
static constexpr uint16_t SPD_CLEAR_H      = 90;

// Bottom row sections (horizontal thirds)
static constexpr uint16_t H2_X             = 10;
static constexpr uint16_t H2_LABEL_Y       = 235;
static constexpr uint16_t H2_VAL_Y         = 270;
static constexpr uint16_t H2_CLEAR_W       = 140;
static constexpr uint16_t H2_CLEAR_H       = 35;

static constexpr uint16_t CUSTOM_X         = 160;
static constexpr uint16_t CUSTOM_Y         = 230;
static constexpr uint16_t CUSTOM_W         = 160;
static constexpr uint16_t CUSTOM_H         = 80;

static constexpr uint16_t CURR_X           = 320;
static constexpr uint16_t CURR_VAL_Y       = 270;
static constexpr uint16_t CURR_LABEL_Y     = 235;
static constexpr uint16_t CURR_CLEAR_W     = 140;
static constexpr uint16_t CURR_CLEAR_H     = 35;

// Voltage position (for backward compatibility - will be in top row)
static constexpr uint16_t VOLT_VAL_X       = FUELCELL_X;
static constexpr uint16_t VOLT_VAL_Y       = FUELCELL_VAL_Y;

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