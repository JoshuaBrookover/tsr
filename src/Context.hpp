#pragma once

#include <string>
#include <duktape.h>

class Context
{
public:
	static Context* create();
	Context(duk_context* dukContext);

	bool runFile(const std::string& file);
	void runCode(const std::string& code);
private:
	duk_context* mDukContext;
};
