#pragma once

#include "pch.h"

#ifdef _DEBUG

	#define CONSOLE_LOG_ERROR(src, msg) std::cout << "ERROR(" << src << "): " << msg << "!" << std::endl
	#define CONSOLE_LOG_WARNING(src, msg) std::cout << "WARNING(" << src << "): " << msg << "!" << std::endl
	// TODO: file logs
	#define FILE_LOG_ERROR(src, msg) __file_log__("ERROR", src, msg)
	#define FILE_LOG_WARNING(src, msg) __file_log__("WARNING", src, msg)

	void __file_log__(const char* type, const char* src, const char* msg)
	{
		std::ofstream file;
		file.open("../DebugLog.txt", std::ios::app);
		if (file.is_open())
		{
			file << type << "(" << src << "): " << msg << "!\n";
		}
		file.close();
	}

#else

	#define CONSOLE_LOG_ERROR(src, msg)
	#define CONSOLE_LOG_WARNING(src, msg)
	#define FILE_LOG_ERROR(src, msg)
	#define FILE_LOG_WARNING(src, msg)

#endif