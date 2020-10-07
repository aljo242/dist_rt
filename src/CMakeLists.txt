
add_executable(main 
	main.cpp
	 "Ray.h" "defs.h" "Ray.cpp" "Plane.h" "Plane.cpp" "Image.h" "Image.cpp")

target_link_libraries(main PUBLIC
	${EXTRA_LIBS}
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)



