#include "native/require.hpp"
#include "Context.hpp"
#include "util/path.hpp"

#include <path.ts.h>

#include <string>
#include <fstream>
#include <iostream>

static duk_ret_t native_require(duk_context *ctx)
{
	std::string query = duk_to_string(ctx, 0);
	if (query == "path")
	{
		Context* context = Context::create();
		context->runCode((const char*)path_ts);
		duk_context* duk = context->getDukContext();
		duk_get_global_string(duk, "module");
		duk_get_prop_string(duk, -1, "exports");
		duk_xmove_top(ctx, duk, 1);
		duk_pop(duk);
	}
	else
	{
		duk_get_global_string(ctx, "__dirname");
		std::string dirname = duk_get_string(ctx, -1);
		duk_pop(ctx);
		std::string filename = path::join(dirname, duk_to_string(ctx, 0)) + ".ts";
		Context* context = Context::create();
		if (!context->runFile(filename)) {
			std::cerr << "Failed to load file: " << filename << std::endl;
		}
		duk_context* duk = context->getDukContext();
		duk_get_global_string(duk, "module");
		duk_get_prop_string(duk, -1, "exports");
		duk_xmove_top(ctx, duk, 1);
		duk_pop(duk);
	}
	return 1;
}

void nativeRequire(duk_context* ctx)
{
	duk_push_c_function(ctx, native_require, 1);
	duk_put_global_string(ctx, "__require");
	duk_push_object(ctx);
	duk_push_object(ctx);
	duk_put_prop_string(ctx, -2, "exports");
	duk_put_global_string(ctx, "module");
	duk_get_global_string(ctx, "module");
	duk_get_prop_string(ctx, -1, "exports");
	duk_put_global_string(ctx, "exports");
	duk_pop(ctx);
}
