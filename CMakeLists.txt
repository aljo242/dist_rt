cmake_minimum_required(VERSION 3.15)

project(Tutorial VERSION 1.0
	DESCRIPTION "learning cmake and other CI/CD stuff"
	LANGUAGES CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

find_program(CCACHE ccache)
if(CCACHE)
	set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# link this 'library' to set c++ standard / compile time options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
	option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
	if(ENABLE_BUILD_WITH_TIME_TRACE)
		add_compile_definitions(project_warnings INTERFACE -ftime-trace)
	endif()
endif()

# link this 'library' to use standard warnings in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer optoins if supported by compilers 
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_warnings)

#enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

#################################################################################################################################
# options
#################################################################################################################################

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" ON)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" OFF)

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
	# sets a global PCH parameter, each project will build its own PCH though
	target_precompile_headers(
		project_options
		INTERFACE
		<vector>
		<string>
		<map>
		<utility>
		)
endif()

# set up extra conan dependencies 
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

# use the custom math lib or no?
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

if(USE_MYMATH)
	add_subdirectory(MathFunctions)
	list(APPEND EXTRA_LIBS MathFunctions)
endif()

list(APPEND EXTRA_LIBS 
	project_options 
	project_warnings
	)

include(cmake/Conan.cmake)
run_conan()



#################################################################################################################################
# project setup
#################################################################################################################################

# add the executable
add_executable(Tutorial tutorial.cpp)

target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

# add the binaruy tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
						"${PROJECT_BINARY_DIR}"
						)

# install rules
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

####################################################################################

enable_testing()

# does the app run?
add_test(NAME Runs COMMAND Tutorial 25.0)

# does the useage message work?
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage 
	PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
	)

# define a function to simplify adding tests
function(do_test target arg result)
	add_test(NAME Comp${arg} COMMAND ${target} ${arg})
	set_tests_properties(Comp${arg}
		PROPERTIES PASS_REGULAR_EXPRESSION ${result}
		)
endfunction(do_test)

# do a bunch of tests
do_test(Tutorial 4 "4 is: 2")
do_test(Tutorial 9 "9 is: 3")
do_test(Tutorial 5 "5 is: 2.236")
do_test(Tutorial 7 "7 is: 2.645")
do_test(Tutorial 25 "25 is: 5")
do_test(Tutorial -25 "-25 is: [-nan|nan|0]")
do_test(Tutorial 0.0001 "0.0001 is: 0.01")


