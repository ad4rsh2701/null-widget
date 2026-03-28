#include "ClockWidget.hpp"
#include "ContextMenu.hpp"
#include "Fonts.hpp"
#include <basetsd.h>
#include <datetimeapi.h>
#include <minwinbase.h>
#include <sysinfoapi.h>
#include <windef.h>
#include <windows.h>
#include <wingdi.h>
#include <winnls.h>
#include <winuser.h>
#include <time.h>

LRESULT CALLBACK WidgetHandler(HWND window, UINT event, WPARAM wparam, LPARAM lparam){

    // Retrieve the WidgetState pointer stored in this window's GWLP_USERDATA, the User Data.
    // This gives access to this window's instance of the struct.
    WidgetState* state = (WidgetState*)GetWindowLongPtr(window, GWLP_USERDATA);

    // That is the syntax yeah and I don't get it either. Just trust it.
    // You'll have to do a lot of that when dealing with WindowsAPI apparently.

    // At this point in code, `state` just points to NULL, and that's fine, since
    // WM_CREATE will be called first, initializing the WidgetStore and replacing
    // all the garbage or NULL data in the GWLP_USERDATA with the struct instance.
    // It would make sense to put that line later yes... yes, it would make sense.

    switch (event) {

        case WM_CREATE: // is triggered first and only ONCE

            // Instantiating
            state = new WidgetState();

            // Creating Fonts for the DayFont and TimeFont using WidgetFonts namespace
            state -> DayFont = WidgetFonts::Doto(32, FW_BOLD);
            state -> TimeFont = WidgetFonts::Urbanist(16, FW_NORMAL);

            // Update the User Data field to a "pointer to WidgetState instance".
            SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)state);
            // The userdata field is apparently a pointer sized field with key GWLP_USERDATA

            SetTimer(window, 1, 1000, NULL); // Triggers WM_TIMER every 1 second
            // For redrawing the window every second (overkill, a minute updation will work
            // fine for a clock of H:M format, but oh well).

            break;

        case WM_LBUTTONDOWN: // Triggered when left-clicked on the window

            // We want to make the window draggable by holding the left mouse button.
            // I want to be able to move it freely, that's why, don't ask too many questions,
            // this is Windows API, it's already messed up.

            // Stop windows from tracking the mouse
            ReleaseCapture();

            // Then lie to windows, saying "User clicked the title bar",
            // enabling the built-in window-drag mode.
            // SendMessage(window, WM_NCLBUTTONDOWN, HTCAPTION, 0);

            // Apparently that's a "known hack" to make title-bar-less windows
            // draggable, thanks LLMs (yea, macros just expands to random numbers
            // with zero comments or docs).
            // I am ssuming WM_NCLBUTTONDOWN implies that the user pressed the
            // mouse button down and HTCAPTION implies where the press happened,
            // in this case the Title Bar, no clue what's that 0 for though.

            // Okay, pause, let's try a "modern" approach instead.

            // Instruct windows to make the window movable as if the title bar was dragged.
            SendMessage(window, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);

            // I am still not sure about those macros, but...
            //
            // WM_SYSCOMMAND tells windows to perform a built-in window
            // operation (move, resize, minimize, etc.).
            //
            // SC_MOVE is the requested mode, which is move in this case.
            //
            // OR'ed with HTCAPTION, this indicates to move as if title bar was being
            // dragged? But why is it being OR'ed?
            //
            // And 0 is for the location of the pointer, doesn't matter what it is in
            // case of dragging a simple window like this.

            // Wow, okay... Apparently WM_SYSCOMMAND expects a 8-bit parameter, the first
            // four bits (higher bits) define the "mode", i.e. MOVE, RESIZE, etc.
            // And the next four bits (lower bits), are defualted to 0.
            // These lower four bits are used to define the position from where the mode
            // occurs. It doesn't make sense in the hindsight, but say you want to resize
            // from the left bar of the window, for this you'd need to specify the location.
            // The left window, probabaly has some macro for it.
            // In our case, it's the the title bar, with a macro HTCAPTION (expands to 2 btw).
            // This is then OR'ed with the SC_MOVE to fill in the lower 4 bits, forming the
            // entire 8 bits parameter for WM_SYSCOMMAND.
            //
            // If only someone documented this in the WM_SYSCOMMAND code docs instead of just..
            // "WM_SYSCOMMAND expands to 0x0112".
            //
            // Correction: The parameter of WM_SYSCOMMAND is not 8 bits, it's platform dependent,
            // though the concept remains the same, as only the lower 4 bits are left to 0. So,
            // the logic holds true, just the size isn't necesarrily 8. And they did document this..
            // "the low 4 bits are reserved for system use"
            // tfym "system use"?!?! anyways.

            break;

        case WM_TIMER: // this case is triggered every 1000ms or 1 second.
            // Mark the window as "to be refreshed/redrawn"
            InvalidateRect(window, NULL, TRUE);
            // NULL implies the WHOLE window must be redrawn
            // TRUE allows to "erase" the existing background first

            break;

        case WM_PAINT:{
            // this case is triggered when a window is to be drawn, in this case
            // once at start and everytime InvalidateRect is called.

            // if somehow we are here before the WidgetState is initialized, we bail.
            if (!state) break;

            PAINTSTRUCT ps; // a struct containing info about the area to be painted

            // Handle to Device Context, basically a canvas with all the tools
            // to draw on it. Acts as a bridge between the actual pixels on the monitor
            // and the universal display attributes... I think.
            HDC canvas = BeginPaint(window, &ps);

            // standard windows time retireival
            SYSTEMTIME time;
            GetLocalTime(&time);

            wchar_t day[64], timeStr[64];

            // formating them for "wide" characters
            GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &time, L"dddd", day, 64, NULL);
            GetTimeFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &time, L"hh':'mm tt", timeStr, 64);

            // Text Color
            SetTextColor(canvas, RGB(255,255,255));

            // Apparently the windows graphics device interface (GDI), requires that we restore the
            // original state of the font. So, we save that to `defaultFont`.
            // This is possible as, while replacing the font, `SelectObject` returns the previously
            // stored font value, which is the default font value.
            HFONT defaultFont = (HFONT)SelectObject(canvas, state->DayFont);    // Loading the font for Day
            SetBkMode(canvas, TRANSPARENT);                                     // Background Color
            TextOutW(canvas, 40, 5, day, (int)wcslen(day));                     // The Day text with postion coordinates
            SelectObject(canvas, state->TimeFont);                              // Loading the Font for Time
            TextOutW(canvas, 40, 40, timeStr, (int)wcslen(timeStr));            // The Time text with position coordinates
            SelectObject(canvas, defaultFont);                                  // Restoring the original font
            EndPaint(window, &ps);                                              // Ending the instance.. I guess?

            break;
        }



        case WM_RBUTTONUP:{
            POINT pt;
            GetCursorPos(&pt);

            CreateWindowExW(
                WS_EX_TOOLWINDOW | WS_EX_TOPMOST, // Keep it at TOP
                MENU_CLASS_NAME, NULL,
                WS_POPUP | WS_VISIBLE,
                pt.x, pt.y,
                MENU_LENGTH, MENU_WIDTH,
                window,     // New thing, it's specifying who is the parent of this menu
                NULL,       // I still do not know this
                (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE),
                // We are not in WinMain, so we have no way to directly access the "HINSTANCE instance",
                // The handle to the executable (first param of WinMain). So, we are kindly asking
                // "window" to show its HINSTANCE value via GetWindowLongPointer.
                NULL        // Nope
            );
            break;
        }

        case WM_DESTROY: // Triggered when the executable is killed
            // Basically cleanup

            if (state) {
                // Kill the font handles
                DeleteObject(state->DayFont);
                DeleteObject(state->TimeFont);

                delete state;   // Free the struct memory
            }
            PostQuitMessage(0);
            return 0;
    }
    // Handle every other case normally, thank you Windows
    return DefWindowProc(window, event, wparam, lparam);
}
