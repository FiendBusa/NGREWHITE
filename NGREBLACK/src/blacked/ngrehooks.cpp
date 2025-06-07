
#include "../blacked/ngrehooks.h"


bool Hook(void* hookAddress, void* myFunc, int len, int nopeLen) {

    if (len < 14 && nopeLen <= 0) {
        return false;
    }

    DWORD oldProtect;
    VirtualProtect(hookAddress, len, PAGE_EXECUTE_READWRITE, &oldProtect);

    *(BYTE*)hookAddress = 0xFF;
    *((BYTE*)hookAddress + 1) = 0x25;
    *(DWORD*)((BYTE*)hookAddress + 2) = 0;
    *(DWORD_PTR*)((BYTE*)hookAddress + 6) = (DWORD_PTR)myFunc;

    if (nopeLen > 0) {
        for (int i = 0; i < nopeLen; i++) {
            *((BYTE*)hookAddress + len + i) = 0x90;
        }
    }

    VirtualProtect(hookAddress, len, oldProtect, &oldProtect);

    return true;
}

void ApplyHooks(HookInfo* hooks, int count, DWORD_PTR baseAddress) {
    for (int i = 0; i < count; i++) {
        DWORD_PTR hookAddress = baseAddress + hooks[i].offset;
        if (hooks[i].returnAddress) {
            *(hooks[i].returnAddress) = hookAddress + hooks[i].length;
        }
        if (!Hook((void*)hookAddress, hooks[i].hookFunction, hooks[i].length, hooks[i].nopeLen)) {

        }
    }
}
uint16_t SwapAnimations(uint16_t currentAnim, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (animSwaps[i].oldAnim == currentAnim) {
            return animSwaps[i].newAnim;
        }
    }
    return currentAnim;
}

uint16_t AttackCancel(uint16_t currentAnim, uint16_t currentInput, AttackCancels* attackCancelList) {
    size_t size = GetAttackCancelSize( );
    
    if (currentAnim == 0xFFFF || (currentAnim == 0x0000 || size == 0)) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (currentInput == attackCancelList[i].input && currentAnim == attackCancelList[i].oldAnim) {
            *(uint16_t*)(playerIdentAddress + 0x086E) = attackCancelList[i].newAnim;
            return 1;
        }
    }
    return 0;
}
 
    

size_t GetAttackCancelSize() {
    return attackCancelList.size( );
}


__attribute__((naked)) void InjectAttackCancels( ) {

    __asm(".intel_syntax noprefix;"
          "mov ebp,0x0000FFFF;"
          "cmp bp,[rcx+0x0000086E];"
          "je attackCancelJE;"
          "jmp attackCancelsExit;"

          "attackCancelJE:"
          "push rax;"
          "push rbx;"
          "push rcx;"
          "push rdx;"
          "push r8;"

          "mov rax, qword ptr [rip + playerIdentAddress];"
          "cmp rax,rcx;"
          "jne attackCancelJEFinish;"
          
          "movzx rcx, word ptr [rcx + 0x01C4];"
          "movzx rdx, word ptr [rip + playerInput];"
          "lea r8, qword ptr [rip + attackCancelList];"
          "mov r8, qword ptr [r8];"
          "lea rbx, qword ptr [rip + AttackCancel];"

          "sub rsp,0x08;"
          "call rbx;"
          "add rsp,0x08;"

                

          "attackCancelJEFinish:"
          "pop r8;"
          "pop rdx;"
          "pop rcx;"
          "pop rbx;"
          "pop rax;"
          "jmp qword ptr [rip + injectAttackCancelsJE];"

          "attackCancelsExit:"
          "jmp qword ptr [rip + returnInjectAttackCancels];"

    );
}


__attribute__((naked)) void InjectNinpoGauge( ) {

    __asm(".intel_syntax noprefix;"
          "push rax;"
          "mov rax, qword ptr [rip + ngreBaseAddress];"
          "movss xmm1,[rip + ninpoGaugeFillRate];"
          "addss xmm0,xmm1;" 
          "movss[rbx + 0x00000D6C],xmm0;"
          "pop rax;"
          "jmp qword ptr [rip + ninpoGaugeRateJumpAddress];"
          "movzx ecx,dil;"
          "call qword ptr [rip + ninpoGaugeRateCallAddress];"

          "jmp qword ptr [rip + returnInjectNinpoGauge];"

    );
}

