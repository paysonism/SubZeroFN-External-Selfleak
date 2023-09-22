#include "../Main/offsets.h"
#include "../Other/Controller.h"





void PerformAiming(DWORD_PTR entity)
{
    uint64_t currentactormesh = driver.read<uint64_t>(entity + 0x318);

    // Early return if currentactormesh is invalid
    if (!currentactormesh)
    {
        return;
    }

    auto rootHead = GetBone(currentactormesh, hitbox);
    Vector3 rootHeadOut = w2s(rootHead);

    // Combine conditions and use early return
    if (rootHeadOut.x != 0 || rootHeadOut.y != 0)
    {
        aimbot(rootHeadOut.x, rootHeadOut.y);
    }
}




void DrawESP() {
    SPOOF_FUNC;
    const auto size = ImGui::GetIO().DisplaySize;
    const auto center = ImVec2(size.x / 2, size.y / 2);

    if (square_fov) {
        ImGui::GetOverlayDrawList()->AddRect(ImVec2(ScreenCenterX - AimFOV, ScreenCenterY - AimFOV),
            ImVec2(ScreenCenterX + AimFOV, ScreenCenterY + AimFOV),
            IM_COL32(255, 255, 255, 255), thicknessa);
    }

    if (fovcircle) {
        ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(AimFOV),
            ImColor(255, 255, 255, 255), 100.0f, thicknessa);
    }

    if (fovcirclefilled) {
        ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(AimFOV),
            ImColor(255, 255, 255, 255), 100.0f, thicknessa);

        ImGui::GetOverlayDrawList()->AddCircleFilled(center, AimFOV, ImColor(0, 0, 0, 110), 100);
    }







    switch (hitboxpos)
    {
    case 0:
        hitbox = 67; // neck
        break;
    case 2:
        hitbox = 36; // chest
        break;
    case 3:
        hitbox = 2;  // pelvis
        break;
    default:
       
        break;
    }

    
    cache::uworld = driver.read<uintptr_t>(rootAddress + UWORLD);
    cache::game_instance = driver.read<uintptr_t>(cache::uworld + GAME_INSTANCE);
    cache::local_players = driver.read<uintptr_t>(driver.read<uintptr_t>(cache::game_instance + LOCAL_PLAYERS));
    cache::player_controller = driver.read<uintptr_t>(cache::local_players + PLAYER_CONTROLLER);
    cache::local_pawn = driver.read<uintptr_t>(cache::player_controller + LOCAL_PAWN);

    
    if (cache::local_pawn != 0) {
        
        cache::root_component = driver.read<uintptr_t>(cache::local_pawn + ROOT_COMPONENT);
        cache::relative_location = driver.read<Vector3>(cache::root_component + RELATIVE_LOCATION);
        cache::player_state = driver.read<uintptr_t>(cache::local_pawn + PLAYER_STATE);
        cache::my_team_id = driver.read<int>(cache::player_state + TEAM_INDEX);
    }

    
    cache::game_state = driver.read<uintptr_t>(cache::uworld + GAME_STATE);
    cache::player_array = driver.read<uintptr_t>(cache::game_state + PLAYER_ARRAY);
    cache::player_count = driver.read<int>(cache::game_state + (PLAYER_ARRAY + sizeof(uintptr_t)));
    cache::closest_distance = FLT_MAX;

    
    for (uint32_t i = 0; i < cache::player_count; i++) {
        player_state = driver.read<uintptr_t>(cache::player_array + (i * sizeof(uintptr_t)));

        
        if (!player_state) continue;
        int player_team_id = driver.read<int>(player_state + TEAM_INDEX);
        if (player_team_id == cache::my_team_id) continue;

        
        uintptr_t pawn_private = driver.read<uintptr_t>(player_state + PAWN_PRIVATE);

        
        if (!pawn_private) continue;
        if (pawn_private == cache::local_pawn) continue;

        
        uintptr_t mesh = driver.read<uintptr_t>(pawn_private + MESH);
        if (!mesh) continue;
        Vector3 head3d = GetBone(mesh, 67);
        Vector3 head2d = w2s(head3d);
        Vector3 bottom3d = GetBone(mesh, 0);
        Vector3 bottom2d = w2s(bottom3d);
        Vector3 w2shead = w2s(head3d);
        float box_height = abs(head2d.y - bottom2d.y);
        float box_width = box_height * 0.50f;
        float distance = cache::relative_location.distance(bottom3d) / 100;


        if (distance < VisDist) {
            {

                if (Esp)
                {
                    SPOOF_FUNC;
                    static ImColor visible_color;
                    if (is_visible(mesh)) {
                        visible_color = ImGui::GetColorU32({ fl_VisibleColor[0], fl_VisibleColor[1], fl_VisibleColor[2],  1.0f }); // Green for visible
                    }
                    else {
                        visible_color = ImGui::GetColorU32({ fl_InVisibleColor[0], fl_InVisibleColor[1], fl_InVisibleColor[2],  1.0f }); // Red for non-visible
                    }
                    

                    if (weaponesp)
                    {
                        SPOOF_FUNC;
                        auto current_weapon = driver.read<uintptr_t>(pawn_private + 0x948); //SDKGlobalData->ThreadInfoPlayer[i].Actor

                        auto mycurrent_weapon = driver.read<uintptr_t>(LocalPawn + 0x948);
                        auto myis_reloading = driver.read<bool>(mycurrent_weapon + 0x358);

                        auto is_reloading = driver.read<bool>(current_weapon + 0x358);


                        auto ammocount = driver.read<INT32>(current_weapon + 0xd08);
                        std::string s_name22 = ("Invalid");
                        std::string s_name = ("Invalid");
                        std::string mys_name = ("Invalid");
                        uintptr_t weapon_data = driver.read<uintptr_t>(current_weapon + 0x450); //UFortWeaponItemDefinition*

                        uintptr_t display_name = driver.read<uintptr_t>(weapon_data + 0x98); // DisplayName (FText)

                        uint32_t weapon_lenght = driver.read<uint32_t>(display_name + 0x40); // FText -> Length


                        wchar_t* buffer = new wchar_t[weapon_lenght + 1];
                        driver.readm((PVOID)driver.read<PVOID>(display_name + 0x38), buffer, weapon_lenght * sizeof(wchar_t));
                        std::wstring w_name(buffer);

                        s_name = std::string(w_name.begin(), w_name.end());
                        delete[] buffer;

                        auto s_namesz = ImGui::CalcTextSize(s_name.c_str());
                        uintptr_t myweapon_data = driver.read<uintptr_t>(mycurrent_weapon + 0x450); //UFortWeaponItemDefinition*

                        uintptr_t mydisplay_name = driver.read<uintptr_t>(myweapon_data + 0x98); // DisplayName (FText)

                        uint32_t myweapon_lenght = driver.read<uint32_t>(mydisplay_name + 0x40); // FText -> Length

                        wchar_t* myname = new wchar_t[uintptr_t(myweapon_lenght) + 1];
                        driver.readm((PVOID)driver.read<PVOID>(mydisplay_name + 0x38), myname, myweapon_lenght * sizeof(wchar_t)); // FText -> Name

                        DrawString(12, bottom2d.x, bottom2d.y - 50, &Col.white, true, true, s_name.c_str());

                        std::wstring myw_name(myname);
                        mys_name = std::string(myw_name.begin(), myw_name.end());
                        delete[] myname;
                    }


                    if (crosshairEnabled) {

                        SPOOF_FUNC;

                    }
                    //if (playernames) { names(head2d, distance, ImColor(250, 250, 250, 250)); }

                    if (playernames)
                    {
                        std::string namedecrypted = GetPlayerName(player_state);
                        //DrawString(15, Headbox.X, Headbox.Y - 15, &Col.white, true, true, namedecrypted.c_str());

                        ImVec2 TextSize = ImGui::CalcTextSize(namedecrypted.c_str());
                        DrawString(18, (head2d.x) - (TextSize.x / 2), (head2d.y - 15), &Col.white, false, true, namedecrypted.c_str());
                    }



                    if (Esp_box) {
                        SPOOF_FUNC;

                        // Precompute box position if it's constant
                        const float boxX = head2d.x - (box_width / 2);

                        // Precompute box height and width if they are constant
                        const float boxWidth = box_width;
                        const float boxHeight = box_height;

                        // Cache the result of isVisible to avoid redundant work
                        bool isActorVisible = isVisible(mesh);

                        // Use a single DrawBox call for all visible boxes (batching)
                            const ImU32 boxColor = visible_color;
                            DrawBox(boxX, head2d.y, boxWidth, boxHeight, boxColor, thickness);
                        
                    }

                    if (ammoESP)
                    {
                        SPOOF_FUNC;
                        auto current_weapon = driver.read<uintptr_t>(pawn_private + 0x948); // by FG (blu)

                        auto ammocount = driver.read<INT32>(current_weapon + 0xd08);
                        char buffer[128];
                        sprintf_s(buffer, "[%i]", ammocount);

                        if (buffer != "?")
                        {
                            ImVec2 DistanceTextSize = ImGui::CalcTextSize(buffer);
                            DrawString(12, bottom2d.x - DistanceTextSize.x / 2, bottom2d.y + DistanceTextSize.y / 2 + 20, &Col.darkgreens, false, false, buffer);
                        }
                    }

                    if (norecoil) {
                        driver.write<float>(PlayerController + 0x64, -1);
                    }

                    Vector3 vHeadBone = GetBone(mesh, 68);
                    Vector3 vRootBone = GetBone(mesh, 0);
                    Vector3 vHeadBoneOut = w2s(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15));
                    Vector3 bone66 = GetBone(mesh, 66);
                    Vector3 top = w2s(bone66);
                    Vector3 bone0 = GetBone(mesh, 0);
                    Vector3 bottom = w2s(bone0);
                    Vector3 Headbox = w2s(Vector3(head2d.x, head2d.y, +15));

                    if (ThreeDBoxEsp)
                    {
                        if (vHeadBoneOut.x != 0 || vHeadBoneOut.y != 0 || vHeadBoneOut.z != 0)
                        {
                            ImU32 ESPSkeleton;
                            if (isVisible(mesh))
                            {
                                ESPSkeleton = ImColor(3, 3, 3);
                            }
                            else if (isVisible(mesh))
                            {
                                ESPSkeleton = ImColor(3, 0, 0);
                            }
                            Vector3 bottom1 = w2s(Vector3(vRootBone.x + 40, vRootBone.y - 40, vRootBone.z));
                            Vector3 bottom2 = w2s(Vector3(vRootBone.x - 40, vRootBone.y - 40, vRootBone.z));
                            Vector3 bottom3 = w2s(Vector3(vRootBone.x - 40, vRootBone.y + 40, vRootBone.z));
                            Vector3 bottom4 = w2s(Vector3(vRootBone.x + 40, vRootBone.y + 40, vRootBone.z));
                            Vector3 top1 = w2s(Vector3(vHeadBone.x + 40, vHeadBone.y - 40, vHeadBone.z + 15));
                            Vector3 top2 = w2s(Vector3(vHeadBone.x - 40, vHeadBone.y - 40, vHeadBone.z + 15));
                            Vector3 top3 = w2s(Vector3(vHeadBone.x - 40, vHeadBone.y + 40, vHeadBone.z + 15));
                            Vector3 top4 = w2s(Vector3(vHeadBone.x + 40, vHeadBone.y + 40, vHeadBone.z + 15));
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ESPSkeleton, 0.1f);
                            ImGui::GetOverlayDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ESPSkeleton, 0.1f);
                        }
                    }

                    if (skeletonesp)
                    {
                        SPOOF_FUNC;
                        Vector3 vHeadBone, vHip, vNeck, vUpperArmLeft, vUpperArmRight, vLeftHand, vRightHand,
                            vLeftHand1, vRightHand1, vRightThigh, vLeftThigh, vRightCalf, vLeftCalf,
                            vLeftFoot, vRightFoot, vPelvisOut;

                        vHeadBone = GetBone(mesh, 68);
                        vHip = GetBone(mesh, 2);
                        vNeck = GetBone(mesh, 67);
                        vUpperArmLeft = GetBone(mesh, 9);
                        vUpperArmRight = GetBone(mesh, 38);
                        vLeftHand = GetBone(mesh, 10);
                        vRightHand = GetBone(mesh, 39);
                        vLeftHand1 = GetBone(mesh, 30);
                        vRightHand1 = GetBone(mesh, 59);
                        vRightThigh = GetBone(mesh, 78);
                        vLeftThigh = GetBone(mesh, 71);
                        vRightCalf = GetBone(mesh, 79);
                        vLeftCalf = GetBone(mesh, 72);
                        vLeftFoot = GetBone(mesh, 73);
                        vRightFoot = GetBone(mesh, 80);
                        vPelvisOut = GetBone(mesh, 8);

                        Vector3 vHeadBoneOut = w2s(vHeadBone);
                        Vector3 vPelvis = w2s(vPelvisOut);
                        Vector3 vHipOut = w2s(vHip);
                        Vector3 vNeckOut = w2s(vNeck);
                        Vector3 vUpperArmLeftOut = w2s(vUpperArmLeft);
                        Vector3 vUpperArmRightOut = w2s(vUpperArmRight);
                        Vector3 vLeftHandOut = w2s(vLeftHand);
                        Vector3 vRightHandOut = w2s(vRightHand);
                        Vector3 vLeftHandOut1 = w2s(vLeftHand1);
                        Vector3 vRightHandOut1 = w2s(vRightHand1);
                        Vector3 vRightThighOut = w2s(vRightThigh);
                        Vector3 vLeftThighOut = w2s(vLeftThigh);
                        Vector3 vRightCalfOut = w2s(vRightCalf);
                        Vector3 vLeftCalfOut = w2s(vLeftCalf);
                        Vector3 vLeftFootOut = w2s(vLeftFoot);
                        Vector3 vRightFootOut = w2s(vRightFoot);

                        DrawLine(vHeadBoneOut.x, vHeadBoneOut.y, vNeckOut.x, vNeckOut.y, &Col.black, thickness);
                        DrawLine(vHipOut.x, vHipOut.y, vNeckOut.x, vNeckOut.y, &Col.black, thickness);
                        DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.black, thickness);
                        DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.black, thickness);
                        DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.black, thickness);
                        DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.black, thickness);
                        DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, &Col.black, thickness);
                        DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, &Col.black, thickness);
                        DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, &Col.black, thickness);
                        DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, &Col.black, thickness);
                        DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.black, thickness);
                        DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.black, thickness);
                        DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.black, thickness);
                        DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.black, thickness);
                    }



                    if (fillbox) {
                        SPOOF_FUNC;
                        // Adjust the coordinates and dimensions as needed
                        DrawFilledRect(ImGui::GetOverlayDrawList(), ImVec2(Headbox.x - (box_width / 2), Headbox.y), ImVec2(Headbox.x + (box_width / 2), Headbox.y + box_height), visible_color);
                    }





                    if (cornerbox && isVisible(mesh)) {
                        SPOOF_FUNC;
                        DrawCorneredBox(head2d.x - (box_width / 2), head2d.y, box_width, box_height, visible_color, thickness);
                    }
                    if (Esp_Distance)
                    {
                        SPOOF_FUNC;
                        if (isVisible(mesh)) {
                            XorS(dst, "[%.fm]\n");
                            char dist[64];
                            sprintf_s(dist, dst.decrypt(), distance);
                            DrawOutlinedText(m_pFont, dist, ImVec2(head2d.x, head2d.y - 35), 16.0f, visible_color, true);
                        }
                        if (!isVisible(mesh)) {
                            XorS(dst, "[%.fm]\n");
                            char dist[64];
                            sprintf_s(dist, dst.decrypt(), distance);
                            DrawOutlinedText(m_pFont, dist, ImVec2(head2d.x, head2d.y - 35), 16.0f, visible_color, true);
                        }
                    }

                    if (Esp_line)
                    {
                        SPOOF_FUNC;
                        DrawLine(Width / 2, Height, bottom.x, bottom.y, &Col.black, 2.0);

                    }
                    if (sdesp) {
                        if (isVisible) {
                            SPOOF_FUNC;
                            // Draw the box with one color when isVisible is true
                            DrawNormalBox(ImGui::GetOverlayDrawList(), ImVec2(Headbox.x - (box_width / 2), Headbox.y), ImVec2(Headbox.x + (box_height / 2), Headbox.y + box_height), 2, visible_color);
                        }
                        else {
                            SPOOF_FUNC;
                            // Draw the box with another color when isVisible is false
                            DrawNormalBox(ImGui::GetOverlayDrawList(), ImVec2(Headbox.x - (box_width / 2), Headbox.y), ImVec2(Headbox.x + (box_width / 2), Headbox.y + box_height), 2, visible_color);
                        }
                    }
                }
                if (WindowStreamProof) {
                    SPOOF_FUNC;
                    SetWindowDisplayAffinity(Window, WDA_EXCLUDEFROMCAPTURE);
                }
                if (!WindowStreamProof) {
                    SPOOF_FUNC;
                    SetWindowDisplayAffinity(Window, !WDA_EXCLUDEFROMCAPTURE);
                }

            }
            auto dx = w2shead.x - (Width / 2);
            auto dy = w2shead.y - (Height / 2);
            auto dist = sqrtf(dx * dx + dy * dy);
            if (!isVisible(mesh)) {

                if (dist < AimFOV && dist < cache::closest_distance) {
                    cache::closest_distance = dist;
                    cache::closest_mesh = pawn_private;



                }
            }

            else
            {
                if (isVisible(mesh)) {

                    if (dist < AimFOV && dist < cache::closest_distance) {
                        cache::closest_distance = dist;
                        cache::closest_mesh = pawn_private;

                    }
                }
            }

        }










    }
    if (Aimbot)
    {
        if (Aimbot && cache::closest_mesh && (GetAsyncKeyState(hotkeys::aimkey) < 0 || Controller::IsPressingLeftTrigger())) {
            PerformAiming(cache::closest_mesh);
        }
    }
    Sleep(0.2);
}