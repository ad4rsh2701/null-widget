#include "ContextMenu.hpp"
#include "Fonts.hpp"
#include <minwindef.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>


LRESULT CALLBACK ContextMenuHandler(HWND menu, UINT event, WPARAM wparam, LPARAM lparam){

    MenuState* state = (MenuState*)GetWindowLongPtr(menu, GWLP_USERDATA);

    switch(event) {

        case WM_CREATE:
            state = new MenuState();
            state -> MenuFont = WidgetFonts::KodeMono(16, FW_NORMAL);
            SetWindowLongPtr(menu, GWLP_USERDATA, (LONG_PTR)state);
            break;

        case WM_ACTIVATE: // is triggered when

            // I will just link to the docs:
            // https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-activate
            if (LOWORD(wparam) == WA_INACTIVE){
                DestroyWindow(menu);
            }
            break;

        case WM_PAINT:{
            PAINTSTRUCT ps;

            HDC menuCanvas = BeginPaint(menu, &ps);

            const wchar_t* exitStr = L"Close Widget";

            SetTextColor(menuCanvas, RGB(244, 244, 244));

            HFONT defaultFont = (HFONT)SelectObject(menuCanvas, state->MenuFont);
            SetBkMode(menuCanvas, TRANSPARENT);

            TextOutW(menuCanvas, 10, 5, exitStr, (int)wcslen(exitStr));
            // I almost want to hardcode the string size as 13, but judging
            // from the fact that I can't count (it's actually 12) I will let
            // wcslen do that job, it will be computed at compile time anyways.

            SelectObject(menuCanvas, defaultFont);
            EndPaint(menu, &ps);

            break;
        }

        case WM_LBUTTONUP:{

            HWND hParent = GetWindow(menu, GW_OWNER);

            PostMessage(hParent, WM_CLOSE, 0, 0);
            DestroyWindow(menu);
            break;
        }

        case WM_DESTROY:
            if (state) {
                DeleteObject(state->MenuFont);
            }
            delete state;
            break;
    }

    return DefWindowProc(menu, event, wparam, lparam);
}
