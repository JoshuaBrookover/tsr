#include "Context.hpp"
#include <iostream>
#include <uv.h>

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

	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	uv_loop_close(uv_default_loop());

	return 0;
}
