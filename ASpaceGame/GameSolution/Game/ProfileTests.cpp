#include "Profiler.h"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;
using Profiling::Profiler;

namespace
{
	char* categories[] = 
	{
		"Category1",
		"Category2",
		"Category3"
	};
	const char* const PROFILE_FILE_NAME = "profiles.csv";
	const unsigned int NUM_CATEGORIES = sizeof(categories) / sizeof(*categories);
	const unsigned int NUM_FRAMES = 5;
}

string getNextToken(ifstream& theFile)
{
	char c;
	string ret;
	while(theFile.good())
	{
		theFile >> std::noskipws;
		theFile >> c;
		if(c == ',' || c == '\n')
			break;
		ret += c;
	}
	return ret;
}

void writeFrames(unsigned int numFrames)
{
	float sampleNumber = 0;
	for(float frame = 0; frame< numFrames; frame++)
	{
		profiler.newFrame();
		for(unsigned int cat = 0; cat < NUM_CATEGORIES; cat++)
		{
			profiler.addEntry(categories[cat], sampleNumber++);
		}
	}
}

TEST(Profiler, SampleProfiles)
{
	profiler.initialize(PROFILE_FILE_NAME);
	writeFrames();
	profiler.shutdown();
	checkFrames();
}

bool isAtEndOfFile(ifstream& input)
{
	if(! input.good())
		return false;
	char bitBucket;
	input >> bitBucket;
	return !input.good();
}

void checkFrames(unsigned int numFrames, bool excludeLastFrame = false)
{
	ifstream input(PROFILE_FILE_NAME);

	for(unsigned int i=0; i< NUM_CATEGORIES; i++)
	{
		EXPECT_EQ(getNextToken(input), categories[i]);
	}

	unsigned int profileNumber = 0;

	if(numFrames >= Profiler::MAX_FRAME_SAMPLES)
	{
		profileNumber = (numFrames - Profiler::MAX_FRAME_SAMPLES)*NUM_CATEGORIES;
		numFrames = Profiler::MAX_FRAME_SAMPLES;
	}
	if(excludeLastFrame)
	{
		profileNumber += NUM_CATEGORIES;
		numFrames--;
	}

	for(unsigned int i=0; i< (numFrames * NUM_CATEGORIES); i++)
	{
		string buf = getNextToken(input);
		EXPECT_EQ(atoi(buf.c_str()), profileNumber++);
	}
	EXPECT_TRUE(isAtEndOfFile(input));
}

void runTestsOnFrames(unsigned int numFrames)
{
	profiler.initialize(PROFILE_FILE_NAME);
	writeFrames(numFrames);
	profiler.shutdown();
	checkFrames(numFrames);
}

TEST(Profiler, SmallAmountOfFrames)
{
	runTestsonFrames(5);
	/*profiler.initialize(PROFILE_FILE_NAME);
	const unsigned int NUM_FRAMES_THIS_TEST = 5;
	writeFrames(NUM_FRAMES_THIS_TEST);
	profiler.shutdown();
	checkFrames(NUM_FRAMES_THIS_TEST);*/
}

TEST(Profiler, LargeAmountOfFramesNonCircular)
{
	const unsigned int NUM_FRAMES_THIS_TEST = 
		static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * .8);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profiler, ArrayBoundaries)
{
	const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES;
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);

	const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES + 1;
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);

	const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES + 2;
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profiler, CirulatingOnePlusSome)
{
	const unsigned int NUM_FRAMES_THIS_TEST = 
		static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * 1.5);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profile, GOAroundSeveralTimes)
{
	const unsigned int NUM_FRAMES_THIS_TEST = 
		static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * 3.14159);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

void writeIncompleteFrames(unsigned int numFrames)
{
	bool wrapped = numFrames >= Profiler::MAX_FRAME_SAMPLES;
	profiler.initialize(PROFILE_FILE_NAME);
	writeFrames(numFrames);
	profiler.newFrame();
	profiler.addEntry(categories[0], 15);
	profiler.shutdown();
	checkFrames(numFrames, wrapped);

	profiler.initialize(PROFILE_FILE_NAME);
	writeFrames(numFrames);
	profiler.newFrame();
	profiler.addEntry(categories[0], 15);
	profiler.addEntry(categories[1], 16);
	profiler.shutdown();
	checkFrames(numFrames, wrapped);
}

TEST(Profiler, ExcludeIncompleteFrames)
{	
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES - 2); // Not wrap
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES + 2); // Wrap
}