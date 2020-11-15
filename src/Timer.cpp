#include "Timer.h"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	using namespace std::chrono;
	start = std::chrono::high_resolution_clock::now();
}

uint64_t Timer::Stop()
{
	using namespace std::chrono;
	stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	return static_cast<uint64_t>(duration.count());
}