#include "SimpleIni.h"

wchar_t* GetExecutablePath(wchar_t* exePath, DWORD size) {
    GetModuleFileNameW(NULL, exePath, size);
    wchar_t* lastSlash = wcsrchr(exePath, L'\\');
    if (lastSlash) {
        *lastSlash = L'\0';
    }
    return exePath;
}
void LoadConfig( ) {
    wchar_t exePath[MAX_PATH];
    std::wstring iniPath = std::wstring(GetExecutablePath(exePath, MAX_PATH)) + L"\\dllMods\\fbngreconfig.ini";

    CSimpleIniW ini;
    ini.SetUnicode( );

    SI_Error rc = ini.LoadFile(iniPath.c_str( ));
    if (rc < 0)
        return;

    //MAIN
    ninpoGaugeFillRate = ini.GetDoubleValue(L"MAIN", L"ninpoGaugeFillRate", 0.50f);
    cicadaSurgeNinpoCost = ini.GetDoubleValue(L"MAIN", L"cicadaSurgeNinpoCost", -2.5f);
    damageMulp = ini.GetDoubleValue(L"MAIN", L"damageMulp", 1.10f);
    enableStruggleSystem = ini.GetBoolValue(L"MAIN", L"enableStruggleSystem", true);

    //UIEFFECTS
    disableLowHPRedTint = ini.GetBoolValue(L"UIEFFECTS", L"disableLowHPRedTint", true);
    disableHPUI = ini.GetBoolValue(L"UIEFFECTS", L"disableHPUI", false);
    disableBloodyRageChime = ini.GetBoolValue(L"UIEFFECTS", L"disableBloodyRageChime", true);
    freeCameraEnable = ini.GetBoolValue(L"UIEFFECTS", L"freeCameraEnable", false);
    disableSobGlow = ini.GetBoolValue(L"UIEFFECTS", L"disableSobGlow", false);

    //ENEMYAI
    aiDodgeChance = ini.GetDoubleValue(L"ENEMYAI", L"aiDodgeChance", 65);

    //NINJA TRIALS
    replaceInfernoTrueInf = ini.GetBoolValue(L"NINJATRIALS", L"replaceInfernoTrueInf", false);


    for (auto& entry : attackCancelList)
        free((void*)entry.attackCancelName);
    attackCancelList.clear( );

    CSimpleIniW::TNamesDepend keys;
    ini.GetAllKeys(L"ATTACKCANCELS", keys);

    for (const auto& key : keys) {
        const wchar_t* value = ini.GetValue(L"ATTACKCANCELS", key.pItem, nullptr);
        if (!value)
            continue;

        uint16_t oldAnim = 0, newAnim = 0, input = 0;
        wchar_t desc[256]{ };

        if (swscanf(value, L"0x%hx,0x%hx,%hx,%255[^\"]", &oldAnim, &newAnim, &input, desc) >= 3) {
            std::wstring wideDesc(desc);
            std::string utf8desc(wideDesc.begin( ), wideDesc.end( ));

            char* copiedDesc = _strdup(utf8desc.c_str( ));
            attackCancelList.push_back({oldAnim, newAnim, input, copiedDesc});
        }
    }
}

void SaveConfig( ) {
    wchar_t exePath[MAX_PATH];
    std::wstring iniPath = std::wstring(GetExecutablePath(exePath, MAX_PATH)) + L"\\dllMods\\fbngreconfig.ini";


    CreateDirectoryW((iniPath.substr(0, iniPath.find_last_of(L'\\'))).c_str( ), NULL);

    if (attackCancelList.empty( ))
        return;

    CSimpleIniW ini;
    ini.SetUnicode( );
    ini.LoadFile(iniPath.c_str( ));

    ini.Delete(L"ATTACKCANCELS", nullptr);

    for (size_t i = 0; i < attackCancelList.size( ); ++i) {
        const auto& entry = attackCancelList[i];

        std::wstring wideDesc(entry.attackCancelName, entry.attackCancelName + strlen(entry.attackCancelName));

        std::wstringstream valueStream;
        valueStream << L"0x" << std::hex << entry.oldAnim
                    << L",0x" << entry.newAnim
                    << L",0x" << entry.input
                    << L"," << wideDesc;

        wchar_t key[32];
        swprintf_s(key, L"Entry%zu", i);

        ini.SetValue(L"ATTACKCANCELS", key, valueStream.str( ).c_str( ));
    }

    ini.SaveFile(iniPath.c_str( ));
}
