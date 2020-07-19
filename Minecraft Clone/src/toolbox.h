#pragma once

#include <string>
#include <fstream>
#include <chrono>

#include "Logger.h"

namespace toolbox
{
	typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

	std::string readFile(const char* src);

	float clampFloat(float val, float min, float max);

	float cycleClampFloat(float val, float min, float max);

	int flatten3DIndex(int x, int y, int z, int w, int h);

	TimePoint getCurrentTime();

	double getElapsedTime(TimePoint start, TimePoint end);

}