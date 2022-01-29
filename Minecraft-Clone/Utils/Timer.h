#pragma once

#include <chrono>
#include <functional>

namespace utils
{

	using TimePoint = std::chrono::high_resolution_clock::time_point;
	using Milliseconds = std::chrono::milliseconds;
	using Seconds = std::chrono::seconds;

	template<class T>
	using DoubleIfTValidTime = std::enable_if_t<std::is_same<T, Milliseconds>::value || std::is_same<T, Seconds>::value, double>;

	const static inline double millisecondsToSeconds(double milli)
	{
		return milli / 1000.0;
	}

	const static inline double secondsToMilliseconds(double seconds)
	{
		return seconds * 1000.0;
	}

	const static TimePoint getTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	template<class T>
	const static DoubleIfTValidTime<T> getElapsedTime(const TimePoint start, const TimePoint end)
	{
		return std::chrono::duration_cast<T>(end - start).count();
	}

	template<class T>
	const static DoubleIfTValidTime<T> getElapsedTime(std::function<void()> func)
	{
		TimePoint start = std::chrono::high_resolution_clock::now();
		func();
		TimePoint end = std::chrono::high_resolution_clock::now();

		return std::chrono::duration_cast<T>(end - start).count();
	}

}