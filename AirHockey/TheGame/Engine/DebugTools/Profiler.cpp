#include <DebugTools\Profiler.h>

#ifdef PROFILING_ON
#include <DebugTools\AssertExpression.h>
#include <iostream>
#include <fstream>
#endif

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
		ASSERT_EXP(categoryIndex < MAX_PROFILE_CATEGORIES, "The profiler's category index was larger than the maximum number of categories");
		ProfileCategory& pc = categories[categoryIndex];

		if(frameIndex == 0)
		{
			pc.name = category;
			numUsedCategories++;
		}
		else
		{
			ASSERT_EXP((pc.name == category && category != NULL), "The profiler's pc.name wasn't equal to category and category may be NULL" );
			ASSERT_EXP((categoryIndex < numUsedCategories),"The profiler's category index is greater than or equal to the number of used categories");
		}
		categoryIndex++;
		pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
	}

	void Profiler::newFrame()
	{
		if(frameIndex > 0)
		{
			ASSERT_EXP((categoryIndex == numUsedCategories), "The profiler's category index was not equal to the number of used categores");
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

	char Profiler::getDelimiter(unsigned int index) const
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
		for(unsigned int i=0;i< numUsedCategories; i++)
		{
			outStream << categories[i].name;
			outStream << getDelimiter(i);
		}

		//Account for last frame if they added entries


		unsigned int endIndex;
		unsigned int startIndex;
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
			unsigned int numActualFrames = frameIndex;
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

	void Profiler::writeFrame(unsigned int frameNumber) const
	{
		for(unsigned int category = 0; category < numUsedCategories; category++)
		{
			outStream << categories[category].samples[frameNumber];
			outStream << getDelimiter(category);
		}
	}

	
#endif // PROFILING_ON
}