__attribute__((naked)) void InjectSurgeGauge( ) {

    __asm(".intel_syntax noprefix;"
          "movss xmm1,[rip + cicadaSurgeNinpoCost];"
          "call qword ptr [rip + surgeGaugeRateCallAddress];"
          "jmp qword ptr [rip + surgeGaugeRateJumpAddress];"
          "jmp qword ptr [rip + returnInjectSurgeGauge];"

    );
}
__attribute__((naked)) void InjectDmgMulp( ) {

    __asm(".intel_syntax noprefix;"
          "push rax;"
          "mov rax, qword ptr [rip + ngreBaseAddress];"
          "cmp byte ptr [rbx + 0x20],0x00;"
          "jnz isNotPlayer;"

          "movss xmm6,[rax + 0x20FA698];"
          "jmp injectDmgExit;"

          "isNotPlayer:"
          "movss xmm6, [rip + damageMulp];"
      
       
          "injectDmgExit:"
          "pop rax;"
          "movaps xmm3,xmm6;"
          "movaps xmm2,xmm6;"
          "xor ecx,ecx;"
                                                                     
                                                                     
          

          "jmp qword ptr [rip + returnInjectDmgMulp];"

    );
}

__attribute__((naked)) void InjectWepEquip( ) {

    __asm(".intel_syntax noprefix;"
          "lea rdx, [rax + rcx * 0x02];"
          "mov rax, qword ptr [rip + jumpInjectWepEquip];"
          "movzx eax, word ptr [rax + rdx * 0x02];"

           "cmp ax,0x01;"
           "je isSword;"
           "cmp ax,0x02;"
           "je isSword;"
           "cmp ax,0x05;"
           "je isSword;"
           "cmp ax,0xAF;"
           "je isSword;"
           "cmp ax,0x9B;"
           "je isSword;"
           "cmp ax,0x2E;"
           "je isSword;"
           "jmp exitInjectWepEquip;"

          "isSword:"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x00;"
          "jz exitInjectWepEquip;"

          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x04;"
          "je isNonSpark;"

         "cmp r10,0x05;"
         "jne exitInjectWepEquip;"

         /* "mov eax,0x01;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x01;"
          "je equipNewWep;"*/

          "mov rax,0x05;"
          "mov r10,0x9B;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x02;"
          "je exitInjectWepEquip;"

         /* "mov eax,0x9B;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x03;"
          "je equipNewWep;"

          "mov eax,0xAF;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x04;"
          "je equipNewWep;"

          "mov eax,0x2E;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x05;"
          "je equipNewWep;"*/

          "movzx eax, word ptr [rax + rdx * 0x02];"
          "jmp exitInjectWepEquip;"

         /* "equipNewWep:"
          "mov r10,rax;"*/
          "isNonSpark:"
          "cmp r10,0x0AF;"
          "jne exitInjectWepEquip;"
          "cmp rax,0x02E;"
          "jne exitInjectWepEquip;"
          "mov rax,r10;"

          "exitInjectWepEquip:"
          "jmp qword ptr [rip + returnInjectWepEquip];"

    );
}


