#pragma once
#include <stdint.h>

enum class ButtonID : uint8_t {
    LN = 0, // left north 
    LE = 1, // left east 
    LS = 2, // left south
    LW = 3, // left west
    RN = 4,
    RE = 5,
    RS = 6,
    RW = 7,
    COUNT  = 8   // Dimension of the enum. Not a real Button.
};

static constexpr uint8_t BUTTON_COUNT = static_cast<uint8_t>(ButtonID::COUNT);