#include "camera.h"
#include "casting.h"
#include "common.h"


using namespace mathLib;
using namespace rtLib;

camera::camera(const point3& lookFrom,
		const point3& lookAt,
		const vec3& vUP, 
		const double vFOV, 
		const double aspectRatio,		
		const double aperture,
		const double focusDist,
		const double t0,
		const double t1)
{
	const auto theta 				{DegreesToRadians(vFOV)};
	const auto h 					{std::tan(theta / 2.0)};
	const auto viewportH 			{2.0 * h};
	const auto viewportW			{aspectRatio * viewportH};

	const auto w 					{UnitVector(lookFrom - lookAt)};
	const auto u 					{UnitVector(Cross(vUP, w))};
	const auto v 					{Cross(u, w)};

	origin 			= lookFrom;
	horizontal 		= focusDist * viewportW * u;
	vertical		= focusDist * viewportH * v;
	lowerLeftCorner = origin - horizontal/2.0 - vertical/2.0 - focusDist * w;

	lensRadius = aperture / 2;
	time0 = t0;
	time1 = t1;
}

ray camera::GetRay(const double s, const double t) const
{
	const vec3 rd 		{lensRadius * RandInUnitDisk()};
	const vec3 offset	{u * rd.x() + v * rd.y()};	
	return {
		origin + offset, 
		lowerLeftCorner + s*horizontal + t*vertical - origin - offset, 
		RandDouble(time0, time1)
	};
}