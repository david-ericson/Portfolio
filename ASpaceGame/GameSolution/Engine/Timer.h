#pragma once
#include <Windows.h>

typedef struct {
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
} stopWatch;

class __declspec(dllexport) Timer {
	stopWatch timer;
	LARGE_INTEGER frequency;
	float LIToSecs( LARGE_INTEGER & L);
public:
	Timer();
	void startTimer();
	float stopTimer();
	float getLastTimeInterval();
};