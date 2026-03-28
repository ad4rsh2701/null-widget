// ClockWidget.hpp
#pragma once
#include <windows.h>

// Widget Text Location
#define X_DAY_TEXT_POS 40
#define Y_DAY_TEXT_POS 10
#define X_TIME_TEXT_POS 40
#define Y_TIME_TEXT_POS 50

// Text Size
#define DAY_FONT_SIZE 36
#define TIME_FONT_SIZE 18


// Widget Dimensions
#define WIDGET_LENGTH 250
#define WIDGET_WIDTH 80

// Widget Spawn Location
#define X_SPAWN 100
#define Y_SPAWN 100


// A name for our "window template". Do not ask why we need this,
// it's probably what Windows uses to identify our widegt window.
const wchar_t* const WIDGET_CLASS_NAME = L"NullWidget";        // Unicode btw


/*
 * The state of the widget is stored here, it only stores the font information for now.
 * Each widget gets its own state object with its own Font Data.
 */
struct WidgetState {
    HFONT DayFont;
    HFONT TimeFont;
};

// I do realize that WidgetState is probably overkill for just "one" widget,
// but on paper this makes mroe sense to me than `static DayFont`
// and leave everything to the global scope.

/*
 * @brief The Event Handler for the Widget
 *
 * This function handles each Windows Event (like Create Window, Paint Window,
 * Left Mouse button clicked on Window, etc.).
 *
 * Each HWND (window) will store a pointer to its own WidgetState via GWLP_USERDATA,
 * essentially storing a pointer to WidgetState object inside HWND's user data.
 *
 * Usually it's termed as WindowProc as in "Windows Procedure"; procedure == function.
 * But that's stupid in my honest opinion, no offense to anceint coding practices.
 *
 */
LRESULT CALLBACK WidgetHandler(HWND window, UINT event, WPARAM wparam, LPARAM lparam);
