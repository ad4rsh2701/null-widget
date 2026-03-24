#include "../../include/Fonts.hpp"

HFONT WidgetFonts::Urbanist(int size, int weight = FW_NORMAL){
    return CreateFontA(size, 0, 0, 0, weight,
                       FALSE, FALSE, FALSE,
                       ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                       DEFAULT_PITCH | FF_SWISS, "Urbanist");
}

HFONT WidgetFonts::Doto(int size, int weight = FW_NORMAL){
    return CreateFontA(size, 0, 0, 0, weight,
                       FALSE, FALSE, FALSE,
                       ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                       DEFAULT_PITCH | FF_SWISS, "Doto");
}

HFONT WidgetFonts::KodeMono(int size, int weight = FW_NORMAL){
    return CreateFontA(size, 0, 0, 0, weight,
                       FALSE, FALSE, FALSE,
                       ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                       DEFAULT_PITCH | FF_SWISS, "KodeMono");
}
