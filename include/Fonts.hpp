// Fonts.hpp
#pragma once
#include <windows.h>

namespace WidgetFonts {

    /*
     * @brief Loads Custom Fonts to GDI memory
     */
    void LoadCustomFonts();

    // Create the URBANIST font
    HFONT Urbanist(int size, int weight = FW_NORMAL);

    // Create the DOTO font
    HFONT Doto(int size, int weight = FW_NORMAL);

    // Create the KODE MONO font
    HFONT KodeMono(int size, int weight = FW_NORMAL);
}
