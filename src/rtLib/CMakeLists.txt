

add_library(rtLib hitable_list.cpp hitable_list.h
	sphere.cpp sphere.h
	hitable.h
	)

target_include_directories(mathLib
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
	)

target_link_libraries(rtLib
	PUBLIC mathLib)


#install