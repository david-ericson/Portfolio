#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <ExportHeader.h>
//#include "Core.h"

namespace Engine
{
	// your stuff goes here...
	// use ENGINE_SHARED to indicate a function or class that you want to export
	ENGINE_SHARED void Init(void(updateMethod)(void));
	void callUpdate();
	ENGINE_SHARED bool sampleFunctionThatReturnsTrue();
	ENGINE_SHARED void shutdown();
}

#endif // _ENGINE_H_