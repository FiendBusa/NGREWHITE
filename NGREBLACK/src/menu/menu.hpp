#pragma once

#include <Windows.h>
#include "..\utils\SimpleIni.h"

namespace Menu {
    void InitializeContext(HWND hwnd);
    void Render( );


    inline bool bShowMenu = true;
} // namespace Menu
