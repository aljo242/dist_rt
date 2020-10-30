#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
MESSAGE("SETTING UP TESTS")

add_executable(test_glm_features glm_test.cpp)


foreach(TARGET_NAME
	IN ITEMS
		test_glm_features
		
)

	target_link_libraries(${TARGET_NAME} PUBLIC
		${EXTRA_LIBS}
	)

	target_include_directories(${TARGET_NAME} PUBLIC
		${PROJECT_BINARY_DIR}
	)
	
endforeach()


add_test(glm_features test_glm_features)