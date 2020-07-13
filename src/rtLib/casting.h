#ifndef CASTING_H
#define CASTING_H

#include "common.h"
#include "vec3.h"

using namespace mathLib;


namespace rtLib
{

vec3 RandInUnitDisk();
vec3 RandUnitVec();
vec3 RandInUnitSphere();
vec3 RandInHemiSphere(const vec3& normal);
vec3 Reflect(const vec3& vec, const vec3& normal);
vec3 Refract(const vec3& uv, const vec3& normal, const double refRatio);

} // namespace rtLib


#endif // CASTING_H