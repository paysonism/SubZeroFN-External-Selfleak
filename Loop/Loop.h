//static void OverlayHook();
static void InitializeD3D();
static void Cleanup();
static void MyCustomLoop();

void InitializeD3D()
{
    SPOOF_FUNC;

    // Create Direct3D9Ex object
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
        exit(3);

    // Initialize the D3DPRESENT_PARAMETERS struct
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.BackBufferWidth = Width;
    d3dpp.BackBufferHeight = Height;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.hDeviceWindow = Window;
    d3dpp.Windowed = TRUE;

    // Create Direct3D device
    if (FAILED(p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice)))
        exit(3);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Initialize ImGui for Win32 and DirectX 9
    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX9_Init(D3dDevice);

    // Load a custom font
    XorS(font, "C:\\Windows\\Fonts\\Burbank-Big-Condensed-Black.ttf", 14.0f);
    m_pFont = io.Fonts->AddFontFromMemoryTTF(font1, sizeof(font1), 14.0f);

    // Release the Direct3D object (it's no longer needed)
    p_Object->Release();
}




MSG Message = { NULL };
int Loop = 0;
void MyCustomLoop()
{
    SPOOF_FUNC;
    static RECT old_rc;
    ZeroMemory(&Message, sizeof(MSG));

    while (Message.message != WM_QUIT)
    {
        // Process Windows messages
        if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        // Bring the overlay window to the front when it's active
        HWND hwnd_active = GetForegroundWindow();
        if (hwnd_active == hwnd)
        {
            HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
            SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }

        // Handle exit key (VK_END, 0x23)
        if (GetAsyncKeyState(VK_END) & 1)
            exit(8);

        // Get the client rectangle and screen coordinates
        RECT rc;
        POINT xy;
        ZeroMemory(&rc, sizeof(RECT));
        ZeroMemory(&xy, sizeof(POINT));
        GetClientRect(hwnd, &rc);
        ClientToScreen(hwnd, &xy);
        rc.left = xy.x;
        rc.top = xy.y;

        // ImGui setup
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;
        io.ImeWindowHandle = hwnd;
        io.DeltaTime = 1.0f / 60.0f;

        // Update mouse position and button state
        POINT p;
        GetCursorPos(&p);
        io.MousePos.x = p.x - xy.x;
        io.MousePos.y = p.y - xy.y;
        io.MouseDown[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

        // Check for window size changes
        if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
        {
            old_rc = rc;

            Width = rc.right;
            Height = rc.bottom;

            d3dpp.BackBufferWidth = Width;
            d3dpp.BackBufferHeight = Height;
            d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

            // Reset the window size and D3D device
            SetWindowPos(Window, nullptr, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
            D3dDevice->Reset(&d3dpp);
        }

        render();

        // Initialize base address on the first loop iteration
        if (Loop == 0)
        {
            XorS(base, "Process base address: %p.\n"); // l1nkywashere
        }
        Loop++;
    }

    // Shutdown ImGui and clean up resources
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    DestroyWindow(Window);
}




LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    SPOOF_FUNC;
    if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
        return true;

    switch (Message)
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED)
            {
                // Release and recreate ImGui device objects on window resize
                ImGui_ImplDX9_InvalidateDeviceObjects();
                d3dpp.BackBufferWidth = LOWORD(lParam);
                d3dpp.BackBufferHeight = HIWORD(lParam);
                HRESULT hr = D3dDevice->Reset(&d3dpp);
                if (hr == D3DERR_INVALIDCALL)
                    IM_ASSERT(0);
                ImGui_ImplDX9_CreateDeviceObjects();
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, Message, wParam, lParam);
    }
    return 0;
}



void Cleanup()
{
    SPOOF_FUNC;
    TriBuf->Release();
    D3dDevice->Release();
    p_Object->Release();

    DestroyWindow(Window);
    UnregisterClass("notepad", NULL);
}
