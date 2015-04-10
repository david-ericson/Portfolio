#include "ProfileManager.h"

ProfileManager::ProfileManager()
{
	profiledFile.open("profiler.csv");
}

ProfileManager::~ProfileManager()
{

}

void ProfileManager::storeSample(const char* name, LARGE_INTEGER time)
{
	if(profiledFile)
	{
		profiledFile << name;
		profiledFile << "," << time.QuadPart;
	}
}