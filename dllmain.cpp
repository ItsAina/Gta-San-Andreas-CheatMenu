// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdint.h>
#include<TlHelp32.h>
#include <list>
#include <tchar.h> 
#include <iostream>






struct playerpos {
    float x, y, z;


}PlayerPosition;

namespace offsets {
    DWORD health_offset = 0x540;
    DWORD xpos_offset = 0x30;
    DWORD ypos_offset = 0x34;
    DWORD zpos_offset = 0x38;
    DWORD localplayeroffset = 0x771A38;
    DWORD money_offset = 0xb7f4d0;
    DWORD MuscleAddr = 0xB7BA5C;
    DWORD LungCapacityAddr = 0xB7F43C;
    DWORD MaxHealthAddr = 0xB7BA60;
    DWORD RespectAddr = 0xB7BB00;
    DWORD Inventory = 0xB7F43C;
    DWORD TimeControl = 0xB7F4D0;
    DWORD skillpistoladdr = 0xB7BB14;
    DWORD skillsilenecedpistoladdr = 0xB7BB18;
    DWORD skillDeagleaddr = 0xB7BB1C;
    DWORD skillshotgunaddr = 0xB7BB20;
    DWORD skillsawnaddr = 0xB7BB24;
    DWORD skillcombatshotgunaddr = 0xB7BB28;
    DWORD skillmachinepistoladdr = 0xB7BB2C;
    DWORD skillsmgaddr = 0xB7BB30;
    DWORD skillak47addr = 0xB7BB34;
    DWORD skillm4addr = 0xB7BB38;
    DWORD infiniteammoaddr = 0x96B7F8;
    DWORD SpawnRomaddr = 0xB7B6C4;
    DWORD Unbreakablecar = 0x96B7E4;
    DWORD neverwanted = 0x96B7F0;
    DWORD minigunoffset = 0x5AC;
    DWORD invincible = 0x96B7EC;
    DWORD megapunch = 0x96B7F0;
}




void cheatmenu() {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    bool godmode = false;
    bool unbreakableshield = false;
    bool unbreakablecar = false;
    bool infiniteammo = false;
    bool overwrite = true;

    // Get base address of the game module
    const auto BaseModule = (DWORD)GetModuleHandle(L"gta_sa.exe");
    if (BaseModule == NULL) {
        std::cerr << "Failed to get module handle." << std::endl;
        return;
    }
    std::cout << BaseModule << std::endl;

    /*int32_t * money = (int32_t*)(offsets::money_offset);
    *money = 500000000;*/
        
    //std::cout << *money << std::endl;

    uintptr_t LocalPlayer = *(uintptr_t*)(BaseModule + offsets::localplayeroffset);
    float health = *(float*)(LocalPlayer + offsets::health_offset);
    std::cout << "Health: " << health << std::endl;
    FreeConsole();
}








BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)cheatmenu, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

