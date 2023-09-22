
void SetWindowToTarget()
{
    SPOOF_FUNC;

    if (!hwnd)
    {
        exit(0);
        return;
    }

    DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
    RECT gameRect;

    if (GetWindowRect(hwnd, &gameRect))
    {
        int newWidth = gameRect.right - gameRect.left;
        int newHeight = gameRect.bottom - gameRect.top;

        if (dwStyle & WS_BORDER)
        {
            gameRect.top += 32;
            newHeight -= 39;
        }

        // Only move the window if necessary
        if (newWidth != Width || newHeight != Height)
        {
            Width = newWidth;
            Height = newHeight;
            ScreenCenterX = Width / 2;
            ScreenCenterY = Height / 2;
            MoveWindow(Window, gameRect.left, gameRect.top, Width, Height, true);
        }
    }
}


const MARGINS Margin = { -1 };

void OverlayHook()
{
    SPOOF_FUNC;

    // Cache system metrics to reduce API calls
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

    WNDCLASS windowClass = { 0 };
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = WinProc;
    windowClass.lpszClassName = "notepad";
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&windowClass))
    {
        // Efficient error handling
        MessageBox(NULL, "Failed to register window class.", "Error", MB_ICONERROR | MB_OK);
        return;
    }

    Window = CreateWindow("notepad",
        NULL,
        WS_POPUP,
        0,
        0,
        screenWidth,
        screenHeight,
        NULL,
        NULL,
        NULL,
        NULL);

    if (Window)
    {
        ShowWindow(Window, SW_SHOW);

        DwmExtendFrameIntoClientArea(Window, &Margin);
        SetWindowLong(Window, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
        UpdateWindow(Window);
    }
}
