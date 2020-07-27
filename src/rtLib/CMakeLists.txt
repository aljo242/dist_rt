

add_library(rtLib 
	Constant_Medium.cpp		Constant_Medium.h
	Rotate.cpp				Rotate.h
	Translate.cpp			Translate.h
	Box.cpp					Box.h
	Axis_Aligned_Rect.cpp	Axis_Aligned_Rect.h
	Texture.cpp				Texture.h
	bounding_vol_node.cpp 	bounding_vol_node.h
	Material.cpp 			Material.h
	casting.cpp 			casting.h
	camera.cpp 				camera.h
	hittable_list.cpp 		hittable_list.h
	sphere.cpp 				sphere.h
	hittable.h
	)

target_include_directories(mathLib
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
	)

target_link_libraries(rtLib
	PUBLIC mathLib
	CONAN_PKG::spdlog)


#install