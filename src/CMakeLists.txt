add_subdirectory(mathLib)
add_subdirectory(rtLib)
list(APPEND EXTRA_LIBS 
	mathLib
	rtLib
	project_options
	project_warnings
	)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC
	${EXTRA_LIBS}
	CONAN_PKG::fmt
	CONAN_PKG::spdlog
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)



