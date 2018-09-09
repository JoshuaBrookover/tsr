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
	void runPrecompiled(const unsigned char* buffer, unsigned int len);

	duk_context* getDukContext() const;
private:
	duk_context* mDukContext;
};
