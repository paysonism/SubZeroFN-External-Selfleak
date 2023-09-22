#pragma once


// Namespace for color constants
namespace VisibleColCheck {
    float r = 0;
    float g = 255;
    float b = 0;
}

namespace InVisibleColCheck {
    float r = 255;
    float g = 0;
    float b = 0;
}

// Variables related to aiming
static int aimkeypos = 3;
static int aimbone = 1;
int faken_rot = 0;

// Angle conversion functions
float BOG_TO_GRD(float BOG) {
    return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
    return (M_PI / 180) * GRD;
}



// General Settings
bool ShowMenu = true;
bool watermark = true;
bool fpsCounter = true;
bool vectorview = false;

// ESP Settings
bool Esp = true;
bool Esp_box = false;
bool skeletonesp = false;
bool weaponesp = false;
bool cornerbox = false;
bool cornerbox2 = false;
bool Esp_info = false;
bool Esp_line = false;
bool ThreeDBoxEsp = false;
bool sdesp = false;
bool CrosshairSnapLines = true;
bool crosshairEnabled = false;
bool Skeleton = false;
bool enablefov = true;
bool fovcircle = false;
bool slefESP = false;
bool square_fov = false;
bool playernames = false;
bool ammoesp = false;
bool ammoESP = false;
bool EnemyAlert = false;
bool Esp_Distance = false;
bool lineheadesp = false;
bool cornerline = false;
bool fillbox = false;
bool fovcirclefilled = false;

// Aimbot Settings
bool Aimbot = true;
bool clientspinbot = false;
bool AimWhileJumping = false;
bool triggerbot = false;

// Miscellaneous Settings
bool test2 = false;
bool norecoil = false;
int Locations = 0;
bool lobby = false;
bool fuel = false;
bool animate = false;
bool exploits = false;
bool targetlines = false;
bool WindowStreamProof = false;
bool RapidFire = false;
bool spinbot = false;
bool boatspeed = false;
bool bostspeed = false;
bool carto = false;
bool Safemode = true;
bool reloadcheck = true;
bool SkipKnocked = true;

// Adjustable Settings
float minFOV = 0.1f;
float maxFOV = 359.9f;
float BoxWidthValue = 0.550;
float ChangerFOV = 80;


// Font and text-related variables
ImFont* m_pFont;
int smooth = 3;
int thickness = 1;
int thicknessa = 1;

// Visibility and aiming variables
static int VisDist = 200;
int AimFOV = 200;
static int aimkey;
static int hitbox;
static int hitboxpos = 0;

// Color variables
float fl_VisibleColor[3];
float fl_InVisibleColor[3];

 // Pointers to various memory addresses
 uintptr_t Penis;
 uintptr_t PlayerCameraManager;
 uintptr_t Crrneytwep;
 uintptr_t AOFFSETS;
 uintptr_t CurrentVehicle;
 DWORD_PTR ActorCount;
 DWORD_PTR Gameinstance;
 DWORD_PTR LocalPlayers;
 DWORD_PTR GameState;
 DWORD_PTR PlayerArray;

 DWORD_PTR Uworld;
 DWORD_PTR LocalPawn;
 DWORD_PTR PlayerState;
 DWORD_PTR Localplayer;
 DWORD_PTR Rootcomp;
 DWORD_PTR PlayerController;
 DWORD_PTR Persistentlevel;
 Vector3 localactorpos;

 // Other variables
 uint64_t TargetPawn;
 int localplayerID;

 RECT GameRect = { NULL };
 D3DPRESENT_PARAMETERS d3dpp;
 DWORD ScreenCenterX;
 DWORD ScreenCenterY;
 Vector3 LocalRelativeLocation;

 // Struct definition
 struct FBoxSphereBounds
 {
	 Vector3 Origin;
	 Vector3 BoxExtent;
	 double SphereRadius;
 };
