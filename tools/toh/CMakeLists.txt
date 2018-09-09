add_library( toh STATIC src/toh.cpp )
target_include_directories( toh PUBLIC include )
add_executable( tohcli src/main.cpp )
target_link_libraries( tohcli PUBLIC toh )
function( toh )
	cmake_parse_arguments( ARG "NULL" "IN;OUT;VARIABLE" "" ${ARGN} )
	set( COMMAND "$<TARGET_FILE:tohcli>" )
	if( ARG_NULL )
		list( APPEND COMMAND "-null" )
	endif()
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
		tohcli
	)
endfunction()
