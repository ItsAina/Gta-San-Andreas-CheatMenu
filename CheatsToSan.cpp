
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
#include <algorithm> 
#include <cctype>    
#include <string>

using namespace std;



template<typename Iterator1, typename Iterator2>
class ZipIterator {
public:
	using value_type = std::pair<typename std::iterator_traits<Iterator1>::value_type, typename std::iterator_traits<Iterator2>::value_type>;
	using difference_type = typename std::iterator_traits<Iterator1>::difference_type;
	using pointer = value_type*;
	using reference = value_type&;
	using iterator_category = std::forward_iterator_tag;

	ZipIterator(Iterator1 iter1, Iterator2 iter2) : it1(iter1), it2(iter2) {}

	value_type operator*() const {
		return std::make_pair(*it1, *it2);
	}

	ZipIterator& operator++() {
		++it1;
		++it2;
		return *this;
	}

	bool operator!=(const ZipIterator& other) const {
		return it1 != other.it1 || it2 != other.it2;
	}

private:
	Iterator1 it1;
	Iterator2 it2;
};

template<typename Container1, typename Container2>
class Zip {
public:
	Zip(Container1& c1, Container2& c2) : container1(c1), container2(c2) {}

	auto begin() {
		return ZipIterator<typename Container1::iterator, typename Container2::iterator>(container1.begin(), container2.begin());
	}

	auto end() {
		return ZipIterator<typename Container1::iterator, typename Container2::iterator>(container1.end(), container2.end());
	}

private:
	Container1& container1;
	Container2& container2;
};




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


