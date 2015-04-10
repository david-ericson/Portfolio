#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

ofstream profiledFile;

class ProfileManager
{
	ProfileManager();
	~ProfileManager();
	void storeSample(const char* name, LARGE_INTEGER time);
};