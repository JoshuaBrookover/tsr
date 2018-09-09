#pragma once

#include <string>

namespace ts
{
	void initialize();
	void cleanup();

	std::string transpile(const std::string& code);
}
