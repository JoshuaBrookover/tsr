#pragma once
#include <string>
namespace toh
{
	struct Options
	{
		bool null;
		std::string variable;
		Options();
	};
	std::string convert(const char* buffer, size_t length, const toh::Options& options);
}
