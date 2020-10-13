include(FindMPI)

set(MPI_INCLUDES "")

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
	set(MPI_INCLUDES "parallel.h")

else()
	MESSAGE("Count not find MPI, compiling without support")
	set(MPI_INCLUDES "")

endif()




add_executable(main 
	main.cpp
	 "Ray.h" "defs.h" "Ray.cpp" "Plane.h" "Plane.cpp" "Image.h" "Image.cpp" "Sphere.h" "Sphere.cpp" "Scene_Object.h" "utils.h" "Camera.h" "Camera.cpp" ${MPI_INCLUDES})

target_link_libraries(main PUBLIC
	${EXTRA_LIBS}
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)



