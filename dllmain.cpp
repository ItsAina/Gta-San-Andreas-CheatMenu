// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
//void test() {
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//
//
// 
//}



namespace offsets {
    DWORD localplayerof = 0x112050;
    std::vector<DWORD> sunflower = { 0x5578 ,0x16C,0x15C ,0x24};
    

}

DWORD findrealptr(DWORD localplayerptr,std::vector<DWORD>offsets){
    DWORD realaddress = localplayerptr;
    for (int i = 0; i < offsets.size(); i++) {
        realaddress += *reinterpret_cast<DWORD*>(realaddress+offsets[i]);
        


    }
    return realaddress;


}

int cheat_test() {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    auto const basemod = reinterpret_cast<DWORD>(GetModuleHandleA("PlantsVsZombies.exe"));
    if (!basemod) {
        std::cerr << "Failed to retrieve module" << std::endl;
        return 1;
        
    }

    auto const localplayer = *reinterpret_cast<DWORD*>(basemod + offsets::localplayerof);

    int32_t sunflowerval = *reinterpret_cast<int32_t*>(findrealptr(localplayer,offsets::sunflower));
    std::cout << sunflowerval << std::endl;
    sunflowerval = 10000;
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
        CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(cheat_test), hModule, 0, nullptr);
        /*FreeLibraryAndExitThread(hModule,0);*/
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

