#include "Profiler.h"

#ifdef PROFILING_ON
#include "Assert.h"
#include <iostream>
#include <fstream>
#endif
using types::uint;

namespace Profiling
{

	Profiler Profiler::theInstance;

	Profiler& Profiler::getInstance()
	{
		return theInstance;
	}

#ifdef PROFILING_ON




	static std::ofstream outStream;

	void Profiler::addEntry(const char* category, float time)
	{
		ASSERT(categoryIndex < MAX_PROFILE_CATEGORIES, "The profiler's category index was larger than the maximum number of categories");
		ProfileCategory& pc = categories[categoryIndex];

		if(frameIndex == 0)
		{
			pc.name = category;
			numUsedCategories++;
		}
		else
		{
			ASSERT((pc.name == category && category != NULL), "The profiler's pc.name wasn't equal to category and category may be NULL" );
			ASSERT((categoryIndex < numUsedCategories),"The profiler's category index is greater than or equal to the number of used categories");
		}
		categoryIndex++;
		pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
	}

	void Profiler::newFrame()
	{
		if(frameIndex > 0)
		{
			ASSERT((categoryIndex == numUsedCategories), "The profiler's category index was not equal to the number of used categores");
		}
		frameIndex++;
		categoryIndex = 0;
	}

	void Profiler::initialize(const char* fileName)
	{
		this->fileName = fileName;
		frameIndex = -1;
		categoryIndex = 0;
		numUsedCategories = 0;
	}

	void Profiler::shutdown()
	{
		writeData();
	}

	char Profiler::getDelimiter(uint index) const
	{
		return ((index+1) < numUsedCategories) ? ',' : '\n';
	}

	bool Profiler::wrapped() const
	{
		return (frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1);
	}

	void Profiler::writeData() const
	{
		outStream.open(fileName, std::ios::trunc);

		//Write category headers
		for(uint i=0;i< numUsedCategories; i++)
		{
			outStream << categories[i].name;
			outStream << getDelimiter(i);
		}

		//Account for last frame if they added entries


		uint endIndex;
		uint startIndex;
		if(wrapped())
		{
			endIndex = frameIndex % MAX_FRAME_SAMPLES;
			startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
			while(startIndex != endIndex)
			{
				writeFrame(startIndex);
				startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
			}
			if(currentFrameComplete())
			{
				writeFrame(startIndex);
			}
		}
		else
		{
			uint numActualFrames = frameIndex;
			if(currentFrameComplete())
			{
				numActualFrames++;
			}
			startIndex = 0;
			endIndex = numActualFrames;
			while(startIndex < endIndex)
			{
				writeFrame(startIndex++);
			}
		}
		outStream.close();
	}

	bool Profiler::currentFrameComplete() const
	{
		return categoryIndex == numUsedCategories;
	}

	void Profiler::writeFrame(uint frameNumber) const
	{
		for(uint category = 0; category < numUsedCategories; category++)
		{
			outStream << categories[category].samples[frameNumber];
			outStream << getDelimiter(category);
		}
	}

	
#endif // PROFILING_ON
}
