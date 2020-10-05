
add_executable(main 
	main.cpp
	)

target_link_libraries(main PUBLIC
	${EXTRA_LIBS}
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)



