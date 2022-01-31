#pragma once

namespace utils
{
	//Non-negative modulo
	const inline int loopMod(const int dividend, const int divisor)
	{
		return (dividend % divisor + divisor) % divisor;
	}
}