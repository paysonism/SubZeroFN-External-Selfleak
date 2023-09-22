#pragma once
#include "../AntiDebug/CallStack-Spoofer.h"


float DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;
	float y = 0.0f;
	int i = 0;

	ImU32 outlineColor = ImGui::GetColorU32(ImVec4(0, 0, 0, 255));

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
		ImVec2 textPos = pos;

		if (center)
		{
			textPos.x -= textSize.x * 0.5f;
		}

		// Draw outline
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if (j != 0 || k != 0)
				{
					ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(textPos.x + j, textPos.y + k), outlineColor, line.c_str());
				}
			}
		}

		// Draw the main text
		ImGui::GetOverlayDrawList()->AddText(pFont, size, textPos, color, line.c_str());

		y = pos.y + textSize.y * (i + 1);
		i++;
	}

	return y;
}


HWND get_process_wnd(uint32_t pid)
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bresult = EnumWindows([](HWND hwnd, LPARAM lparam) -> BOOL
		{
			auto pparams = (std::pair<HWND, uint32_t>*)(lparam);
			uint32_t processid = 0;
			if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processid)) && processid == pparams->second)
			{
				SetLastError((uint32_t)-1);
				pparams->first = hwnd;
				return FALSE;
			}
			return TRUE;
		}, (LPARAM)&params);
	if (!bresult && GetLastError() == -1 && params.first) return params.first;
	return 0;
}




static ImVec4 ConvertColorToImVec4(const RGBA* color)
{
	return ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f);
}


void DrawLine(int x1, int y1, int x2, int y2, const RGBA* color, int thickness)
{
	static ImVec2 p1;
	static ImVec2 p2;

	p1.x = static_cast<float>(x1);
	p1.y = static_cast<float>(y1);

	p2.x = static_cast<float>(x2);
	p2.y = static_cast<float>(y2);

	ImGui::GetOverlayDrawList()->AddLine(p1, p2, ImGui::ColorConvertFloat4ToU32(ConvertColorToImVec4(color)), thickness);
}




void DrawFilledRect(ImDrawList* drawList, const ImVec2& topLeft, const ImVec2& bottomRight, ImU32 color)
{
	drawList->AddRectFilled(topLeft, bottomRight, color);
}


void DrawNormalBox(ImDrawList* drawList, const ImVec2& topLeft, const ImVec2& bottomRight, int borderPx, ImU32 color)
{
	// Top border
	drawList->AddRectFilled(topLeft, ImVec2(bottomRight.x, topLeft.y + borderPx), color);

	// Bottom border
	drawList->AddRectFilled(ImVec2(topLeft.x, bottomRight.y - borderPx), bottomRight, color);

	// Left border (excluding corners)
	drawList->AddRectFilled(ImVec2(topLeft.x, topLeft.y + borderPx), ImVec2(topLeft.x + borderPx, bottomRight.y - borderPx), color);

	// Right border (excluding corners)
	drawList->AddRectFilled(ImVec2(bottomRight.x - borderPx, topLeft.y + borderPx), ImVec2(bottomRight.x, bottomRight.y - borderPx), color);
}


void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	SPOOF_FUNC;
	ImDrawList* drawList = ImGui::GetOverlayDrawList();
	ImU32 colorU32 = ImGui::GetColorU32(color);

	float lineW = static_cast<float>(W) / 3.0f;
	float lineH = static_cast<float>(H) / 3.0f;

	ImVec2 topLeft(X, Y);
	ImVec2 topRight(X + W, Y);
	ImVec2 bottomRight(X + W, Y + H);
	ImVec2 bottomLeft(X, Y + H);


	drawList->AddLine(topLeft, ImVec2(topLeft.x + lineW, topLeft.y), colorU32, thickness);
	drawList->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + lineH), colorU32, thickness);
	drawList->AddLine(topRight, ImVec2(topRight.x - lineW, topRight.y), colorU32, thickness);
	drawList->AddLine(topRight, ImVec2(topRight.x, topRight.y + lineH), colorU32, thickness);
	drawList->AddLine(bottomLeft, ImVec2(bottomLeft.x + lineW, bottomLeft.y), colorU32, thickness);
	drawList->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - lineH), colorU32, thickness);
	drawList->AddLine(bottomRight, ImVec2(bottomRight.x - lineW, bottomRight.y), colorU32, thickness);
	drawList->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - lineH), colorU32, thickness);
}



void DrawBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	SPOOF_FUNC;
	ImGui::GetOverlayDrawList()->AddRect(
		ImVec2(X, Y),
		ImVec2(X + W, Y + H),
		color,
		0.0f,
		ImDrawCornerFlags_All,
		thickness
	);
}


typedef struct _FNlEntity
{

	uint64_t Actor;
	int ID;
	uint64_t mesh;
}FNlEntity;

std::vector<FNlEntity> entityList;


struct HandleDisposer
{

	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;



std::wstring MBytesToWString(const char* lpcszString)
{
	SPOOF_FUNC;
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	SPOOF_FUNC;
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
void sleep_for_5_seconds() {
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* format, ...)
{
	SPOOF_FUNC;
	va_list args;
	va_start(args, format);

	char buffer[1024];
	vsnprintf_s(buffer, sizeof(buffer), format, args);

	va_end(args);

	std::string text = WStringToUTF8(MBytesToWString(buffer).c_str());

	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - static_cast<int>(textSize.x / 2);
		y = y - static_cast<int>(textSize.y / 2);
	}

	ImU32 textColor = ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f));

	if (stroke)
	{
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i != 0 || j != 0)
				{
					ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + i, y + j), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
				}
			}
		}
	}

	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), textColor, text.c_str());
}


std::string GetPlayerName(uintptr_t player_state)
{
	SPOOF_FUNC;
	int pNameLength; // rsi
	_WORD* pNameBufferPointer;
	int i; // ecx
	char v25; // al
	int v26; // er8
	int v29; // eax

	uintptr_t pNameStructure = driver.read<uintptr_t>(player_state + 0xAE8);//0xAE0
	pNameLength = driver.read<int>(pNameStructure + 0x10);
	if (pNameLength <= 0) return "";

	wchar_t* pNameBuffer = new wchar_t[pNameLength];
	uintptr_t pNameEncryptedBuffer = driver.read<uintptr_t>(pNameStructure + 0x8);

	driver.readm((PVOID)pNameEncryptedBuffer, pNameBuffer, pNameLength * sizeof(wchar_t));

	v25 = pNameLength - 1;
	v26 = 0;
	pNameBufferPointer = (_WORD*)pNameBuffer;

	for (i = (v25) & 3; ; *pNameBufferPointer++ += i & 7)
	{
		v29 = pNameLength - 1;
		if (!(_DWORD)pNameLength)
			v29 = 0;

		if (v26 >= v29)
			break;

		i += 3;
		++v26;
	}

	std::wstring temp_wstring(pNameBuffer);
	return std::string(temp_wstring.begin(), temp_wstring.end());
}


void ClearConsole()
{
	system("cls");
}





void RainbowText(const char* text, float hue) {
	SPOOF_FUNC;
	ImVec4 color = ImVec4(ImColor::HSV(hue, 1.0f, 1.0f));
	ImGui::TextColored(color, text);
}





inline bool is_visible(uintptr_t mesh) {
	SPOOF_FUNC;
	if (!mesh)
		return false;

	float last_sumbit_time = driver.read<float>(mesh + 0x360);
	float last_render_time_on_screen = driver.read<float>(mesh + 0x368);
	const float fVisionTick = 0.06f;
	bool visible = last_render_time_on_screen + fVisionTick >= last_sumbit_time;
	return visible;
}

using namespace std;

std::string random_string(std::string::size_type length)
{
	SPOOF_FUNC;
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#%^&*()";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s + ".exe";
}