#pragma once
#include <DebugTools\Logger.h>

#define  ASSERT_EXP(expression,...) do { if(!(expression)) { LOG(Severe, #expression##" "##__VA_ARGS__); Logger::shutDown(); exit(1); } } while(0,0)
