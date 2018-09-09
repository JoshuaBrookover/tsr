#include "ts.hpp"
#include <ts.js.h>
#include <duktape.h>

void loadTypescript(duk_context* ctx);

duk_context* ctx = nullptr;

void ts::initialize()
{
	if (!ctx)
	{
		ctx = duk_create_heap(0, 0, 0, 0, 0);
		duk_push_object(ctx);
		duk_push_object(ctx);
		duk_put_prop_string(ctx, -2, "exports");
		duk_put_global_string(ctx, "module");
		loadTypescript(ctx);
		duk_eval_string_noresult(ctx, (char*)ts_js);
	}
}

void ts::cleanup()
{
	if (ctx)
	{
		duk_destroy_heap(ctx);
		ctx = nullptr;
	}
}

std::string ts::transpile(const std::string& code)
{
	ts::initialize();
	duk_get_global_string(ctx, "transpile");
	duk_push_string(ctx, code.c_str());
	std::string result = "";
	if (duk_pcall(ctx, 1) != 0)
	{
		printf("Error: %s\n", duk_safe_to_string(ctx, -1));
		throw "error";
	}
	else
	{
		result = duk_safe_to_string(ctx, -1);
	}
	duk_pop(ctx);
	return result;
}
