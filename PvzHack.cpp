
#include <iostream>
#include <Windows.h>
#include <vector>
#include<TlHelp32.h>
#include <list>
#include <tchar.h> 
#include <chrono>
#include <thread>
#include <algorithm> 
#include <cctype>    
#include <string>


using namespace std;

struct offsets {
	DWORD playeroffset = 0x112050;
	vector<DWORD> sunflower = { 0x24,0x15C,0x16C,0x5578};

}offset;
DWORD getbasemoduleaddress(const wchar_t* modulename, DWORD pid) {
	DWORD dwModuleBaseAddress = 0;
	MODULEENTRY32 ModuleEntry32 = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnapshot, &ModuleEntry32))
	{
		do
		{
			if (_tcscmp(ModuleEntry32.szModule, modulename) == 0) {
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));
	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}


DWORD findrealptr(HANDLE myhandle,DWORD localplayerptr, std::vector<DWORD>offsets) {
	DWORD realaddress = localplayerptr;
	DWORD addressval;
	for (int i = 0; i < offsets.size(); i++) {
		//ReadProcessMemory(myhandle, LPCVOID(localplayerptr+offsets[i]), &addressval, sizeof(DWORD), 0);
		realaddress = localplayerptr + offsets[i];
		cout << realaddress << endl;
	}
	return realaddress;


}

int main() {
	HWND windowtitle = FindWindowA(0,"Plants vs. Zombies");
	if (!windowtitle) {
		cerr << "hwnd not found" << endl;
		return 1;

	}
	
	DWORD procid;
	GetWindowThreadProcessId(windowtitle,&procid);
	HANDLE mhandle = OpenProcess(PROCESS_ALL_ACCESS, 0, procid);
	DWORD localplayer = getbasemoduleaddress(L"PlantsVsZombies.exe",procid);
	DWORD localplayerptr;
	ReadProcessMemory(mhandle,LPCVOID(localplayer + offset.playeroffset),&localplayerptr,sizeof(localplayerptr),0);
	DWORD localplayerslist = findrealptr(mhandle, localplayerptr, offset.sunflower);
	cout << localplayerslist << endl;
	int32_t sunamount;
	ReadProcessMemory(mhandle, LPCVOID(localplayerslist), &sunamount, sizeof(int32_t), 0);
	cout << sunamount << endl;






}