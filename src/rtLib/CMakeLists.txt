

add_library(rtLib 
	Material.cpp Material.h
	casting.cpp casting.h
	camera.cpp camera.h
	hittable_list.cpp hittable_list.h
	sphere.cpp 	sphere.h
	hittable.h
	)

target_include_directories(mathLib
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
	)

target_link_libraries(rtLib
	PUBLIC mathLib)


#install