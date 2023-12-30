// Project_Final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bitset>

#include "Main.h"

using namespace std;
int main()
{
	uint64_t volumeSize = 1024 * 1024;
	VolumeSys vls = VolumeSys(volumeSize*10);

	string name;
	cout << "Nhập tên file : ";
	cin >> name;
	/*if (createVolume(name, (volumeSize * 10)) == true) {
		formatVolume(name, vls);
	}*/
	//cout << "Pass : " << vls.getPass() << endl;
	//VolumeSys vlsx;
	//fstream f(name);
	//vlsx.ReadVolume(f);
	//cout << "Pass of sys : " << vlsx.getPass();

	resetPass(name);
	OpenVolume(name, volumeSize * 10);
	return 0;


}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
