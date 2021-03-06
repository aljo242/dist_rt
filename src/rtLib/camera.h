#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "vec3.h"
#include "ray.h"
using namespace mathLib;

namespace rtLib
{

class camera
{
public:
	camera(const point3& lookFrom,
		const point3& lookAt,
		const vec3& vUP, 
		const double vFOV, 
		const double aspectRatio,
		const double aperture,
		const double focusDist,
		const double t0 = 0.0,
		const double t1 = 0.0);

	ray GetRay(const double s, const double t) const;


private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lensRadius;
	double time0, time1; // shutter open/close times
};

} // namespace rtLib

#endif