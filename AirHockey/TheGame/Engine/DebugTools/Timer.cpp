#include <DebugTools\Timer.h>

float deltaT;

float Timer::LIToSecs(LARGE_INTEGER & L)
{
	return ((float)L.QuadPart / (float)frequency.QuadPart);
}

Timer::Timer()
{
	timer.start.QuadPart=0;
	timer.stop.QuadPart=0;
	QueryPerformanceFrequency (&frequency);
}

void Timer::startTimer()
{
	QueryPerformanceCounter(&timer.start);	
}

float Timer::stopTimer()
{
	QueryPerformanceCounter(&timer.stop);
	return LIToSecs(timer.stop);
}

float Timer::getLastTimeInterval() {
	LARGE_INTEGER time;
	stopTimer();
	time.QuadPart = (timer.stop.QuadPart - timer.start.QuadPart);
	startTimer();
	return LIToSecs(time);
}

float Timer::getLastTimeIntervalDT() {
	LARGE_INTEGER time;
	stopTimer();
	time.QuadPart = (timer.stop.QuadPart - timer.start.QuadPart);
	startTimer();
	deltaT = LIToSecs(time);
	deltaT = (deltaT > .2f)?.033f:deltaT;
	return deltaT;
}

float Timer::dt()
{
	return deltaT;
}