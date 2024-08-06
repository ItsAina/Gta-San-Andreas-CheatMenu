#include <iostream>
#include <Windows.h>
#include <vector>
#include<TlHelp32.h>
#include <list>
#include <tchar.h> 
#include <chrono>
#include <thread>
#include <ranges>
#include <tuple>

using namespace std;


//class PlayerObject {
//public:
//
//
//
//};
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


DWORD getpointeraddress(HANDLE phandle, DWORD PlayerObjectaddress, const vector<DWORD>& offsets) {
	DWORD address = PlayerObjectaddress;

	for (size_t i = 0; i < offsets.size(); ++i) {
		ReadProcessMemory(phandle, (LPCVOID)address, &address, sizeof(address), nullptr);
		address += offsets[i];
		cout << address << endl;
	}

	return address;
}


void choosecheatmenumode(DWORD pid,HANDLE GetHandle) {
	vector<DWORD> offsets = { 0x540,0xB4,0x0,0x4,0xB0,0x1CC };
	vector<DWORD> locationoffsets = { 0x30,0x34,0x38 };
	//float health = *(float*)(0xB6F5F0 + 0x540);
	DWORD MoneyOffset = 0xB7F4D0;
	DWORD BaseAddr = getbasemoduleaddress(L"gta_sa.exe", pid);
	DWORD PlayerObj = 0x771A38;
	DWORD xaddr = 0x771C70;
	DWORD yaddr = 0x771A38;
	DWORD zaddr = 0x771C70;
	uintptr_t Playerptr;
	uintptr_t xptr;
	uintptr_t yptr;
	uintptr_t zptr;
	ReadProcessMemory(GetHandle, LPCVOID(BaseAddr + PlayerObj), &Playerptr, sizeof(Playerptr), 0);
	ReadProcessMemory(GetHandle, LPCVOID(BaseAddr + xaddr), &xptr, sizeof(xptr), 0);
	ReadProcessMemory(GetHandle, LPCVOID(BaseAddr + yaddr), &yptr, sizeof(yptr), 0);
	ReadProcessMemory(GetHandle, LPCVOID(BaseAddr + zaddr), &zptr, sizeof(zptr), 0);
	//DWORD Offset = getpointeraddress(getwindowtitle,PlayerObjectAddr,offsets);
	bool godmode = false;
	int Addmoney;
	float health, armor;
	float fatness,stamina,muscle;
	float x, y, z;
	while (true) {
		
		if (GetAsyncKeyState(VK_F2)) {
			godmode = not godmode;
			this_thread::sleep_for(chrono::milliseconds(500));
			//cout << godmode << endl;
			if (godmode) {
				cout << "God mode is toggled on" << endl;
				health = std::numeric_limits<double>::infinity();
				WriteProcessMemory(GetHandle, LPVOID(Playerptr + 0x540), &health, sizeof(health), 0);
				cout << health << endl;
	
				
			}

			else {
				cout << "God mode is toggled off" << endl;
				health = 100;
				WriteProcessMemory(GetHandle, LPVOID(Playerptr + 0x540), &health, sizeof(health), 0);


			}
		}
		if (GetAsyncKeyState(VK_F3)) {
			ReadProcessMemory(GetHandle, LPCVOID(MoneyOffset), &Addmoney, sizeof(Addmoney), 0);
			cout << "Your current money is" << "$" << Addmoney << endl;
			cout << "How much money, you want to add?" << endl;
			cin >> Addmoney;
			WriteProcessMemory(GetHandle, LPVOID(MoneyOffset), &Addmoney, sizeof(Addmoney), 0);


		}
		if (GetAsyncKeyState(VK_F4)) {
			ReadProcessMemory(GetHandle, LPCVOID(xptr + 0x30), &x, sizeof(x), 0);
			ReadProcessMemory(GetHandle, LPCVOID(yptr + 0x34), &y, sizeof(y), 0);
			ReadProcessMemory(GetHandle, LPCVOID(zptr + 0x38), &z, sizeof(z), 0);
			cout << "Your current position of:\t" << "x\t" << x << "y\t" << y << "z\t" << z << "\n";
			cout << "Add coordinates for x" << endl;
			cin >> x;
			cout << "Add coordinates for y" << endl;
			cin >> y;
			cout << "Add coordinates for x" << endl;
			cin >> z;


			WriteProcessMemory(GetHandle, LPVOID(xptr + 0x30), &x, sizeof(x), 0);
			WriteProcessMemory(GetHandle, LPVOID(yptr + 0x34), &y, sizeof(y), 0);
			WriteProcessMemory(GetHandle, LPVOID(zptr + 0x38), &z, sizeof(z), 0);
	/*		int counter = 0;
			for (float coordinate : coordinates) {
				WriteProcessMemory(GetHandle, LPVOID(locationpointer[counter] + locationoffsets[counter]), &coordinate, sizeof(coordinate), 0);
				counter += 1;

			}*/

		}


		/*if (GetAsyncKeyState(VK_F4)) {


		}

		if (GetAsyncKeyState(VK_F5)) {



		}*/



	}
}


int main() {
	HWND getwindowtitle = FindWindowA(0,"GTA: San Andreas");
	if (not getwindowtitle == 0) {
		cout << "Window founded" << endl;

	}

	else {
		return 1;


	}

	DWORD pid;
	GetWindowThreadProcessId(getwindowtitle, &pid);
	HANDLE GetHandle = OpenProcess(PROCESS_ALL_ACCESS,0,pid);

	choosecheatmenumode(pid,GetHandle);
	/*DWORD FatAddress = 0xB793D4;
	DWORD x = 0x14;
	DWORD y = 0x0;
	DWORD z = 0x2C;
	DWORD playerptr = 0xB7CD98;
	DWORD playerptrhealth = playerptr + x;*/






}
