#pragma once
enum class Scales {
    RATIO_C = 0,        // C
    RATIO_C_SHARP,  // C# (Db)
    RATIO_D,        // D
    RATIO_D_SHARP,  // D# (Eb)
    RATIO_E,        // E
    RATIO_F,        // F
    RATIO_F_SHARP,  // F# (Gb)
    RATIO_G,        // G
    RATIO_G_SHARP,  // G# (Ab)
    RATIO_A,        // A
    RATIO_A_SHARP,  // A# (Bb)
    RATIO_B,        // B
};
const float FREQUENCY_RATIOS[] = {
    1.0f,            // RATIO_C
    16.0f / 15.0f,   // RATIO_C_SHARP
    9.0f / 8.0f,     // RATIO_D
    6.0f / 5.0f,     // RATIO_D_SHARP
    5.0f / 4.0f,     // RATIO_E
    4.0f / 3.0f,     // RATIO_F
    45.0f / 32.0f,   // RATIO_F_SHARP
    3.0f / 2.0f,     // RATIO_G
    8.0f / 5.0f,     // RATIO_G_SHARP
    5.0f / 3.0f,     // RATIO_A
    9.0f / 5.0f,     // RATIO_A_SHARP
    15.0f / 8.0f,    // RATIO_B
};