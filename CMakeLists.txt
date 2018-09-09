cmake_minimum_required( VERSION 3.0 )
add_subdirectory( deps )
add_subdirectory( tools )

duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/deps/typescript/typescript.js OUT typescript.duk.h NULL VARIABLE typescript_duk )
toh( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/util/ts.js OUT ts.js.h NULL VARIABLE ts_js )
duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/console.js OUT console.duk.h NULL VARIABLE console_duk )
duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/promise.js OUT promise.duk.h NULL VARIABLE promise_duk )
duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/require.js OUT require.duk.h NULL VARIABLE require_duk )
duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/timers.js OUT timers.duk.h NULL VARIABLE timers_duk )
duk( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/util.js OUT util.duk.h NULL VARIABLE util_duk )
toh( IN ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/path.ts OUT path.ts.h NULL VARIABLE path_ts )
add_executable(
	tsr
	typescript.duk.h
	ts.js.h
	console.duk.h
	require.duk.h
	promise.duk.h
	timers.duk.h
	util.duk.h
	path.ts.h
	src/main.cpp
	src/Context.cpp
	src/native/require.cpp
	src/native/timers.cpp
	src/util/path.cpp
	src/util/ts.cpp
	src/util/ts.duk.cpp
)
target_link_libraries( tsr PUBLIC duktape uv_a )
target_include_directories( tsr PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src )
