add_executable( duk src/main.cpp )
target_link_libraries( duk PUBLIC toh duktape )
function( duk )
	cmake_parse_arguments( ARG "" "IN;OUT;VARIABLE" "" ${ARGN} )
	set( COMMAND "$<TARGET_FILE:duk>" )
	if( ARG_VARIABLE )
		list( APPEND COMMAND "-variable" "${ARG_VARIABLE}" )
	endif()
	list( APPEND COMMAND "${ARG_IN}" )
	list( APPEND COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${ARG_OUT}" )
	add_custom_command(
		OUTPUT
		${ARG_OUT}
		COMMAND
		${COMMAND}
		MAIN_DEPENDENCY
		${ARG_IN}
		DEPENDS
		duk
	)
endfunction()
