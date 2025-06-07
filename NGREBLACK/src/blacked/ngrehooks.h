#pragma once
#include <Windows.h>
#include <cstdint>
#include "globals.h"

struct HookInfo {
    DWORD_PTR offset;
    int length;
    void* hookFunction;
    const char* hookName;
    DWORD_PTR* returnAddress;
    int nopeLen;
};

extern "C" void InjectNinpoGauge( );
extern "C" void InjectSurgeGauge( );
extern "C" void InjectDmgMulp( );
extern "C" void InjectWepEquip( );
extern "C" void InjectWepEquip2( );
extern "C" void InjectInput( );
extern "C" void InjectStruggle( );
extern "C" void InjectAIDodge( );
extern "C" void InjectAnimation( );
extern "C" uint16_t SwapAnimations(uint16_t currentAnim, size_t size);
extern "C" uint16_t AttackCancel(uint16_t currentAnim, uint16_t currentInput, AttackCancels* attackCancelList);
size_t GetAttackCancelSize( );
extern "C" void InjectTrialNinpo( );

extern "C" void InjectAttackCancels( );

void ApplyHooks(HookInfo* hooks, int count, DWORD_PTR baseAddress);
bool Hook(void* hookAddress, void* myFunc, int len, int nopeLen = 0);
