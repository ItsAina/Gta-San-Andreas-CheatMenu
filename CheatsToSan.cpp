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

std::string toLower(const std::string& str) {
	std::string lowerStr = str; // Make a copy of the input string
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return lowerStr;
}


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
	DWORD MoneyAddr = 0xB7F4D0;
	DWORD FatAddr = 0xB7BA54;
	DWORD StaminaAddr = 0xB7BA58;
	DWORD MuscleAddr = 0xB7BA5C;
	DWORD LungCapacityAddr = 0xB7F43C;
	DWORD MaxHealthAddr = 0xB7A60;
	DWORD RespectAddr = 
	DWORD Inventory = 0xB7F43C;
	DWORD TimeControl = 0xB7F4D0;
	DWORD BaseAddr = getbasemoduleaddress(L"gta_sa.exe", pid);
	DWORD PlayerObj = 0x771A38;
	DWORD xaddr = 0x771C70;
	DWORD yaddr = 0x771A38;
	DWORD zaddr = 0x771C70;
	DWORD skillpistol = 0xB7BB14;
	DWORD skillsilenecedpistol = 0xB7BB18;
	DWORD skillDeagle = 0xB7BB1C;
	DWORD skillshotgun = 0xB7BB20;
	DWORD skillsawn = 0xB7BB24;
	DWORD skillcombatshotgun = 0xB7BB28;
	DWORD skillmachinepistol = 0xB7BB2C;
	DWORD skillsmg = 0xB7BB30;
	DWORD skillak47 = 0xB7BB34;
	DWORD skillm4 = 0xB7BB38;
	DWORD SpawnRom = 0xB7B6C4;



	void* PlayerObject = (void*)(BaseAddr + PlayerObj);
	void* xobj = (void*)(BaseAddr + xaddr);
	void* yobj = (void*)(BaseAddr + yaddr);
	void* zobj = (void*)(BaseAddr + zaddr);
	uintptr_t Playerptr;
	uintptr_t xptr;
	uintptr_t yptr;
	uintptr_t zptr;

	ReadProcessMemory(GetHandle, PlayerObject, &Playerptr, sizeof(Playerptr), 0);
	ReadProcessMemory(GetHandle, xobj, &xptr, sizeof(xptr), 0);
	ReadProcessMemory(GetHandle, yobj, &zptr, sizeof(zptr), 0);
	ReadProcessMemory(GetHandle, zobj, &yptr, sizeof(yptr), 0);

	
	//DWORD Offset = getpointeraddress(getwindowtitle,PlayerObjectAddr,offsets);
	bool godmode = false;
	int money;
	float health, armor;
	float maxhealth;
	float fatness,stamina,muscle,lung,respect;
	float x, y, z;
	cout << "For toggle on godmode press: F2\t For changing money press: F4\nFor changing xyz position press: F5\t For infinity armor press: F6\nFor altering stats press: F7\t For toggle on aimbot press: F8\n ";
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
	
		if (GetAsyncKeyState(VK_F5)) {
			ReadProcessMemory(GetHandle, LPCVOID(xptr + 0x30), &x, sizeof(x), 0);
			ReadProcessMemory(GetHandle, LPCVOID(yptr + 0x34), &y, sizeof(y), 0);
			ReadProcessMemory(GetHandle, LPCVOID(zptr + 0x38), &z, sizeof(z), 0);
			cout <<"Your current position of:\t" << "x:" << x << "\t" << "y:" << y << "\t" << "z:" << z << "\n";
			cout << "Add coordinates for x" << endl;
			cin >> x;
			cout << "Add coordinates for y" << endl;
			cin >> y;
			cout << "Add coordinates for z" << endl;
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

		if (GetAsyncKeyState(VK_F7)) {
			//cout << ""
			string UserInput;
			cin >> UserInput;
			this_thread::sleep_for(chrono::milliseconds(500));
			if (toLower(UserInput) == "muscle") {
				ReadProcessMemory(GetHandle, LPCVOID(MuscleAddr), &muscle, sizeof(muscle), 0);
				cout << "Your current muscle stat is" << muscle << endl;

			}

			else if (toLower(UserInput) == "stamina") {
				ReadProcessMemory(GetHandle,LPCVOID(StaminaAddr), &stamina, sizeof(stamina), 0);
				cout << "Your current stamina stat is" << muscle << endl;

			}
			else if (toLower(UserInput) == "fat") {
				ReadProcessMemory(GetHandle, LPCVOID(FatAddr), &fatness, sizeof(fatness), 0);
				cout << "Your current fat stat is" << muscle << endl;

			}
			else if (toLower(UserInput) == "lung") {
				ReadProcessMemory(GetHandle, LPCVOID(LungCapacityAddr), &lung, sizeof(lung), 0);
				cout << "Your current lung stat is" << muscle << endl;
			}

			else if (toLower(UserInput) == "maxhealth") {
				ReadProcessMemory(GetHandle, LPCVOID(MaxHealthAddr), &maxhealth, sizeof(maxhealth), 0);
				cout << "Your current maxhealth stat is" << muscle << endl;

			}


			else if (toLower(UserInput) == "money") {
				ReadProcessMemory(GetHandle, LPCVOID(MoneyAddr), &money, sizeof(money), 0);
				cout << "Your current money is" << "$" << money << endl;
				cout << "How much money, you want to add?" << endl;
				cin >> money;
				WriteProcessMemory(GetHandle, LPVOID(MoneyAddr), &money, sizeof(money), 0);

			}

			else if (toLower(UserInput) == "respect") {
				ReadProcessMemory(GetHandle, LPCVOID();
				cout << "Your current respect stat is" << muscle << endl;

			}

			/*	else if (toLower(UserInput) == "weaponskill") {
					ReadProcessMemory();
					cout << "Your current muscle stat is" << muscle << endl;

				}

				else if (toLower(UserInput) == "driveskill") {
					ReadProcessMemory();
					cout << "Your current muscle stat is" << muscle << endl;*/

			//}






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
