#pragma once
#include <DebugTools\TypeDefs.h>

namespace Profiling
{

	class __declspec(dllexport) Profiler
	{
	public:
		static const unsigned int MAX_FRAME_SAMPLES = 500;
		static Profiler& getInstance();
	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiling::Profiler theInstance;
#if PROFILING_ON
		const char* fileName;
		static const unsigned int MAX_PROFILE_CATEGORIES = 20;
		int frameIndex;
		unsigned int categoryIndex;
		unsigned int numUsedCategories;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];
		void writeData() const;
		void writeFrame(unsigned int frameNumber) const;
		char getDelimiter(unsigned int index) const;
		bool currentFrameComplete() const;
		bool wrapped() const;
#endif

	public:
#if PROFILING_ON
		void addEntry(const char* category, float time);
		void newFrame();
		void initialize(const char* fileName);
		void shutdown();
#else
		void addEntry(const char* , float ) {}
		void newFrame() {}
		void initialize(const char* ) {}
		void shutdown() {}
#endif
	};

#define profiler Profiling::Profiler::getInstance()
}