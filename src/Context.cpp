#include "Context.hpp"
#include "ts.hpp"
#include <fstream>

static duk_context* dukPrimaryHeap = nullptr;

static duk_ret_t print(duk_context *ctx)
{
	printf("%s\n", duk_to_string(ctx, 0));
	return 0;
}

static void fatal(void *udata, const char *msg)
{
	fprintf(stderr, "*** FATAL ERROR: %s\n", (msg ? msg : "no message"));
	fflush(stderr);
	abort();
}

Context* Context::create()
{
	if (!dukPrimaryHeap)
	{
		dukPrimaryHeap = duk_create_heap(0, 0, 0, 0, fatal); // TODO: cleanup?
	}
	duk_push_thread_new_globalenv(dukPrimaryHeap); // TODO: cleanup?
	duk_context* ctx = duk_get_context(dukPrimaryHeap, -1);
	duk_push_c_function(ctx, print, 1);
	duk_put_global_string(ctx, "print");
	return new Context(ctx);
}

Context::Context(duk_context* dukContext) :
	mDukContext(dukContext)
{
}

bool Context::runFile(const std::string& file)
{
	duk_push_string(mDukContext, file.c_str());
	duk_put_global_string(mDukContext, "__filename");
	std::ifstream ifs(file); // TODO: error checks for file
	if (!ifs.is_open())
	{
		return false;
	}
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	content = ts::transpile(content);
	duk_eval_string_noresult(mDukContext, content.c_str());
	return true;
}

void Context::runCode(const std::string& code)
{
	std::string content = ts::transpile(code);
	duk_eval_string_noresult(mDukContext, content.c_str());
}
