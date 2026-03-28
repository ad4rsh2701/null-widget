#include "ClockWidget.hpp"
#include "ContextMenu.hpp"
#include <minwindef.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>

// The main entry point for Win32 apps: WinMain
// @param instance: Handle to the executable, basically an identifer
// of our widget executable
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int){

    // Apparently we are creating a template for our window
    // WNDCLASS creates a template for a window (just like how
    // a class is a template for an object, closest thing to
    // OOP in Windows API so far.)
    WNDCLASSW widgetTemplate = { };

    // We define what kind of window our window will be here
    widgetTemplate.lpfnWndProc = WidgetHandler;                                 // Refer our Message Handler
    widgetTemplate.hInstance = instance;                                        // Refer the Executable
    widgetTemplate.lpszClassName = CLASS_NAME;
    widgetTemplate.style = CS_HREDRAW | CS_VREDRAW;                             // Redraw in X and Y enabled
    widgetTemplate.hCursor = LoadCursor(NULL, IDC_ARROW);                       // Load the default cursor on hover
    widgetTemplate.hbrBackground = CreateSolidBrush(RGB(20,20,20));             // Assign Background color

    // Now we register our template and now we can reference it by CLASS_NAME?
    RegisterClassW(&widgetTemplate);

    CreateWindowExW(
        WS_EX_TOOLWINDOW,                   // Hide executable from taskbar
        WIDGET_CLASS_NAME, L"NullWidget",   // Use "this" template
        WS_POPUP | WS_VISIBLE,              // Borderless window to be shown after creation (same bit packing logic.. ig?)
        X_SPAWN, Y_SPAWN,                   // Initial X,Y coords
        WIDGET_LENGTH,WIDGET_WIDTH,         // Width and Height of the window in px
        NULL, NULL, instance, NULL          // NO.
    );
    // WS_EX_TOOLWINDOW  — hides it from the taskbar
    // WS_POPUP          — borderless window (no title bar, no frame)
    // WS_VISIBLE        — show immediately after creation
    // 100, 100          — initial x, y position on screen
    // 250, 80           — width, height in pixels

    // Now, for the Context Menu
    WNDCLASSW menuTemplate = { };
    menuTemplate.lpfnWndProc = ContextMenuHandler;
    menuTemplate.hInstance = instance;
    menuTemplate.lpszClassName = MENU_CLASS_NAME;
    menuTemplate.hCursor = LoadCursor(NULL, IDC_ARROW);
    menuTemplate.hbrBackground = CreateSolidBrush(RGB(15, 15, 15));
    RegisterClassW(&menuTemplate);
    // We will handle Menu Window creation in ClockWidget.cpp

    // MSG holds one event from the Windows event queue, they said.
    // I think it's a "holder" for those events Windows works on,
    // you know.. those MACROS WHICH EXPANDS TO HEX.
    // It's a container for one of those events.
    MSG eventMsg = { };

    // The always on loop for our window for those messages
    // GetMessages gets those messages (see it wasn't hard to
    // properly name things microsoft.) and fills the event_msg
    // with that MACRO.
    while (GetMessageW(&eventMsg, NULL, 0, 0)) {

        //      TranslateMessage translates those Macros to
        //      meaningfull things I guess, I am assuming those
        //      numbers/codes are mapped to instructions/functions.
        //
        // Nope, that's wrong, it's more of a "specifier"? Like
        // it adds more details, why is it named translate?!?
        // And I won't use this atm, since I am not pressing
        // any keys or need to attach extra information, the
        // only complexity is dragging amd mouse click doesn't
        // need extra info.
        //
        // WE WILL NEED THIS, IF KEYBOARD gets involved though.
        // TranslateMessage(&eventMsg);

        // Send the message we stored to our "WidgetHandler"
        // cuz we need to spoonfeed these event messages windows
        // detected and created to our event handler we created
        DispatchMessageW(&eventMsg);
    }

    // We need to delete the "Brush" we created, or else memory leak
    // This is allocated on heap apparently.
    // And WinMain will just delete the struct WidgetTemplate
    // on return, but won't delete the allocated heap things.
    // Classic, but inconvinient. And I am not creating a
    // an extra var for this.
    DeleteObject(widgetTemplate.hbrBackground);     // Direct access and yeet
    DeleteObject(menuTemplate.hbrBackground);
    // Executed only when the loop ends which signals
    // the end of the program.

    // I have given up on documenting this cleanly,
    // I am mad.

    return 0;
}

// I am so done with typedefs and exapands to hex
// In my honest opinion, WinAPI isn't bad, it's
// intutive.. just in a very ancient kind of way.
// Sighhh, why am I still using Windows!?