void choosecheatmenumode(DWORD pid, HANDLE GetHandle) {
	vector<DWORD> offsets = { 0x540,0xB4,0x0,0x4,0xB0,0x1CC };
	vector<DWORD> locationoffsets = { 0x30,0x34,0x38 };
	//float health = *(float*)(0xB6F5F0 + 0x540);
	DWORD MoneyAddr = 0xB7F4D0;
	DWORD FatAddr = 0xB7BA54;
	DWORD StaminaAddr = 0xB7BA58;
	DWORD MuscleAddr = 0xB7BA5C;
	DWORD LungCapacityAddr = 0xB7F43C;
	DWORD MaxHealthAddr = 0xB7BA60;
	DWORD RespectAddr = 0xB7BB00;
	DWORD Inventory = 0xB7F43C;
	DWORD TimeControl = 0xB7F4D0;
	DWORD BaseAddr = getbasemoduleaddress(L"gta_sa.exe", pid);
	DWORD PlayerObj = 0x771A38;
	DWORD xaddrstatic = 0x771C70;
	DWORD yaddrstatic = 0x771A38;
	DWORD zaddrstatic = 0x771C70;
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

	DWORD minigunoffset = 0x5AC;

	void* PlayerObject = (void*)(BaseAddr + PlayerObj);
	void* xobj = (void*)(BaseAddr + xaddrstatic);
	void* yobj = (void*)(BaseAddr + yaddrstatic);
	void* zobj = (void*)(BaseAddr + zaddrstatic);
	uintptr_t Playerptr;
	uintptr_t xptr;
	uintptr_t yptr;
	uintptr_t zptr;
	float xcoord, ycoord, zcoord;


	ReadProcessMemory(GetHandle, PlayerObject, &Playerptr, sizeof(Playerptr), 0);
	ReadProcessMemory(GetHandle, xobj, &xptr, sizeof(xptr), 0);
	ReadProcessMemory(GetHandle, yobj, &zptr, sizeof(zptr), 0);
	ReadProcessMemory(GetHandle, zobj, &yptr, sizeof(yptr), 0);


	//DWORD Offset = getpointeraddress(getwindowtitle,PlayerObjectAddr,offsets);
	bool godmode = false;
	bool unbreakableshield = false;
	bool unbreakablecar = false;
	bool infiniteammo = false;
	bool overwrite = true;
	int toggle = 0;
	int toggle2 = 0;
	int money;
	int cartoggle;
	float health, armor;
	float maxhealth;
	float fatness, stamina, muscle, lung, respect;
	float currenthealth;
	uintptr_t x, y, z;
	while (true) {
		if (overwrite) {
			cout << "For toggle on godmode, press: F2\t For toggle on infinite ammo, press: F4\t For changing xyz position, press: F5\t For infinity armor, press: F6\nFor altering stats, press: F7\t For undestroyable car, press: F8\n";
			overwrite = false;
		}


		if (GetAsyncKeyState(VK_F2)) {
			godmode = not godmode;
			if (toggle == 0) {
				ReadProcessMemory(GetHandle, LPVOID(Playerptr + 0x540), &currenthealth, sizeof(currenthealth), 0);


			}
			this_thread::sleep_for(chrono::milliseconds(200));
			//cout << godmode << endl;
			if (godmode) {
				cout << currenthealth << endl;
				toggle = 1;
				cout << "God mode is toggled on" << endl;
				health = std::numeric_limits<double>::infinity();
				WriteProcessMemory(GetHandle, LPVOID(Playerptr + 0x540), &health, sizeof(health), 0);


			}

			else {
				toggle = 0;
				cout << "God mode is toggled off" << endl;
				WriteProcessMemory(GetHandle, LPVOID(Playerptr + 0x540), &currenthealth, sizeof(currenthealth), 0);
				overwrite = true;

			}

		}

		if (GetAsyncKeyState(VK_F4)) {
			infiniteammo = not infiniteammo;
			this_thread::sleep_for(chrono::milliseconds(200));
			if (infiniteammo) {
				cout << "Infinity ammo is on" << endl;
				int ammoinfinity = 1;
				WriteProcessMemory(GetHandle, LPVOID(infiniteammoaddr), &ammoinfinity, sizeof(ammoinfinity), 0);


			}

			else {
				cout << "Infinity ammo is off" << endl;
				int ammoinfinity = 0;
				WriteProcessMemory(GetHandle, LPVOID(infiniteammoaddr), &ammoinfinity, sizeof(ammoinfinity), 0);
				overwrite = true;

			}




		}

		if (GetAsyncKeyState(VK_F5)) {
			ReadProcessMemory(GetHandle, LPCVOID(xptr + 0x14), &x, sizeof(x), 0);
			ReadProcessMemory(GetHandle, LPCVOID(yptr + 0x14), &y, sizeof(y), 0);
			ReadProcessMemory(GetHandle, LPCVOID(zptr + 0x14), &z, sizeof(z), 0);
			ReadProcessMemory(GetHandle, LPCVOID(x + 0x30), &xcoord, sizeof(xcoord), 0);
			ReadProcessMemory(GetHandle, LPCVOID(x + 0x34), &ycoord, sizeof(ycoord), 0);
			ReadProcessMemory(GetHandle, LPCVOID(y + 0x38), &zcoord, sizeof(zcoord), 0);
			cout << "Your current position of:\t" << "x:" << xcoord << "\t" << "y:" << ycoord << "\t" << "z:" << zcoord << "\n";
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

		if (GetAsyncKeyState(VK_F6)) {
			unbreakableshield = not unbreakableshield;
			this_thread::sleep_for(chrono::milliseconds(500));
			//cout << godmode << endl;
			if (unbreakableshield) {
				cout << "Unbreakable armor is toggled on" << endl;
				float shield = std::numeric_limits<double>::infinity();
				WriteProcessMemory(GetHandle, LPVOID(Playerptr + 0x548), &shield, sizeof(shield), 0);
				cout << shield << endl;


			}

			else
				cout << "Unbreakable armor is toggled off" << endl;
			float shield = 100;
			WriteProcessMemory(GetHandle, LPVOID(Playerptr + 0x548), &shield, sizeof(shield), 0);
			overwrite = true;

		}




		if (GetAsyncKeyState(VK_F7)) {
			cout << "Choose, what stats you want to alter between: (muscle,stamina,maxhealth,fat,lung,money,respect,weaponskill)" << endl;
			string UserInput;
			cin >> UserInput;
			this_thread::sleep_for(chrono::milliseconds(500));
			if (toLower(UserInput) == "muscle") {
				float value;
				ReadProcessMemory(GetHandle, LPCVOID(MuscleAddr), &muscle, sizeof(muscle), 0);
				cout << "Your current muscle stat is\t" << muscle << endl;
				cout << "Type here how much to change that value?" << endl;
				cin >> value;
				float muscle = value;
				cout << "Succesfully overwrite muscle value to " << muscle << endl;
				WriteProcessMemory(GetHandle, LPVOID(MuscleAddr), &muscle, sizeof(muscle), 0);
				overwrite = true;
			}

			else if (toLower(UserInput) == "stamina") {
				float value;
				ReadProcessMemory(GetHandle, LPCVOID(StaminaAddr), &stamina, sizeof(stamina), 0);
				cout << "Your current stamina stat is\t" << stamina << endl;
				cout << "Type here how much to change that value?" << endl;
				cin >> value;
				float stamina = value;
				cout << "Succesfully overwrite stamina value to " << stamina << endl;
				WriteProcessMemory(GetHandle, LPVOID(StaminaAddr), &stamina, sizeof(stamina), 0);
				overwrite = true;
			}
			else if (toLower(UserInput) == "fat") {
				float value;
				ReadProcessMemory(GetHandle, LPCVOID(FatAddr), &fatness, sizeof(fatness), 0);
				cout << "Your current fat stat is\t" << fatness << endl;
				cout << "Type here how much to change that value?" << endl;
				cin >> value;
				float fat = value;
				cout << "Succesfully overwrite fat value to " << fat << endl;
				WriteProcessMemory(GetHandle, LPVOID(FatAddr), &fat, sizeof(fat), 0);
				overwrite = true;
			}
			else if (toLower(UserInput) == "lung") {
				float value;
				ReadProcessMemory(GetHandle, LPCVOID(LungCapacityAddr), &lung, sizeof(lung), 0);
				cout << "Your current lung stat is\t" << lung << endl;
				cout << "Type here how much to change that value?" << endl;
				cin >> value;
				float lung = value;
				cout << "Succesfully overwrite lung value to " << lung << endl;
				WriteProcessMemory(GetHandle, LPVOID(LungCapacityAddr), &lung, sizeof(lung), 0);
				overwrite = true;
			}

			else if (toLower(UserInput) == "maxhealth") {
				float value;
				ReadProcessMemory(GetHandle, LPCVOID(MaxHealthAddr), &maxhealth, sizeof(maxhealth), 0);
				cout << "Your current maxhealth stat is\t" << maxhealth << endl;
				cout << "Type here how much to change that value?" << endl;
				cin >> value;
				float maxhealth = value;
				cout << "Succesfully overwrite maxhealth value to " << maxhealth << endl;
				WriteProcessMemory(GetHandle, LPVOID(MaxHealthAddr), &maxhealth, sizeof(maxhealth), 0);
				overwrite = true;
			}


			else if (toLower(UserInput) == "money") {
				ReadProcessMemory(GetHandle, LPCVOID(MoneyAddr), &money, sizeof(money), 0);
				cout << "Your current money is\t" << "$" << money << endl;
				cout << "How much money, you want to add?" << endl;
				cin >> money;
				cout << "Succesfully overwrite money value to " << money << endl;
				WriteProcessMemory(GetHandle, LPVOID(MoneyAddr), &money, sizeof(money), 0);
				overwrite = true;

			}

			else if (toLower(UserInput) == "respect") {
				float value;
				ReadProcessMemory(GetHandle, LPCVOID(RespectAddr), &respect, sizeof(respect), 0);
				cout << "Your current respect stat is\t" << respect << endl;
				cout << "Type here how much to change that value?" << endl;
				cin >> value;
				float respect = value;
				cout << "Succesfully overwrite respect value to " << respect << endl;
				WriteProcessMemory(GetHandle, LPVOID(RespectAddr), &respect, sizeof(respect), 0);
				overwrite = true;

			}

			else if (toLower(UserInput) == "wantedlevel") {




			}

			else if (toLower(UserInput) == "neverwanted") {



			}

			else if (toLower(UserInput) == "weaponskill") {
				vector<DWORD> weaponskilladdresses = { skillpistoladdr,skillsilenecedpistoladdr,skillDeagleaddr,skillshotgunaddr,skillsawnaddr,skillcombatshotgunaddr,skillmachinepistoladdr,skillsmgaddr,skillak47addr,skillm4addr };
				float weaponskillval;
				vector<string> weapons = { "Pistol skill","Silenced pistol skill","Deagle skill","Shotgun skill","Shotgun Sawn skill","Combat Shotgun skill","Machine pistol skill","Smg pistol skill","Ak-47 skill","M4 skill" };
				string userinput;
				Zip<std::vector<DWORD>, std::vector<string>> zipped(weaponskilladdresses, weapons);

				for (const auto& pair : zipped) {
					DWORD weaponskilladdr = pair.first;
					string weapon = pair.second;
					ReadProcessMemory(GetHandle, LPCVOID(weaponskilladdr), &weaponskillval, sizeof(weaponskillval), 0);
					std::cout << "Your\t" << weapon << "\t" << weaponskillval << endl;

				}

				cout << "Choose, what weaponskill you want to alter between : (pistol, silencedpistol, deagle, shotgun, sawn, combatshotgun, machinepistol, smg,ak-47,m4)" << endl;
				cin >> userinput;

				const float weaponskillmax = 1000;
				if (toLower(userinput) == "all") {

					for (DWORD weaponskilladdr : weaponskilladdresses) {
						WriteProcessMemory(GetHandle, LPVOID(weaponskilladdr), &weaponskillmax, sizeof(weaponskillmax), 0);
						cout << "All weapon skills are maximized" << endl;
						overwrite = true;
					}


				}

				else if (toLower(userinput) == "pistol") {
					WriteProcessMemory(GetHandle, LPVOID(skillpistoladdr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of pistol" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "silencedpistol") {
					WriteProcessMemory(GetHandle, LPVOID(skillsilenecedpistoladdr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of silencedpistol" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "deagle") {
					WriteProcessMemory(GetHandle, LPVOID(skillDeagleaddr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of deagle" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "shotgun") {
					WriteProcessMemory(GetHandle, LPVOID(skillshotgunaddr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of shotgun" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "sawnshotgun") {
					WriteProcessMemory(GetHandle, LPVOID(skillsawnaddr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of sawnshotgun" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "combatshotgun") {
					WriteProcessMemory(GetHandle, LPVOID(skillcombatshotgunaddr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of combatshotgun" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "machinepistol") {
					WriteProcessMemory(GetHandle, LPVOID(skillmachinepistoladdr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of machinepistol" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "smg") {
					WriteProcessMemory(GetHandle, LPVOID(skillsmgaddr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of smg" << endl;
					overwrite = true;
				}

				else if ((toLower(userinput) == "ak47") or (toLower(userinput) == "ak-47")) {
					WriteProcessMemory(GetHandle, LPVOID(skillak47addr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of ak-47" << endl;
					overwrite = true;
				}

				else if (toLower(userinput) == "m4") {
					WriteProcessMemory(GetHandle, LPVOID(skillm4addr), &weaponskillmax, sizeof(weaponskillmax), 0);
					cout << "Succesfully maximize weapon skill of m4" << endl;
					overwrite = true;
				}
				/*for () {
					ReadProcessMemory();
					cout << "Your current muscle stat is" << muscle << endl;
				}*/
			}


			/*else if (toLower(UserInput) == "driveskill") {
				ReadProcessMemory();
				cout << "Your current muscle stat is" << muscle << endl; */

				//}






			//}


			/*if (GetAsyncKeyState(VK_F4)) {


			}

			if (GetAsyncKeyState(VK_F5)) {



			}*/



			//}
		}

		if (GetAsyncKeyState(VK_F8)) {
			int invinciblecar;
			unbreakablecar = not unbreakablecar;
			if (toggle2 == 0) {
				ReadProcessMemory(GetHandle, LPVOID(Unbreakablecar), &invinciblecar, sizeof(invinciblecar), 0);


			}
			this_thread::sleep_for(chrono::milliseconds(200));
			//cout << godmode << endl;
			if (unbreakablecar || invinciblecar==1) {
				toggle2 = 1;
				cout << "Invincible car is toggled on" << endl;
				WriteProcessMemory(GetHandle, LPVOID(Unbreakablecar),&toggle2,sizeof(toggle2),0);


			}

			else if (unbreakablecar || invinciblecar == 0) {
				toggle2 = 0;
				cout << "Invincible car is toggled off" << endl;
				WriteProcessMemory(GetHandle, LPVOID(Unbreakablecar), &toggle2, sizeof(toggle2), 0);
				overwrite = true;

			}


		}
	}

}


int main() {
	HWND getwindowtitle = FindWindowA(0, "GTA: San Andreas");
	if (not getwindowtitle == 0) {
		cout << "Window found" << endl;

	}

	else {
		return 1;


	}

	DWORD pid;
	GetWindowThreadProcessId(getwindowtitle, &pid);
	HANDLE GetHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	choosecheatmenumode(pid, GetHandle);
	/*DWORD FatAddress = 0xB793D4;
	DWORD x = 0x14;
	DWORD y = 0x0;
	DWORD z = 0x2C;
	DWORD playerptr = 0xB7CD98;
	DWORD playerptrhealth = playerptr + x;*/






}
