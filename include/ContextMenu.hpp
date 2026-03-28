// ContextMenu.hpp
#pragma once
#include <windows.h>

const wchar_t* const MENU_CLASS_NAME = L"ContextMenuClass";

// Maybe I will need this?
struct MenuState {
    HFONT MenuFont;
};

/*
 * @brief The Event Handler for our Context Menu
 *
 * a.k.a the Right Click Menu
 *
 * Born for the sole purpose of adding an exit option for now.
 */
LRESULT CALLBACK ContextMenuHandler(HWND menu, UINT event, WPARAM wparam, LPARAM lparam);
