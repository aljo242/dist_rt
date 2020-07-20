
add_library(mathLib 
	image.h
	common.h
	Perlin.cpp			Perlin.h
	bounding.cpp 		bounding.h
	color.cpp 			color.h
	ray.cpp 			ray.h
	vec3.cpp 			vec3.h)

target_include_directories(mathLib
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
	)


#install