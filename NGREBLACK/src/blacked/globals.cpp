#include "globals.h"


DWORD_PTR ngreBaseAddress = 0;
uintptr_t playerIdentAddress = 0x6034FE0;
uintptr_t playerIdentAddress2 = 0x6035DD0;
uintptr_t guiplayerActiveAnimation = 0;



int randNum = 0;

uintptr_t returnInjectNinpoGauge = 0;
uintptr_t returnInjectSurgeGauge = 0;
uintptr_t returnInjectDmgMulp = 0;

uintptr_t returnInjectAIDodge = 0;
uintptr_t returnInjectAIDodgeCallAddress = 0x1490240;
int aiDodgeChance = 0;

uintptr_t bloodyRageChimeSoundAddress = 0x1A92942;
uintptr_t ninpoGaugeRateJumpAddress = 0x1A1BF77;
uintptr_t ninpoGaugeRateCallAddress = 0x1979DF0;
uintptr_t surgeGaugeRateCallAddress = 0x1A1BDC0;
uintptr_t surgeGaugeRateJumpAddress = 0x18C153D;
const uintptr_t disableHpUIOffset = 0xCBFC64;
uintptr_t disableHPUIAddress = 0;
const BYTE nope5Bytes[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
const BYTE enableHPUIBytes[]{0xE8, 0x97, 0xF4, 0xFF, 0xFF};
const BYTE freeCameraEnableBytes[]{0xE8, 0x54, 0x3D, 0x04, 0x00};


float ninpoGaugeFillRate = 0.50f;
float cicadaSurgeNinpoCost = -5.00f;
float damageMulp = 1.10f;

const uintptr_t playerHPOffset = 0x6035D24;
uintptr_t playerHPAddress = 0;

const uintptr_t storyDifficultyOffset = 0x61F44D0;
uintptr_t storyDifficultyAddress;


const uintptr_t lowHPRedTintOffset = 0x17BB4BA;
uintptr_t lowHPRedTintAddress = 0;
bool disableLowHPRedTint = true;
bool disableHPUI = false;
bool disableBloodyRageChime = true;




uint16_t guiPlayerHP = 0;
Difficulty currentDifficulty = Difficulty::UNKNOWN;

int dsWeaponSelectedIndex = 0;

uintptr_t returnInjectWepEquip = 0;
uintptr_t jumpInjectWepEquip = 0x1FAB920; // 0x1BC1970;
uintptr_t returnInjectWepEquip2 = 0;
uintptr_t jumpInjectWepEquip2 = 0x1BC1970;

uintptr_t returnInjectInput = 0;
uintptr_t injectInputJEAddress = 0xB92EA7;
uintptr_t injectInputJMPAddress = 0xB92FA4;

uintptr_t struggleResetCheckAddress = 0x60351AA;
uintptr_t returnInjectStruggle = 0;
uint16_t previousButton = 0;
uint16_t playerInput = 0;

bool struggleStarted = false;
bool struggleSuccessFlag = false;
int triangleCount = 0;
int squareCount = 0;
bool enableStruggleSystem = false;

uintptr_t freeCamAddress = 0x147A3D7;
bool freeCameraEnable = false;

uintptr_t returnInjectAnim = 0;

const char* DifficultyToString(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::HERO:
            return "Hero";
        case Difficulty::NORMAL:
            return "Normal";
        case Difficulty::HARD:
            return "Hard";
        case Difficulty::MASTERNINJA:
            return "Master Ninja";
        case Difficulty::ULTIMATENINJA:
            return "Ultimate Ninja";
        default:
            return "Unknown";
    }
}

Difficulty GetStoryDifficulty(uint8_t difficultyValue) {

    switch (difficultyValue) {
        case 0:
            return Difficulty::HERO;
        case 1:
            return Difficulty::NORMAL;
        case 4:
            return Difficulty::ULTIMATENINJA;
        case 5:
        default:
            return Difficulty::UNKNOWN;
    }
}

const AnimationSwaps animSwaps[] = {
    //{0x05CF, 0x0693},
    {0x1746, 0x16E1},   
    {0x0759, 0x075F},
    {0x075C, 0x0762}
};
const size_t animSwapSize = sizeof(animSwaps) / sizeof(animSwaps[0]);

bool disableSobGlow = true;
uintptr_t sobGlowAddress = 0x1665C9B;

std::vector<AttackCancels> attackCancelList;
  


size_t attackCancelSize = attackCancelList.size( );

uintptr_t returnInjectAttackCancels = 0;
uintptr_t injectAttackCancelsJE = 0x146981C;

uintptr_t returnInjectTrialNinpo = 0;
bool replaceInfernoTrueInf = false;

bool disableEnemyAI = false;
uintptr_t disableEnemyAIAddress = 0x149EAAD;
