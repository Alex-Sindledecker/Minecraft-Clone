#pragma once

#include <string>
#include <fstream>

#include "Logger.h"

namespace toolbox
{

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

}