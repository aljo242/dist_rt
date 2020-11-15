#ifndef _TIMER_H
#define _TIMER_H
#include <chrono>

class Timer
{
	// methods
public:
	Timer();
	void Start();
	uint64_t Stop();

private:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point stop;
};

#endif // _TIMER_H