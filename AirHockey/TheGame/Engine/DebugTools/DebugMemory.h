#pragma once
#include <crtdbg.h>

#ifdef DEBUG

	#define DEBUG_NEW  new(_CLIENT_BLOCK,__FILE__,__LINE__)

	#define new DEBUG_NEW

#endif //Debug