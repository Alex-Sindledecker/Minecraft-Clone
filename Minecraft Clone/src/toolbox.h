#pragma once

#include <string>
#include <fstream>
#include <chrono>

#include "Logger.h"

namespace toolbox
{
	typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

	static std::string readFile(const char* src)
	{
		std::string content = "";
		std::ifstream file;
		file.open(src);
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				content += line + '\n';
			}
		}
		else
		{
			CONSOLE_LOG_ERROR("toolbox.h", "Failed to open file " << src);
		}
		file.close();
		return content;
	}

	static float clampFloat(float val, float min, float max)
	{
		if (val > max)
			return max;
		if (val < min)
			return min;
		return val;
	}

	static float cycleClampFloat(float val, float min, float max)
	{
		if (val > max)
			return min;
		if (val < min)
			return max;
		return val;
	}

	static TimePoint getCurrentTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	static double getElapsedTime(TimePoint start, TimePoint end)
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)1000000000;
	}

}