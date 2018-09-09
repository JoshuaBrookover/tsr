#include <duktape.h>
#include <typescript.duk.h>
void loadTypescript(duk_context* ctx)
{
	void *pp;
	pp = duk_push_buffer(ctx, typescript_duk_len, 0);
	memcpy(pp, typescript_duk, typescript_duk_len);
	duk_load_function(ctx);
	duk_call(ctx, 0);
}
