#include "Context.hpp"
#include <fstream>

#include "native/require.hpp"
#include "native/timers.hpp"

#include "util/path.hpp"
#include "util/ts.hpp"

#include <console.duk.h>
#include <promise.duk.h>
#include <require.duk.h>
#include <timers.duk.h>
#include <util.duk.h>

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
		duk_push_object(dukPrimaryHeap);
		duk_put_global_string(dukPrimaryHeap, "global");
	}
	duk_push_thread_new_globalenv(dukPrimaryHeap); // TODO: cleanup?
	duk_context* ctx = duk_get_context(dukPrimaryHeap, -1);
	duk_push_c_function(ctx, print, 1);
	duk_put_global_string(ctx, "print");
	duk_get_global_string(dukPrimaryHeap, "global");
	duk_xmove_top(ctx, dukPrimaryHeap, 1);
	duk_put_global_string(ctx, "global");
	Context* context = new Context(ctx);
	nativeRequire(ctx);
	nativeTimers(ctx);
	context->runPrecompiled(util_duk, util_duk_len);
	context->runPrecompiled(console_duk, console_duk_len);
	context->runPrecompiled(require_duk, require_duk_len);
	context->runPrecompiled(timers_duk, timers_duk_len);
	context->runPrecompiled(promise_duk, promise_duk_len);
	return context;
}

Context::Context(duk_context* dukContext) :
	mDukContext(dukContext)
{
}

bool Context::runFile(const std::string& file)
{
	std::string filename = file;
	if (!path::isAbsolute(filename)) {
		filename = path::resolve(file);
	}
	duk_push_string(mDukContext, path::dirname(filename).c_str());
	duk_put_global_string(mDukContext, "__dirname");
	duk_push_string(mDukContext, filename.c_str());
	duk_put_global_string(mDukContext, "__filename");
	std::ifstream ifs(filename); // TODO: error checks for file
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

void Context::runPrecompiled(const unsigned char* buffer, unsigned int len)
{
	void *pp;
	pp = duk_push_buffer(mDukContext, len, 0);
	memcpy(pp, buffer, len);
	duk_load_function(mDukContext);
	duk_call(mDukContext, 0);
}

duk_context* Context::getDukContext() const
{
	return mDukContext;
}
