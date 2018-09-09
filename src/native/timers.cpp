#include "native/timers.hpp"

#include <uv.h>
#include <string>
#include <vector>
#include <sstream>

struct Timer {
	uv_timer_t handle;
	std::string name;
	uint64_t index;
	duk_context* ctx;
};

static std::vector<Timer*> timers;
static uint32_t timerIndex = 0;

static void do_timer(uv_timer_t* handle) {
	Timer* timer = (Timer*)handle->data;
	duk_push_global_stash(timer->ctx);
	duk_get_prop_string(timer->ctx, -1, timer->name.c_str());
	duk_call(timer->ctx, 0);  // TypeError if not callable / undefined
	duk_pop_2(timer->ctx);
}

static duk_ret_t native_set_timer(duk_context *ctx)
{
	// TODO: parameter validation
	duk_double_t timeout = duk_to_number(ctx, 1);
	if (timeout < 0) {
		timeout = 0;
	}

	duk_double_t interval = duk_to_number(ctx, 2);
	if (interval < 0) {
		interval = 0;
	}

	Timer* timer = new Timer();
	timer->ctx = ctx;
	timer->index = ++timerIndex; // TODO: handle timerIndex overflow?

	std::ostringstream ss;
	ss << "timer" << timer->index;

	timer->name = ss.str();

	uv_timer_init(uv_default_loop(), &timer->handle);
	uv_timer_start(&timer->handle, do_timer, (uint64_t)timeout, (uint64_t)interval);
	timer->handle.data = timer;

	duk_push_global_stash(ctx);
	duk_dup(ctx, 0);
	duk_put_prop_string(ctx, -2, timer->name.c_str()); // TODO: unset on clear
	duk_pop_2(ctx);

	timers.push_back(timer);

	duk_push_number(ctx, timer->index);
	return 1;
}

static duk_ret_t native_clear_timer(duk_context *ctx) {
	// TODO: parameter validation
	duk_double_t index = duk_to_number(ctx, 0);
	uint32_t ind = (uint32_t)index;
	if (ind == index) 
	{
		for (std::vector<Timer*>::iterator itr = timers.begin(); itr != timers.end(); ++itr)
		{
			if ((*itr)->index == ind)
			{
				uv_timer_stop(&(*itr)->handle);
				delete (*itr);
				timers.erase(itr);
				break;
			}
		}
	}

	return 0;
}

void nativeTimers(duk_context* ctx)
{
	duk_push_c_function(ctx, native_set_timer, 3);
	duk_put_global_string(ctx, "__setTimer");
	duk_push_c_function(ctx, native_clear_timer, 1);
	duk_put_global_string(ctx, "__clearTimer");
}
