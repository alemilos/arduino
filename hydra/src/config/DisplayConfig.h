#pragma once

// ═══════════════════════════════════════════════════════════
// SINGLE POINT TO SWITCH BUILD TARGET
// Change TARGET_BOARD to: BOARD_WOKWI, BOARD_ESP32, BOARD_UNO
// ═══════════════════════════════════════════════════════════

#define BOARD_WOKWI  1
#define BOARD_ESP32  2
#define BOARD_UNO    3

// The target board used
#ifndef TARGET_BOARD
    #define TARGET_BOARD BOARD_WOKWI   // default one if not passed by cli arguments by platformio
#endif

#if TARGET_BOARD == BOARD_WOKWI || TARGET_BOARD == BOARD_UNO
    #include <Adafruit_ILI9341.h>
    #define USING_ADAFRUIT_ILI9341
    using TFTDriver = Adafruit_ILI9341;

#elif TARGET_BOARD == BOARD_ESP32
    #include <TFT_eSPI.h>
    #define USING_TFT_eSPI
    using TFTDriver = TFT_eSPI;

#else
    #error "TARGET_BOARD must be BOARD_WOKWI, BOARD_ESP32, or BOARD_UNO"
#endif

// ── Pin mapping (ignored by TFT_eSPI — configured via User_Setup.h) ──
#if TARGET_BOARD == BOARD_WOKWI
    static constexpr uint8_t PIN_TFT_CS  = 5;
    static constexpr uint8_t PIN_TFT_DC  = 2;
    static constexpr uint8_t PIN_TFT_RST = 4;
#elif TARGET_BOARD == BOARD_UNO
    static constexpr uint8_t PIN_TFT_CS  = 9;
    static constexpr uint8_t PIN_TFT_DC  = 8;
    static constexpr uint8_t PIN_TFT_RST = 7;
#endif


// ── Copatibility shims ───────────────────────────────────────
// TFT_eSPI uses tft.setTextColor(fg, bg) — same as Adafruit, fine.
// TFT_eSPI uses tft.fillScreen(), drawFastHLine(), etc. — same API surface.
// The one difference: TFT_eSPI init is tft.init(), Adafruit is tft.begin().
#ifdef USING_ADAFRUIT_ILI9341
    #define TFT_INIT(tft)  (tft).begin()
#elif defined(USING_TFT_eSPI)
    #define TFT_INIT(tft)  (tft).init()
#endif