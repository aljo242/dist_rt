#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

using namespace mathLib;

namespace rtLib
{

class camera
{
public:
	camera();
	ray get_ray(const float u, const float v) const;

private:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

} // namespace rtLib

#endif