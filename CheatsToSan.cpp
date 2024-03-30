#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include<TlHelp32.h>
#include <list>
#include <tchar.h> // _tcscmp
using namespace std;

//12E3FBF0 coords to x teleport
		//12E3FBF4 coords to y teleport
		//12E3FBF8 coords to z teleport
DWORD GetProcId(const wchar_t* procName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {

			do {

				if (!_wcsicmp(procEntry.szExeFile, procName)) {

					procId = procEntry.th32ProcessID;
					break;


				}





			} while (Process32Next(hSnap, &procEntry));






		}







	}
	CloseHandle(hSnap);
	return procId;






	
}


DWORD dwGetModuleBaseAddress(const wchar_t* lpszModuleName, DWORD ProcessID) {
	DWORD dwModuleBaseAddress = 0;
	MODULEENTRY32 ModuleEntry32 = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnapshot, &ModuleEntry32))
	{
		do
		{
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) {
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));
	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}


int main() {
	HWND OpenWindow = FindWindowA(0, "GTA: San Andreas");
	DWORD pid;
	DWORD x_coord = 0x12E3FBF0, y_coord = 0x12E3FBF4, z_coord = 0x12E3FBF8;
	if (OpenWindow != 0) {
		GetWindowThreadProcessId(OpenWindow, &pid);
		HANDLE pidconnect = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		DWORD hpoffset = 0x540;
		cout << "Process found" << endl;
		cout << "f3 for godmode, f4 for teleport, f5 infinite stamina, f6 for unlimited ammo, f7 for gang territory set, f8 for aimbot\n";
		cout << "Choose keyword between f2,f4,f5,f6,f7,f8 to initiate cheat\n";

		DWORD GetProcess = GetProcId(L"gta_sa.exe");
		uintptr_t BaseAddress = dwGetModuleBaseAddress(L"gta_sa.exe", GetProcess);
		DWORD StaticAddress = 0x00772000;
		uintptr_t FullBase = BaseAddress + StaticAddress;
		float health;
		ReadProcessMemory(pidconnect, (LPCVOID)(FullBase+hpoffset), &health, sizeof(health), 0);
		cout << "Health: " << health << endl;

		bool condition = false;
		while (true) {
			if (GetAsyncKeyState(VK_F2)) {
				condition = not condition;
				Sleep(200);
				if (condition) {
					cout << "God mode turned it on" << endl;
					while (true) {
						float health = 100;
						WriteProcessMemory(pidconnect, (LPVOID)FullBase, &health, sizeof(health), 0);
						if (GetAsyncKeyState(VK_F2)) {
							cout << "God mode turned it off\n";
							break;

						}

					}
				}



			}


			//12E3FBF0 coords to x teleport
			//12E3FBF4 coords to y teleport
			//12E3FBF8 coords to z teleport
			//if (health < 100) {
				//float health = 100;
				//WriteProcessMemory(pidconnect, (LPVOID)healthaddress, &health, sizeof(health), 0);

			//}

			if (GetAsyncKeyState(VK_F4)) {
				float Coordinate_x;
				float Coordinate_y;
				float Coordinate_z;
				cout << "Add coordinates for x\n";
				cin >> Coordinate_x;
				cout << "Add coordinates for y\n";
				cin >> Coordinate_y;
				cout << "Add coordinates for z\n";
				cin >> Coordinate_z;
				WriteProcessMemory(pidconnect, (LPVOID)x_coord, &Coordinate_x, sizeof(Coordinate_x), 0);
				WriteProcessMemory(pidconnect, (LPVOID)y_coord, &Coordinate_y, sizeof(Coordinate_y), 0);
				WriteProcessMemory(pidconnect, (LPVOID)z_coord, &Coordinate_z, sizeof(Coordinate_z), 0);


			}





		}

	}
	else {
		cout << "Window not founded" << endl;

	}
}