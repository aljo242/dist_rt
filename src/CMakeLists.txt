include(FindMPI)

set(RUNTIME_INCLUDES "")

if (MPI_CXX_FOUND)
	MESSAGE("Found MPI, compiling with support")
	list(APPEND EXTRA_LIBS 
		MPI::MPI_CXX

	)
	set(RUNTIME_INCLUDES "parallel.h")
	add_compile_definitions(WITH_MPI)

else()
	MESSAGE("Count not find MPI, compiling without support")
	set(RUNTIME_INCLUDES "serial.h")

endif()


add_executable(main 
	main.cpp
	 "Ray.h" "Ray.cpp"
	 "defs.h" 
	 "Plane.h" "Plane.cpp" 
	 "Image.h" "Image.cpp" 
	 "Sphere.h" "Sphere.cpp" 
	 "Scene_Object.h" 
	 "utils.h" 
	 "Camera.h" "Camera.cpp" 
	 "Tiling.h" "Tiling.cpp" 
	 "VMesh.h" "VMesh.cpp" 
	 ${RUNTIME_INCLUDES} 
	 "Transfer.h" "Transfer.cpp"  
	 "Surface.h"  "Surface.cpp" 
	 "Medium.h" "Medium.cpp" 
	 "Material.cpp" "Material.cpp"
	  "Timer.h" "Timer.cpp" "Shape.h" "Shape.cpp" "Transform.h" "Bounds.cpp" "Bounds.h")

target_link_libraries(main PUBLIC
	${EXTRA_LIBS}
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)



