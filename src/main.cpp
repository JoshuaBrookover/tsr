#include "Context.hpp"
#include "ts.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return -1;
	}
	Context* context = Context::create();
	if (!context->runFile(argv[1]))
	{
		std::cerr << "Failed to read file: " << argv[1] << std::endl;
		return -1;
	}
	return 0;
}
