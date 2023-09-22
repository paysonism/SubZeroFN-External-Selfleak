#pragma once
#include "../Main/description.h"
static void DrawESP();


static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static HWND Window = NULL;
IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;








static const char* combo_items1[5] = { "Mega City", "2", "3", "4", "5" };

void render() {
	SPOOF_FUNC;
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		ShowMenu = !ShowMenu;
	}
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	if (ShowMenu)
	{
		SPOOF_FUNC;
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();

		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(8.0f, 8.0f);
		style.WindowRounding = 3.0f;
		style.WindowBorderSize = 1.0f;
		style.WindowMinSize = ImVec2(32.0f, 32.0f);
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		style.ChildRounding = 3.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupRounding = 0.0f;
		style.PopupBorderSize = 1.0f;
		style.FramePadding = ImVec2(4.0f, 3.0f);
		style.FrameRounding = 3.0f;
		style.FrameBorderSize = 0.0f;
		style.ItemSpacing = ImVec2(8.0f, 4.0f);
		style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 6.0f;
		style.ScrollbarSize = 14.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize = 20.0f;
		style.GrabRounding = 1.0f;
		style.TabRounding = 4.0f;
		style.TabBorderSize = 0.0f;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

		style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.4000000059604645f, 0.407843142747879f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.98f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1568627506494522f, 0.239215686917305f, 0.2196078449487686f, 0.6000000238418579f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 1.0f, 0.6499999761581421f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4392156898975372f, 0.800000011920929f, 0.800000011920929f, 0.1800000071525574f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4392156898975372f, 0.800000011920929f, 0.800000011920929f, 0.2700000107288361f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4392156898975372f, 0.8078431487083435f, 0.8588235378265381f, 0.6600000262260437f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1372549086809158f, 0.1764705926179886f, 0.2078431397676468f, 0.7300000190734863f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.2700000107288361f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5400000214576721f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.2000000029802322f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2196078449487686f, 0.2862745225429535f, 0.2980392277240753f, 0.7099999785423279f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.0f, 1.0f, 1.0f, 0.4399999976158142f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.7400000095367432f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 1.0f, 0.6800000071525574f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.0f, 1.0f, 1.0f, 0.3600000143051147f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.7599999904632568f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.6470588445663452f, 0.6470588445663452f, 0.4600000083446503f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.007843137718737125f, 1.0f, 1.0f, 0.4300000071525574f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.6200000047683716f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 1.0f, 1.0f, 0.3300000131130219f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.4199999868869781f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.5400000214576721f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.4980392158031464f, 0.4980392158031464f, 0.3300000131130219f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0f, 0.4980392158031464f, 0.4980392158031464f, 0.4699999988079071f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.6980392336845398f, 0.6980392336845398f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 1.0f, 1.0f, 0.5400000214576721f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.7400000095367432f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f, 0.5764706134796143f, 0.8619999885559082f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 1.0f, 1.0f, 0.2199999988079071f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.03921568766236305f, 0.09803921729326248f, 0.08627451211214066f, 0.5099999904632568f);

		static int maintabs = 0;
		ImGui::SetNextWindowSize(ImVec2(600.0f, 500.0f), ImGuiCond_Once);

		if (ImGui::Begin(("SubZeroFN Private"), NULL, 34))
		{
			if (ImGui::BeginTabBar("TabBar"))
			{
				if (ImGui::BeginTabItem("Aimbot"))
				{
					ImGui::SetWindowSize(ImVec2(600.0f, 400.0f));
					ImGui::BeginChild("##AimbotChild", ImVec2(0, 0), true);

					ImGui::Checkbox("Enable", &Aimbot);
					if (Aimbot)
					{
						HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);

						ImGui::PushItemWidth(150);

						static const char* hitboxOptions[] = { "Head", "Chest", "Pelvis" };
						ImGui::Combo("Hitbox Position", &hitboxpos, hitboxOptions, IM_ARRAYSIZE(hitboxOptions));
						ImGui::Spacing();
						ImGui::Checkbox("Draw FOV", &enablefov);
						if (enablefov)
						{
							ImGui::Checkbox("Circle FOV", &fovcircle);
							if (fovcircle)
							{
								square_fov = false;
								fovcirclefilled = false;
							}

							ImGui::Checkbox("Filled Circle FOV", &fovcirclefilled);
							if (fovcirclefilled)
							{
								fovcircle = false;
								square_fov = false;
							}

							ImGui::Checkbox("Square FOV", &square_fov);
							if (square_fov)
							{
								fovcirclefilled = false;
								fovcircle = false;
							}

							ImGui::Spacing();

							ImGui::SliderInt("FOV Size", &AimFOV, 50, 300);
						}

						ImGui::SliderInt("Smoothing", &smooth, 1, 10);
					}

					ImGui::EndChild();
					ImGui::EndTabItem();
				}
			}

			if (ImGui::BeginTabItem("Visuals"))
			{
				static ImVec2 tabSize = ImVec2(600, 400); // Set the size for the Visuals tab
				ImGui::SetWindowSize(tabSize);

				ImGui::BeginChild("##VisualsChild", ImVec2(0, 0), true);

				ImGui::Checkbox("Enable ESP", &Esp);
				if (Esp)
				{
					ImGui::Checkbox("Weapon ESP [WORKS]", &weaponesp);
					ImGui::Checkbox("Name ESP [DOESNT WORK]", &playernames);
					ImGui::Checkbox("Ammo ESP [WORKS]", &ammoESP);
					ImGui::Checkbox("Enemy Alert [5m]", &EnemyAlert);

					ImGui::Checkbox("2D Box", &Esp_box);
					if (Esp_box)
					{
						Esp_box = true;
						ThreeDBoxEsp = false;
						cornerbox = false;

					}
					ImGui::SameLine();
					ImGui::Checkbox("Corner Box", &cornerbox);
					if (cornerbox)
					{
						Esp_box = false;
						ThreeDBoxEsp = false;
						cornerbox = true;

					}
					ImGui::SameLine();
					ImGui::Checkbox("3D Box", &ThreeDBoxEsp);
					if (ThreeDBoxEsp)
					{
						Esp_box = false;
						ThreeDBoxEsp = true;
						cornerbox = false;

					}

					ImGui::Checkbox("Distance ESP [WORKS]", &Esp_Distance);
					ImGui::Checkbox("Skeleton", &skeletonesp);
					ImGui::Checkbox("Snaplines", &Esp_line);

					const int MinVisDist = 18;
					const int MaxVisDist = 2500;
					ImGui::SliderInt("Distance", &VisDist, MinVisDist, MaxVisDist);
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}


			if (ImGui::BeginTabItem("Exploits"))
			{
				static ImVec2 tabSize = ImVec2(600, 400);
				ImGui::SetWindowSize(tabSize);

				ImGui::BeginChild("##ExtraChild", ImVec2(0, 0), true);

				ImGui::Checkbox("Player TP (LShift)", &test2);
				ImGui::Checkbox("No Recoil", &norecoil);

				ImGui::Combo("Locations", &Locations, combo_items1, IM_ARRAYSIZE(combo_items1));


				ImGui::EndChild();
				ImGui::EndTabItem();
			}


			if (ImGui::BeginTabItem("Misc"))
			{
				static ImVec2 tabSize = ImVec2(650, 680);

				ImGui::BeginChild("##InfoChild", ImVec2(0, 0), true);

				ImGui::Text("Framerate: %.1f", ImGui::GetIO().Framerate);
				ImGui::Spacing();
				ImGui::SliderInt("Thickness | ESP", &thickness, 1, 35);
				ImGui::SliderInt("Thickness | FOV", &thicknessa, 1, 35);
				ImGui::PushItemWidth(200);
				ImGui::Spacing();
				ImGui::ColorPicker3("Visible Color", fl_VisibleColor, ImGuiColorEditFlags_NoInputs);
				ImGui::ColorPicker3("Invisible Color", fl_InVisibleColor, ImGuiColorEditFlags_NoInputs);
				ImGui::PopItemWidth();

				ImGui::Spacing();

				if (rootAddress > 0)
				{
					ImGui::Text("Drivers Loaded: Yes");
				}
				else
				{
					ImGui::Text("Drivers Loaded: No");
				}
				ImGui::Spacing();
				if (ImGui::Button("Exit Cheat", ImVec2(75, 25)))
				{
					exit(0); 
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();

		}

		ImGui::End();
	}

	DrawESP();

	ImGui::EndFrame();

	if (D3dDevice->BeginScene() >= 0)
	{
		D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		D3dDevice->EndScene();

		HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			D3dDevice->Reset(&d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}

		static bool renderStatesSet = false;
		if (!renderStatesSet)
		{
			D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
			D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
			renderStatesSet = true;
		}
	}
}