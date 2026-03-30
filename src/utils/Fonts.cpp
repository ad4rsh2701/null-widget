#include "Fonts.hpp"
#include <libloaderapi.h>
#include <wingdi.h>


namespace {

    // I could have defined macros which exapnded
    // to font-face names, and used that for both,
    // but fonts like "Kode Mono" break in the .rc
    // file, it has no support for space character

    // Font struct, holding the Font ID and the Font Face Name
    struct Font {
      const wchar_t* resourceID;
      const wchar_t* faceName;
    };

    // I feel like even constexpr is a new thing
    // after dealing with this Ancient API
    constexpr Font DOTO      = {.resourceID = L"R301", .faceName = L"Doto"};
    constexpr Font KODE_MONO = {.resourceID = L"R302", .faceName = L"Kode Mono"};
    constexpr Font URBANIST  = {.resourceID = L"R303", .faceName = L"Urbanist"};

    // Private Helper Function to LOAD the fonts
    void Load(const Font& font) {

        HRSRC resource = FindResourceW(NULL, font.resourceID, L"FONT");     // Find the Font
        HGLOBAL memory = LoadResource(NULL, resource);                      // Load the Font
        void* pointerToFont = LockResource(memory);                         // Lock the Font
        DWORD size = SizeofResource(NULL, resource);                        // Size of the Font
        DWORD count;                                                        // I hate this var declaration cuz Win32 DEMANDS IT
        // The first param NULL, it's actually asking for the HINSTANCE of
        // the executable or the module to load the resource from, we should
        // pass our main HINSTANCE (window) here, but passing that to a helper
        // function isn't suiting my taste, and btw NULL means
        // search in the current executable, which is fine..
        // ...unless I get more exes

        // Load the Font to GDI memory (Process-Private Font Table),
        // so now GDI (or more precisely, `CreateFontW()`) can find
        // these fonts even if it's not in C:/Windows/Fonts/
        AddFontMemResourceEx(pointerToFont, size, NULL, &count);
        // AND YES, I did think about doing it in inline
            // AddFontMemResourceEx(
            //      LockResource(LoadResource(NULL, resource)),
            //      SizeofResource(NULL, resource),
            //      &count
            //  );
        // But that `count`...
        // Win32 requires it to be NON-NULL
        // SO, I NEED TO DECLARE IT. STUPID
        // I will just trust clang to yeet all the vars and optimize.
    }


    // Helper Functions to CREATE the font brush (GDI object)
    HFONT Create(const Font& font, int height, int weight){
        return CreateFontW(
            height, 0, 0, 0, weight,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,
            VARIABLE_PITCH | FF_SWISS,
            font.faceName
        );
    }
}

// We load the custom fonts to the GDI memory.
// We will call this function at the start of WinMain()
// This way, all the custom fonts are loaded once, and
// Windows will cleanup this resource automatically on
// exit, we won't need to use `RemoveFontMemResourceEx`
void WidgetFonts::LoadCustomFonts(){
    Load(URBANIST);
    Load(DOTO);
    Load(KODE_MONO);
}

HFONT WidgetFonts::Urbanist(int height, int weight){
    return Create(URBANIST, height, weight);
}

HFONT WidgetFonts::Doto(int height, int weight){
    return Create(DOTO, height, weight);
}

HFONT WidgetFonts::KodeMono(int height, int weight){
    return Create(KODE_MONO, height, weight);
}
