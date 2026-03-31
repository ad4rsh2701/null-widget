#include <ContextMenu.hpp>
#include <Fonts.hpp>

LRESULT CALLBACK ContextMenuHandler(HWND menu, UINT event, WPARAM wparam, LPARAM lparam){

    auto* state = reinterpret_cast<MenuState *>(GetWindowLongPtr(menu, GWLP_USERDATA));

    switch(event) {

        case WM_CREATE:
            state = new MenuState();
            state -> MenuFont = WidgetFonts::KodeMono(FONT_SIZE, FW_NORMAL);
            SetWindowLongPtr(menu, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(state));
            return 0;

        case WM_ACTIVATE: // is triggered when...
            // I will just link to the docs:
            // https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-activate
            if (LOWORD(wparam) == WA_INACTIVE){
                DestroyWindow(menu);
            }
            return 0;

        case WM_PAINT:{

            if (!state) return 0;

            PAINTSTRUCT ps;

            HDC menuCanvas = BeginPaint(menu, &ps);

            auto exitStr = L"Close Widget";
            SetTextColor(menuCanvas, RGB(244, 244, 244));
            auto defaultFont = static_cast<HFONT>(SelectObject(menuCanvas, state->MenuFont));
            SetBkMode(menuCanvas, TRANSPARENT);
            TextOutW(menuCanvas, X_TEXT_POS, Y_TEXT_POS, exitStr, static_cast<int>(wcslen(exitStr)));
            // I almost want to hardcode the string size as 13, but judging
            // from the fact that I can't count (it's actually 12), I will let
            // wcslen do that job, it will be computed at compile time anyway.

            SelectObject(menuCanvas, defaultFont);
            EndPaint(menu, &ps);
            return 0;
        }

        case WM_LBUTTONUP:{
            HWND hParent = GetWindow(menu, GW_OWNER);
            PostMessage(hParent, WM_CLOSE, 0, 0);
            DestroyWindow(menu);
            return 0;
        }

        case WM_DESTROY:
            if (state) {
                DeleteObject(state->MenuFont);
                delete state;  // yeet
            }
            return 0;

        default:
            return DefWindowProc(menu, event, wparam, lparam);
    }
}
