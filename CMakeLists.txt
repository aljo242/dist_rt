cmake_minimum_required(VERSION 3.13)

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

list(APPEND EXTRA_LIBS 
	project_options 
	project_warnings
	)

include(cmake/ConanConfig.cmake)
run_conan()



#################################################################################################################################
# project setup
#################################################################################################################################

add_subdirectory(src)

####################################################################################


