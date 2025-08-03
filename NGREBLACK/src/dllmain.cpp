

#include <Windows.h>
#include <iostream>
#include <thread>
#include <sstream>

#include "console/console.hpp"

#include "hooks/hooks.hpp"
#include "utils/utils.hpp"
#include "utils/SimpleIni.h"

#include "dependencies/minhook/MinHook.h"
#include "blacked/globals.h"
#include "blacked/ngre.h"
#include <random>
#include <tchar.h>




DWORD WINAPI OnProcessAttach(LPVOID lpParam);
DWORD WINAPI OnProcessDetach(LPVOID lpParam);
DWORD WINAPI OnProcessAttachModLogic(LPVOID lpParam);

bool runModLogic = true;









void WriteByte(DWORD_PTR address, BYTE value) {
    DWORD oldProtect;
    VirtualProtect((void*)address, sizeof(BYTE), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(BYTE*)address = value;
    VirtualProtect((void*)address, sizeof(BYTE), oldProtect, &oldProtect);
}
void WriteBytes(DWORD_PTR address, const void* data, size_t size) {
    DWORD oldProtect;
    VirtualProtect((void*)address, sizeof(size), PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy((void*)address, data, size);
    VirtualProtect((void*)address, size, oldProtect, &oldProtect);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    if (fdwReason == DLL_PROCESS_ATTACH) {


    
        DisableThreadLibraryCalls(hinstDLL);

        U::SetRenderingBackend(DIRECTX9);



        CreateThread(NULL, 0, OnProcessAttachModLogic, hinstDLL, 0, NULL);
        HANDLE hHandle = CreateThread(NULL, 0, OnProcessAttach, hinstDLL, 0, NULL);
        
        
        if (hHandle != NULL) {
            CloseHandle(hHandle);
        }
    } else if (fdwReason == DLL_PROCESS_DETACH && !lpReserved) {
        OnProcessDetach(NULL);
    }



    return TRUE;
}

DWORD_PTR GetBaseAddress(LPCWSTR module) {
    return (DWORD_PTR)GetModuleHandleW(module);
}

DWORD WINAPI OnProcessAttachModLogic(LPVOID lpParam) {

    
    ngreBaseAddress = (DWORD_PTR)GetModuleHandleW(L"Ninja Gaiden 3 Razor's Edge.exe");
    if (ngreBaseAddress <= 0) {return 0;}
    Ngre ngre(ngreBaseAddress);
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist(1, 100);
    rng.seed(std::chrono::steady_clock::now( ).time_since_epoch( ).count( ));
    LoadConfig( );

    while (runModLogic) {
        randNum = dist(rng);
        if (GetAsyncKeyState(VK_F11) & 1) {
            
        }
        guiPlayerHP = *(uint16_t*)playerHPAddress;
        guiplayerActiveAnimation = *(uint16_t*)(playerIdentAddress + 0x01C4);
        currentDifficulty = GetStoryDifficulty(*(uint8_t*)storyDifficultyAddress);

        if (disableLowHPRedTint) {
            WriteByte(lowHPRedTintAddress, 0xEB);
        } else {
            WriteByte(lowHPRedTintAddress, 0x74);

        }
        if (disableHPUI) {
            WriteBytes(disableHPUIAddress, nope5Bytes, 5);
        } else {
            WriteBytes(disableHPUIAddress, enableHPUIBytes, 5);
        }
        if (disableBloodyRageChime) {
            WriteByte(bloodyRageChimeSoundAddress, 0x02);
        } else {
            WriteByte(bloodyRageChimeSoundAddress, 0x01);
        }
        if (freeCameraEnable) {
            WriteBytes(freeCamAddress, nope5Bytes, 5);
        } else {
            WriteBytes(freeCamAddress, freeCameraEnableBytes, 5);
        }
        if (disableSobGlow || enableStruggleSystem) {
            WriteByte(sobGlowAddress, 0x00);
        } else {
            WriteByte(sobGlowAddress, 0x01);
        }
        if (ryuEnableVeinyArmEffect) {
            WriteByte(ryuVeinyArmEffectAddress, 0xEB);
        } else {
            WriteByte(ryuVeinyArmEffectAddress, 0x74);
        }
        if (disableModelRender) {
            WriteBytes(disableModelRenderAddress, disableRenderBytes, 5);
        } else {
            WriteBytes(disableModelRenderAddress, disableRenderBytesRestore, 5);
        }
        



       /* if (disableEnemyAI) {
            WriteByte(disableEnemyAIAddress, 0xEB);

        } else {
            WriteByte(disableEnemyAIAddress, 0x75);
        }*/
     

        Sleep(10);
    }
    return 0;
}





DWORD WINAPI OnProcessAttach(LPVOID lpParam) {


    Console::Alloc( );
    LOG("[+] Rendering backend: %s\n", U::RenderingBackendToStr( ));
    if (U::GetRenderingBackend( ) == NONE) {
        LOG("[!] Looks like you forgot to set a backend. Will unload after pressing enter...");
        std::cin.get( );

        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(lpParam), 0);
        return 0;
    }
    
    MH_Initialize( );
    H::Init( );
    //DWORD_PTR ngreBaseAddress2 = (DWORD_PTR)GetModuleHandleW(L"Ninja Gaiden 3 Razor's Edge.exe");
    //// CREDITS TIANMUXIA
    //uint8_t g_hexNg23CheckDllOrg[] = {
    //    0x48, 0x8B, 0xC4, 0x48, 0x89, 0x48, 0x08, 0x56, 0x57, 0x41, 0x56, 0x48, 0x81, 0xEC, 0x80, 0x00,
    //    0x00, 0x00, 0x48, 0xC7, 0x40, 0x98, 0xFE, 0xFF, 0xFF, 0xFF, 0x48, 0x89, 0x58, 0x18, 0x48, 0x89,
    //    0x68, 0x20, 0x45, 0x33, 0xC0, 0x48, 0x8D, 0x50, 0xB0};
    //uint8_t g_hexNg23CheckDllHack[] = {
    //    0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3, 0x90 // mov rax, 0x01; ret;
    //};

    //uintptr_t dllByPassAddress = ngreBaseAddress2 + 0xB857B0;

    //DWORD oldProtect;
    //VirtualProtect((LPVOID)dllByPassAddress, sizeof(g_hexNg23CheckDllOrg), PAGE_EXECUTE_READWRITE, &oldProtect);
    //memcpy((void*)dllByPassAddress, g_hexNg23CheckDllOrg, sizeof(g_hexNg23CheckDllOrg));
    //VirtualProtect((LPVOID)dllByPassAddress, sizeof(g_hexNg23CheckDllOrg), oldProtect, &oldProtect);
    

    return 0;
}

DWORD WINAPI OnProcessDetach(LPVOID lpParam) {
    runModLogic = false;


    H::Free( );
    MH_Uninitialize( );

    Console::Free( );

    

    return 0;
}
