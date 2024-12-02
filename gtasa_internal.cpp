// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdint.h>
#include<TlHelp32.h>
#include <list>
#include <tchar.h> 
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


class localplayerlist
{
public:
    char pad_0004[72]; //0x0004
    float jump; //0x004C
    char pad_0050[1264]; //0x0050
    float health; //0x0540
    char pad_0544[4]; //0x0544
    float armor; //0x0548
    char pad_054C[172]; //0x054C
    int32_t shotgunshoot; //0x05F8
    char pad_05FC[596]; //0x05FC

    virtual void Function0();
    virtual void Function1();
    virtual void Function2();
    virtual void Function3();
    virtual void Function4();
    virtual void Function5();
    virtual void Function6();
    virtual void Function7();
    virtual void Function8();
    virtual void Function9();
}; //Size: 0x0850




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
        cerr << "Failed to get module handle." << endl;
        return;
    }
    cout << BaseModule << endl;

    /*int32_t * money = (int32_t*)(offsets::money_offset);
    *money = 500000000;*/

    //std::cout << *money << std::endl;

    uintptr_t LocalPlayer = *reinterpret_cast<uintptr_t*>(BaseModule + offsets::localplayeroffset);
    float health = *reinterpret_cast<float*>(LocalPlayer + offsets::health_offset);
    uintptr_t playervecpos = *reinterpret_cast<float*>(LocalPlayer + 0x14);
     
    
    localplayerlist* localplayerobjlist = reinterpret_cast<localplayerlist*>(LocalPlayer);
    /* int32_t reloading = 2;
     int32_t shooting = 1;*/
    float x;
    float y;
    float z;
    x = *reinterpret_cast<float*>(playervecpos + 0x30);
    y = *reinterpret_cast<float*>(playervecpos + 0x34);
    z = *reinterpret_cast<float*>(playervecpos + 0x38);
    bool jumphack = false;
    bool flyhack = false;
    float jumpval;


    while (true) {
        localplayerobjlist->jump = 0;

        if (GetAsyncKeyState('6')) {
            jumphack != jumphack;

            if (jumphack) {
                cout << "Add value for jump value" << endl;
                cin >> jumpval;
            }


        }

        else if (GetAsyncKeyState('7')) {
            flyhack != flyhack;
            this_thread::sleep_for(chrono::seconds(1));

        }




        if (jumphack && not flyhack) {
            if (GetAsyncKeyState(VK_SPACE)) {
                localplayerobjlist->jump = jumpval;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }

        if (not jumphack && flyhack) {
            if (GetAsyncKeyState('w')) {
                this_thread::sleep_for(chrono::seconds(1));
            }
            else if (GetAsyncKeyState('a')) {
                //float xneg = 
                localplayerobjlist->jump = jumpval;
                this_thread::sleep_for(chrono::seconds(1));
            }
            else if (GetAsyncKeyState('s')) {
                /*float yneg = */
                localplayerobjlist->jump = jumpval;
                this_thread::sleep_for(chrono::seconds(1));
            }

            else if (GetAsyncKeyState('d')) {
                /*float ypos = */
                localplayerobjlist->jump = jumpval;
                this_thread::sleep_for(chrono::seconds(1));
            }

            else if (GetAsyncKeyState(VK_CONTROL)) {
                float zneg = localplayerobjlist->jump = jumpval;
                this_thread::sleep_for(chrono::seconds(1));
            }

            else if (GetAsyncKeyState(VK_SPACE)) {
                /*float zpos =*/
            localplayerobjlist->jump = jumpval;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }




        /* if (localplayerobjlist->shotgunshoot == shooting) {
             cout << "Local player is shooting now with shotgun" << endl;

         }
         else if (localplayerobjlist->shotgunshoot == reloading) {
             cout << "Local player is reloading now with shotgun" << endl;

         }

         else {
             cout << "Local player is not shooting either reloading" << endl;

         }*/



    }

    FreeConsole();
}


BOOL APIENTRY DllMain(HMODULE hModule,
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
