add_library( duktape STATIC duktape/duktape.c )
target_include_directories( duktape PUBLIC duktape )

add_subdirectory( libuv )
target_include_directories( uv_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libuv/include )
