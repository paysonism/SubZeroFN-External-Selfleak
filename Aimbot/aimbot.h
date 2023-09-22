#pragma once
#include "definitons.h"

auto aimbot(float x, float y) -> void
{
    float CenterX = (ImGui::GetIO().DisplaySize.x / 2);
    float CenterY = (ImGui::GetIO().DisplaySize.y / 2);

    int Smoothness = smooth;


    float TargetX = 0.f;
    float TargetY = 0.f;

    if (x != 0.f)
    {
        if (x > CenterX)
        {
            TargetX = -(CenterX - x);
            TargetX /= Smoothness;
            if (TargetX + CenterX > CenterX * 2.f) TargetX = 0.f;
        }

        if (x < CenterX)
        {
            TargetX = x - CenterX;
            TargetX /= Smoothness;
            if (TargetX + CenterX < 0.f) TargetX = 0.f;
        }
    }

    if (y != 0.f)
    {
        if (y > CenterY)
        {
            TargetY = -(CenterY - y);
            TargetY /= Smoothness;
            if (TargetY + CenterY > CenterY * 2.f) TargetY = 0.f;
        }

        if (y < CenterY)
        {
            TargetY = y - CenterY;
            TargetY /= Smoothness;
            if (TargetY + CenterY < 0.f) TargetY = 0.f;
        }
    }

    mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

}

bool isVisible(uint64_t mesh)
{
	float bing = driver.read<float>(mesh + 0x360);
	float bong = driver.read<float>(mesh + 0x368);
	const float tick = 0.06f;
	return bong + tick >= bing;
}
