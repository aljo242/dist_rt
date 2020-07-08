#ifndef CASTING_H
#define CASTING_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

using namespace mathLib;


namespace rtLib
{

vec3 random_in_unit_sphere();
vec3 color(const ray& r, hitable* world, const int depth);
vec3 reflect(const vec3& vec, const vec3& normal);
bool refract(const vec3& vec, const vec3& normal, const float refRatio, vec3& refracted);
float schlick(const float cosine, const float refIdx);


} // namespace rtLib


#endif // CASTING_H