include(FindMPI)

set(RUNTIME_INCLUDES "")

if (MPI_CXX_FOUND)
	MESSAGE("Found MPI, compiling with support")
	list(APPEND EXTRA_LIBS 
		project_options 
		project_warnings
		OpenMP::OpenMP_CXX
		MPI::MPI_CXX
		CONAN_PKG::spdlog
		CONAN_PKG::glm
		CONAN_PKG::stb
	)
	set(RUNTIME_INCLUDES "parallel.h")
	add_compile_definitions(WITH_MPI)

else()
	MESSAGE("Count not find MPI, compiling without support")
	set(RUNTIME_INCLUDES "serial.h")

endif()




add_executable(main 
	main.cpp
	 "Ray.h" "defs.h" "Ray.cpp" "Plane.h" "Plane.cpp" "Image.h" "Image.cpp" "Sphere.h" "Sphere.cpp" "Scene_Object.h" "utils.h" "Camera.h" "Camera.cpp" ${RUNTIME_INCLUDES})

target_link_libraries(main PUBLIC
	${EXTRA_LIBS}
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)



