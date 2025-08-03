#pragma once
#include <cstdint>
#include <string>
#include <basetsd.h>
#include <wtypes.h>
#include <string>
#include <vector>

enum Difficulty {
    HERO,
    NORMAL,
    HARD,
    MASTERNINJA,
    ULTIMATENINJA,
    UNKNOWN

};

extern "C" int randNum;

extern "C" DWORD_PTR ngreBaseAddress;
extern "C" uintptr_t playerIdentAddress;
extern "C" uintptr_t playerIdentAddress2;
extern "C" uintptr_t ninpoGaugeRateJumpAddress;
extern "C" uintptr_t ninpoGaugeRateCallAddress;

extern "C" uintptr_t surgeGaugeRateCallAddress;
extern "C" uintptr_t surgeGaugeRateJumpAddress;

extern const char* DifficultyToString(Difficulty difficulty);
extern Difficulty GetStoryDifficulty(uint8_t difficultyValue);

extern "C" float ninpoGaugeFillRate;
extern "C" float cicadaSurgeNinpoCost;
extern "C" float damageMulp;


extern const uintptr_t playerHPOffset;
extern uintptr_t playerHPAddress;

extern const uintptr_t storyDifficultyOffset;
extern uintptr_t storyDifficultyAddress;

extern const uintptr_t lowHPRedTintOffset;
extern uintptr_t lowHPRedTintAddress;
extern bool disableLowHPRedTint;
extern bool disableHPUI;
extern bool disableBloodyRageChime;
extern const uintptr_t disableHpUIOffset;
extern uintptr_t disableHPUIAddress;
extern const BYTE nope5Bytes[];
extern const BYTE enableHPUIBytes[];


extern Difficulty currentDifficulty;
extern uint16_t guiPlayerHP;

//HOOKS
extern "C" uintptr_t returnInjectNinpoGauge;
extern "C" uintptr_t returnInjectSurgeGauge;


extern "C" uintptr_t returnInjectDmgMulp;

extern "C" int dsWeaponSelectedIndex;

extern "C" uintptr_t returnInjectWepEquip;
extern "C" uintptr_t jumpInjectWepEquip;
extern "C" uintptr_t returnInjectWepEquip2;
extern "C" uintptr_t jumpInjectWepEquip2;
extern "C" uintptr_t bloodyRageChimeSoundAddress;
extern "C" uintptr_t returnInjectInput;
extern "C" uintptr_t injectInputJEAddress;
extern "C" uintptr_t injectInputJMPAddress;

extern "C" uintptr_t struggleResetCheckAddress;
extern "C" uint16_t previousButton;
extern "C" uint16_t playerInput;
extern "C" bool struggleStarted;
extern "C" bool struggleSuccessFlag;
extern "C" int triangleCount;
extern "C" int squareCount;

extern "C" uintptr_t returnInjectStruggle;
extern "C" bool enableStruggleSystem;

extern uintptr_t freeCamAddress;
extern bool freeCameraEnable;
extern const BYTE freeCameraEnableBytes[];

extern "C" uintptr_t returnInjectAIDodge;
extern "C" uintptr_t returnInjectAIDodgeCallAddress;
extern "C" int aiDodgeChance;

extern "C" uintptr_t returnInjectAnim;

struct AnimationSwaps {
    uint16_t oldAnim;
    uint16_t newAnim;
};
struct AttackCancels {
    uint16_t oldAnim;
    uint16_t newAnim;
    uint16_t input;
    const char* attackCancelName;
};

extern "C" const AnimationSwaps animSwaps[];
extern "C" const size_t animSwapSize;
extern uintptr_t guiplayerActiveAnimation;

extern bool disableSobGlow;
extern uintptr_t sobGlowAddress;

extern "C" std::vector<AttackCancels> attackCancelList;
extern size_t attackCancelSize;

extern "C" uintptr_t returnInjectAttackCancels;
extern "C" uintptr_t injectAttackCancelsJE;

extern "C" uintptr_t returnInjectTrialNinpo;
extern "C" bool replaceInfernoTrueInf;

extern bool disableEnemyAI;
extern uintptr_t disableEnemyAIAddress;

extern bool ryuEnableVeinyArmEffect;
extern uintptr_t ryuVeinyArmEffectAddress;
extern bool disableModelRender;
extern uintptr_t disableModelRenderAddress;
extern const BYTE disableRenderBytes[];
extern const BYTE disableRenderBytesRestore[];