__attribute__((naked)) void InjectWepEquip2( ) {

    __asm(".intel_syntax noprefix;"
          "movzx ecx, byte ptr [rax + 0x00001596];"

         /* "cmp cl,0x01;"
          "je isSword;"
          "cmp cl,0x02;"
          "je isSword;"
          "cmp cl,0x05;"
          "je isSword;"
          "cmp cl,0xAF;"
          "je isSword;"
          "cmp cl,0x9B;"
          "je isSword;"
          "jmp exitInjectWepEquip;"*/

          "isSword2:"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x00;"
          "jz exitInjectWepEquip2;"
          
          "mov ecx,0x01;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x01;"
          "je equipNewWep2;"

          "mov ecx,0x05;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x02;"
          "je equipNewWep2;"

          "mov ecx,0x02;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x03;"
          "je equipNewWep2;"

          "mov ecx,0xAF;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x04;"
          "je equipNewWep2;"

          "mov ecx,0x2E;"
          "cmp byte ptr [rip + dsWeaponSelectedIndex],0x05;"
          "je equipNewWep2;"

          "movzx ecx, byte ptr [rax + 0x00001596];"
          "jmp exitInjectWepEquip2;"

          "equipNewWep2:"
          "mov byte ptr [rax + 0x00001596], cl;"

          "exitInjectWepEquip2:"
          "jmp qword ptr [rip + jumpInjectWepEquip2];"

    );
}
__attribute__((naked)) void InjectInput( ) {

    __asm(".intel_syntax noprefix;"
          "push rax;"
          "push rbx;"
          "movzx rax, word ptr [rsp + 0x35];"
          "mov [rip + playerInput], ax;"


          "mov rbx, qword ptr [rip + struggleResetCheckAddress];"
          "cmp byte ptr [rbx],0x02;"
          "jne struggleReset;"

          "cmp byte ptr [rip + enableStruggleSystem],0x00;"
          "jz struggleReset;"

          "movzx rbx, word ptr [rip + previousButton];"

          "cmp byte ptr [rip + struggleStarted],0x00;"
          "jz struggleDone;"

          "test ax,0x80;"
          "jz skipTriangle;"
          "test bx,0x80;"
          "jnz skipTriangle;"
          "inc dword ptr [rip + triangleCount];"

          "skipTriangle:"
          "test ax,0x01;"
          "je skipSquare;"
          "test bx,0x01;"
          "jnz skipSquare;"
          "inc dword ptr [rip + squareCount];"

          "skipSquare:"
          "mov [rip + previousButton], ax;"
          "mov eax, [rip + triangleCount];"
          "cmp eax,0x05;"
          "jl struggleDone;"
          "mov eax, [rip + squareCount];"
          "cmp eax,0x05;"
          "jl struggleDone;"

          "mov byte ptr [rip + struggleSuccessFlag],0x01;"
          "mov dword ptr [rip + triangleCount],0x00;"
          "mov dword ptr [rip + squareCount],0x00;"
          "jmp struggleDone;"

          "struggleReset:"
          "mov byte ptr [rip + struggleSuccessFlag],0x00;"
          "mov dword ptr [rip + triangleCount],0x00;"
          "mov dword ptr [rip + squareCount],0x00;"
          "mov byte ptr [rip + struggleStarted],0x00;"

          "struggleDone:"
          "pop rbx;"
          "pop rax;"
           
          "test eax,eax;"
          "je injectInputJE;" 
          "xor al,al;"
          "jmp qword ptr [rip + injectInputJMPAddress];"
           
          "injectInputJE:"
          "and dword ptr [rdi],0xFFFFC000;"
          "jmp qword ptr [rip + returnInjectInput];"


    );
}
__attribute__((naked)) void InjectStruggle( ) {

    __asm(".intel_syntax noprefix;"
          "mov dword ptr [rcx+0x00001EA4],0x00000001;"
          "mov eax,0x01;"
          "cmp byte ptr [rip + enableStruggleSystem],0x00;"
          "jz struggleExit;"
          
          "mov byte ptr [rip + struggleStarted],0x01;"

          "xor rax,rax;"
          "cmp byte ptr [rip + struggleSuccessFlag],0x01;"
          "jl struggleExit;"

          "mov byte ptr [rip + struggleStarted],0x00;"
          "mov byte ptr [rip + struggleSuccessFlag],0x00;"
          "mov dword ptr [rip + triangleCount],0x00;"
          "mov dword ptr [rip + squareCount],0x00;"
          "mov eax,0x01;"
            
          "struggleExit:"
          "ret;"

    );
}
__attribute__((naked)) void InjectAIDodge( ) {

    __asm(".intel_syntax noprefix;"
          "push rbx;"
          "push rcx;"
       

          "cmp al,0x05;"
          "jne exitAIDodge;"

          "mov rbx, qword ptr [rip + playerIdentAddress];"
          "cmp rdi,rbx;"
          "jne exitAIDodge;"
          "movzx rbx, byte ptr [rip + randNum];"
          "movzx rcx, byte ptr [rip + aiDodgeChance];"
          "test rcx,rcx;"
          "jz exitAIDodge;"

          "cmp bx,cx;"
          "ja exitAIDodge;"

          "mov al,0x01;"
          "mov si,0x01;"     

          "exitAIDodge:"
          "pop rcx;"
          "pop rbx;"
          "mov [rbp - 0x56], al;"
          "mov rcx,rbx;"
          "call qword ptr [rip + returnInjectAIDodgeCallAddress];"
          "mov [rbp - 0x55],al;"
          "mov [rbp - 0x51],sil;"
          "jmp qword ptr [rip + returnInjectAIDodge];"

    );
}
__attribute__((naked)) void InjectAnimation( ) {

    __asm(".intel_syntax noprefix;" 
         "mov [rsp + 0x60], rbx;" 
         "mov [rsp + 0x68], rbp;"
         "mov [rsp + 0x70], rsi;"

          
          "push rax;"
          "push rbx;"
          "push rcx;"


          "test rdx,rdx;"
          "jz exitAnimation;"

       

          "mov rcx, qword ptr [rip + playerIdentAddress2];"
          "cmp rax,rcx;"
          "jne exitAnimation;"

          "mov rcx,rdx;"
          "mov rdx, [rip + animSwapSize];"
          "sub rsp,0x08;"
          "lea rax, qword ptr [rip + SwapAnimations];"
          "call rax;"
          "add rsp,0x08;"

          "mov dx,ax;"
          
           
          "exitAnimation:"
          "pop rcx;"
          "pop rbx;"
          "pop rax;"
          "jmp qword ptr [rip + returnInjectAnim];"

    );
}
__attribute__((naked)) void InjectTrialNinpo( ) {

    __asm(".intel_syntax noprefix;"
          "mov rax,[r11+rax*0x08+0x02686A80];"
          "movzx edx,word ptr [rax+rdx*0x04];"

          "cmp byte ptr [rip + replaceInfernoTrueInf],0x00;"
          "jz exitInjectTrialNinpo;"
          
          "cmp dx,0x0004;"
          "jne exitInjectTrialNinpo;"
          
          "mov dx,0x004F;"

          "exitInjectTrialNinpo:"
          "mov [rbx+0x44],dx;"
          "jmp qword ptr [rip + returnInjectTrialNinpo];"

    );
}
