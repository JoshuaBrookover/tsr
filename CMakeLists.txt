cmake_minimum_required( VERSION 3.0 )
add_subdirectory( deps )
add_subdirectory( tools )

duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/deps/typescript/typescript.js OUT typescript.duk.h NULL VARIABLE typescript_duk )
toh( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/ts.js OUT ts.js.h NULL VARIABLE ts_js )
toh( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/timers.js OUT timers.js.h NULL VARIABLE timers_js )
toh( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/promise.js OUT promise.js.h NULL VARIABLE promise_js )
add_executable(
	tsr
	typescript.duk.h
	ts.js.h
	timers.js.h
	promise.js.h
	src/main.cpp
	src/ts.cpp
	src/ts.duk.cpp
	src/Context.cpp
	src/native/timers.cpp
)
target_link_libraries( tsr PUBLIC duktape uv_a )
target_include_directories( tsr PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )
