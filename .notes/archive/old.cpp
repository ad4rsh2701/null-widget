#include <time.h>

// Initial Snippet Example (AI-Assisted, I do not know Windows API so let me learn)
// Not Licensed
// Comments starting with ">" are AI geenrated

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // what are these parameters, THE HECK
    switch (uMsg) {
        case WM_CREATE: // so this does.. What exactly?
            SetTimer(hWnd, 1, 1000, NULL);
            break;

        case WM_LBUTTONDOWN:
            // > This trick tells Windows the user clicked the 'caption' (title bar)
            // > allowing you to drag the window anywhere.
            // I just trust that??
            ReleaseCapture();
            SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            break;

        case WM_TIMER:
            // finally a decently named function that makes sense, BUT STILL what's with this case
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_PAINT: { // THIS LITERALLY EXPANDS TO 0x000F WHAT
            PAINTSTRUCT ps; // okay
            HDC hdc = BeginPaint(hWnd, &ps); // aight, you lost me here

            time_t now = time(0); // we get time.. kay, something normal
            struct tm ltm; // some struct? oh time struct, the lack of description istg..
            localtime_s(&ltm, &now); // Oh I think this.. matches the local time to system time? I think?

            // Normal C++ yay!
            char day[32], timeStr[32];
            // we get dayy
            strftime(day, sizeof(day), "%A", &ltm);
            // we get timeee
            strftime(timeStr, sizeof(timeStr), "%I:%M %p", &ltm);
            // see it wasn't that hard!


            // Custom Font time.. something
            HFONT hFont = CreateFontA(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                     ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                     DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Urbanist");

            // Ig we need to hold it too? Hold it? tf? oh its hOLD, my god.
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // sensible code block
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT); // what was hdc again? Oh right I got lost there.

            // This probably prints?
            TextOutA(hdc, 10, 5, day, (int)strlen(day));

            // > Smaller font for time
            HFONT hTimeFont = CreateFontA(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                         ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                         DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Urbanist");
            SelectObject(hdc, hTimeFont);
            TextOutA(hdc, 10, 40, timeStr, (int)strlen(timeStr));

            // > Cleanup
            // Now we yeet things? using functions?
            SelectObject(hdc, hOldFont);
            DeleteObject(hFont);
            DeleteObject(hTimeFont);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_DESTROY:
            // Fair
            PostQuitMessage(0);
            return 0;
    }
    // not Fair, what even is DefWindowProc
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Entry point for windows apps is WinMain, that's the only thing I get and know
// the heck are those parameters though, really.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    // Why.. oh wait this is normal C++ stuff
    const char CLASS_NAME[] = "UrbanistWidget";

    // some windows class presumably.. that does.. WHAT?
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc; // eh? so here?? we creating a process?
    wc.hInstance = hInstance; // at least this makes sense... nvm
    wc.lpszClassName = CLASS_NAME; // get named or wtv
    // > Redraw on resize/move to prevent flickering
    // cool
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // making cursor the default cursor on hover? I guess?
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // if this is setting the bg color then what the heck was all that before??
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(20, 20, 20));

    // what.
    RegisterClass(&wc);

    // this creates.. the process or the window? Window ig.
    HWND hWnd = CreateWindowEx(
        WS_EX_TOOLWINDOW,
        CLASS_NAME, "Clock",
        WS_POPUP | WS_VISIBLE,
        100, 100, 250, 80,
        NULL, NULL, hInstance, NULL
    );


    // what's the purpose of this
    MSG msg = { };
    // maybe we empty the process and all?
    // idk
    // Some loop for entire program?
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        // message are treated as events maybe?
    }
    return 0;
}

// compiled using: clang++ src/main.cpp -o null.exe -luser32 -lgdi32 -Xlinker /subsystem:windows
// Or use g++, but those are the flags and linkers (I am biased towards clang)
// and Idk what those libs are(first two makes sense, what even is -Xlinker tho?)
// , I just know that /subsystem:windows tells the compiler that it's a windows
// application and to not open console with it.. soemthing like that.
