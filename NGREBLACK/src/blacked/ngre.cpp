#include "ngre.h"
#include <basetsd.h>



Ngre::Ngre(DWORD_PTR baseAddress) {
    playerHPAddress = baseAddress + playerHPOffset;
    storyDifficultyAddress = baseAddress + storyDifficultyOffset;
    disableHPUIAddress = baseAddress + disableHpUIOffset;
    ninpoGaugeRateJumpAddress += baseAddress;
    ninpoGaugeRateCallAddress += baseAddress;
    surgeGaugeRateCallAddress += baseAddress;
    surgeGaugeRateJumpAddress += baseAddress;
    lowHPRedTintAddress = baseAddress + lowHPRedTintOffset;
    jumpInjectWepEquip += baseAddress;
    jumpInjectWepEquip2 += baseAddress;
    injectInputJEAddress += baseAddress;
    injectInputJMPAddress += baseAddress;
    struggleResetCheckAddress += baseAddress;
    bloodyRageChimeSoundAddress += baseAddress;
    freeCamAddress += baseAddress;
    returnInjectAIDodgeCallAddress += baseAddress;
    playerIdentAddress += baseAddress;
    playerIdentAddress2 += baseAddress;
    guiplayerActiveAnimation += baseAddress;
    sobGlowAddress += baseAddress;
    injectAttackCancelsJE += baseAddress;
    disableEnemyAIAddress += baseAddress;

    HookInfo hooks[] = {
 
        {0x1A1BF33, 19, InjectNinpoGauge, "InjectNinpoGauge", &returnInjectNinpoGauge, 0},
        {0x18C3C56, 17, InjectSurgeGauge, "InjectSurgeGauge", &returnInjectSurgeGauge, 0},
        //{0x1BC19C1, 18, InjectSurgeGauge, "InjectSurgeGauge", &returnInjectSurgeGauge, 0},
        {0x1A125F1, 16, InjectDmgMulp, "InjectDmgMulp", &returnInjectDmgMulp, 0},
        {0x189612F, 14, InjectWepEquip2, "InjectWepEquip2", &returnInjectWepEquip2, 0},
        {0x1BC19C4, 15, InjectWepEquip, "InjectWepEquip", &returnInjectWepEquip, 0},
        {0xB92E9C, 17, InjectInput, "InjectInput", &returnInjectInput, 0},
        {0x149F410, 14, InjectStruggle, "InjectStruggle", &returnInjectStruggle,0},
        {0x14909DD, 18, InjectAIDodge, "InjectAIDodge", &returnInjectAIDodge, 0},
        {0x14DC827, 15, InjectAnimation, "InjectAnimation", &returnInjectAnim,0},
        {0x14696ED, 18, InjectAttackCancels, "InjectAttackCancels", &returnInjectAttackCancels,0},
        {0x1B75624, 16, InjectTrialNinpo, "InjectTrialNinpo", &returnInjectTrialNinpo,0}
        //NINJA GAIDEN 3 Razor's Edge.exe+18EA9A4 disable OT huge blood
        //NINJA GAIDEN 3 Razor's Edge.exe+1494167 - disable delimb if mem value is not 01
        // FS Regular
        /*cmp dx,
        70A je dsFS
            cmp dx,
        6F7 je dsFS*/
        //disable bloody rage chime sound 5974F88 (set to 02 01 = chime)
        //ONE HIT KILL nop nop NINJA GAIDEN 3 Razor's Edge.exe+14902F0 
        //dodge block NINJA GAIDEN 3 Razor's Edge.exe+149053B 
        //freeze enemies NINJA GAIDEN 3 Razor's Edge.exe+14B0A29 
        //RGB NINJA GAIDEN 3 Razor's Edge.exe+17B6ED7
        //move tracking NINJA GAIDEN 3 Razor's Edge.exe+1462B03 
        //NINJA GAIDEN 3 Razor's Edge.exe+17E269B no hurt box
        //NINJA GAIDEN 3 Razor's Edge.exe+14DC9FA animation 762 unused ET 792
        //NINJA GAIDEN 3 Razor's Edge.exe+14675BE OT struggle
        //CANT MASH SOB
        //NINJA GAIDEN 3 Razor's Edge.exe+149F410  NINJA GAIDEN 3 Razor's Edge.exe+149CD31 
        //XINPUT NINJA GAIDEN 3 Razor's Edge.exe+B92E9C 
        //IS NINJA WILL KILL THEMSELVES NINJA GAIDEN 3 Razor's Edge.exe+14A0D5C 


    };
    ApplyHooks(hooks, sizeof(hooks) / sizeof(HookInfo), baseAddress);
   
   
}

 


   



