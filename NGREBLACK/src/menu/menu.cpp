#include "menu.hpp"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_win32.h"
#include "../blacked/globals.h"
#include "../utils/SimpleIni.h"


namespace ig = ImGui;

namespace Menu {

    void InitializeContext(HWND hwnd) {
        if (ig::GetCurrentContext( ))
            return;

        ImGui::CreateContext( );
        ImGui_ImplWin32_Init(hwnd);

        ImGuiIO& io = ImGui::GetIO( );
        io.IniFilename = io.LogFilename = nullptr;
    }

    void Render( ) {
        if (!bShowMenu) {
            ShowCursor(FALSE);
            return;
        }
    


        ClipCursor(NULL); 
        ShowCursor(TRUE);


        ImGuiStyle& style = ImGui::GetStyle( );
        style.WindowRounding = 4.0f;
        style.FrameRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.95f); // Dark almost black
        colors[ImGuiCol_TitleBg] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_Tab] = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_TabActive] = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.2f, 0.0f, 0.0f, 0.7f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);

        ImGui::Begin("FB NGRE #000000", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        if (ImGui::BeginTabBar("MainTabs")) {
            if (ImGui::BeginTabItem("Mods")) {
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Rate Ninpo Gauge Increases");
                ImGui::DragFloat("Rate Ninpo Gauge Increases", &ninpoGaugeFillRate, 0.01f, 0.00f, 200.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Cicada Surge Ninpo Cost");
                ImGui::DragFloat("Cicada Surge Ninpo Cost", &cicadaSurgeNinpoCost, 0.01f, -200.0f, 200.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Damage Multiplier");
                ImGui::DragFloat("Damage Multiplier", &damageMulp, 0.01f, -100.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

                /*ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Struggle System");
                ImGui::Checkbox("Press Triangle (PS) Y (XBX) / L1 (PS) LB (XBX) one after another during SoB", &enableStruggleSystem);
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "THIS WILL ALSO ONLY ALLOW 1 SOB CHAIN AND WILL INCREASE THE DIFFICULTY QUITE A BIT. (!) NOT RECOMMENDED FOR THE */

                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Change Katana");
                const char* dsWeaponOptions[] = {"Default", "DS", "TDS", "JINRAN-MARU", "BLADE OF ARCHFIEND", "BLADE OF ARCHFIEND (SPARK)"};
                ImGui::Combo("Select Default or DS if you lose Dragon Sword", &dsWeaponSelectedIndex, dsWeaponOptions, IM_ARRAYSIZE(dsWeaponOptions));
        
                  ImGui::Separator( );

                ImGui::Text("WARNING: this optional system is only recommended if you're highly skilled in the game otherwise this may make your play session miserable!!");
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Struggle System");
                ImGui::BulletText("SoB chaining will be disabled");
                ImGui::BulletText("SoB glow will be forced off and selection under UIEffects will be ignored");
                ImGui::BulletText("Press Triangle (PS) Y (XBX) / L1 (PS) LB (XBX) sequentially during a SoB");
                ImGui::Checkbox("Struggle System", &enableStruggleSystem);
                
                   
                

                ImGui::EndTabItem( );
            }
            if (ImGui::BeginTabItem("Ninja Trials")) {
                ImGui::Checkbox("Replace Inferno with True Inferno", &replaceInfernoTrueInf);

                ImGui::EndTabItem( );
            }

            if (ImGui::BeginTabItem("UI & Effects")) {
                ImGui::Checkbox("Disable Low HP Red Tint", &disableLowHPRedTint);
                ImGui::Checkbox("Hide HP Hud (disabling while in-level requires dying / reloading into level)", &disableHPUI);
                ImGui::Checkbox("Disable Bloody Rage Chime", &disableBloodyRageChime);
                ImGui::Checkbox("Free Camera During Action Events (Will Lose R1 Camera Focus)", &freeCameraEnable);
                ImGui::Checkbox("Disable SoB Red Warning Glow", &disableSobGlow);
                ImGui::EndTabItem( );
            }
            if (ImGui::BeginTabItem("Enemy A.I")) {
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Enemy Evade Chance (NOT BLOCK)");
                ImGui::DragInt("Keep at 0 to disable and use game default logic (HIGHER VALUE = LESS CHANCE TO EVADE)", &aiDodgeChance, 1, 0, 100, "%d", ImGuiSliderFlags_AlwaysClamp);


               // ImGui::Checkbox("Disable AI", &disableEnemyAI);
                ImGui::EndTabItem( );
            }
            if (ImGui::BeginTabItem("Debug")) {
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Player HP: %d", guiPlayerHP);
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Animation ID: 0x%08X", guiplayerActiveAnimation);
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Player Ident Address 1: 0x%08X", playerIdentAddress);
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Player Ident Address 2: 0x%08X", playerIdentAddress2);
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Difficulty (Story): %s", DifficultyToString(currentDifficulty));
                ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "Player Controller Input Pressed ID: 0x%08X", playerInput);

                ImGui::Separator( );

                ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.2f, 1.0f), "Struggle System Enabled: %s", enableStruggleSystem ? "Yes" : "No");
                ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.2f, 1.0f), "Struggle Started: %s", struggleStarted ? "Yes" : "No");
                ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.2f, 1.0f), "Struggle Success: %s", struggleSuccessFlag ? "Yes" : "No");
                ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.2f, 1.0f), "Triangle Presses: %d", triangleCount);
                ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.2f, 1.0f), "L1 Presses: %d", squareCount);

               

                ImGui::EndTabItem( );
            }
            if (ImGui::BeginTabItem("Custom Move Legend")) {

                ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.2f, 1.0f), "Custom Move List");

                ImGui::Separator( );

                ImGui::Text("Legend:");
                ImGui::BulletText("-> = Forward");
                ImGui::BulletText("T  = Heavy");
                ImGui::BulletText("S  = Light");
                ImGui::BulletText("O  = Shuriken");
                ImGui::BulletText("L1 = Block");
                ImGui::BulletText("L2 = Left Trigger");
                ImGui::BulletText("DS  = Dragonsword");
                ImGui::BulletText("BOTA  = Dual Swords");
                ImGui::BulletText("SCY = Scythe");
                ImGui::BulletText("LNR = Lunar");
                ImGui::BulletText("KG = Kusarigama");
                ImGui::BulletText("Claw = Falcon Talons...lol");

                ImGui::EndTabItem( );
            }
            static uint16_t newOldAnim = 0;
            static uint16_t newNewAnim = 0;
            static uint16_t newInput = 0;
            static char newDesc[128] = "";

      
           if (ImGui::BeginTabItem("Custom Move List")) {
                ImGui::Text("Current Attack Cancels (%zu):", attackCancelList.size( ));
                ImGui::Separator( );

                
                ImGui::BeginChild("MoveListScroll", ImVec2(0, 400), true);

                for (size_t i = 0; i < attackCancelList.size( ); ++i) {
                    const auto& entry = attackCancelList[i];
                    ImGui::Text("Index: %zu", i);
                    ImGui::BulletText("0x%04X -> 0x%04X | Input: 0x%04X", entry.oldAnim, entry.newAnim, entry.input);
                    ImGui::TextWrapped("Description: %s", entry.attackCancelName);
                    ImGui::Separator( );
                }

                ImGui::EndChild( ); 
                ImGui::EndTabItem( );
            }

           
            if (ImGui::BeginTabItem("Custom Move Creator")) {
                ImGui::InputScalar("Old Animation ID", ImGuiDataType_U16, &newOldAnim, nullptr, nullptr, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
                ImGui::InputScalar("New Animation ID", ImGuiDataType_U16, &newNewAnim, nullptr, nullptr, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
                ImGui::InputScalar("Input ID", ImGuiDataType_U16, &newInput, nullptr, nullptr, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
                ImGui::InputText("Description", newDesc, IM_ARRAYSIZE(newDesc));

                ImGui::Separator( );
                ImGui::Spacing( );
                ImGui::TextColored(ImVec4(0.1f, 1.0f, 0.1f, 1.0f), "Animation ID: 0x%08X", guiplayerActiveAnimation);
                ImGui::TextColored(ImVec4(0.1f, 1.0f, 0.1f, 1.0f), "Current Input ID: 0x%08X", playerInput);
                ImGui::Separator( );
                ImGui::Spacing( );

                ImGui::Text("HELP (EN)");
                ImGui::BulletText("Perform the original move to capture its Animation ID -> enter it as Old Animation ID.");
                ImGui::BulletText("Perform the desired cancel move -> enter its Animation ID as New Animation ID.");
                ImGui::BulletText("Press the input you want to use -> its ID will appear above → enter it as Input ID.");
                ImGui::BulletText("Each Description must be unique.");
                ImGui::BulletText("YOU DO NOT NEED TO PRESS THE CANCEL INPUT RIGHT AWAY. IT CAN BE INPUT AT ANY POINT DURING THE ANIMATION I.E KG RUN Y YOU CAN WAIT UNTIL YOU HIT AN ENEMY BEFORE PRESSING S");
                ImGui::BulletText("VIDEO: https://www.youtube.com/watch?v=d3gNLnlATbI ");

             



                if (ImGui::Button("Add Attack Cancel")) {
                    if (strlen(newDesc) > 0) {
                        char* descCopy = _strdup(newDesc); 
                        attackCancelList.push_back({newOldAnim, newNewAnim, newInput, descCopy});
                        SaveConfig( ); 

                      
                        newOldAnim = newNewAnim = newInput = 0;
                        newDesc[0] = '\0';
                    }
                }

                ImGui::SameLine( );
                if (ImGui::Button("Refresh List from Config")) {
                    LoadConfig( ); 
                }

                ImGui::EndTabItem( );
            }

            ImGui::EndTabBar( );
        }

        ImGui::End( );
    }
    
}
