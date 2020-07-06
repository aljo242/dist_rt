#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

using namespace mathLib;

namespace rtLib
{

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
};

class hitable
{
public:
	virtual bool hit(const ray& r, const float t_min, 
		const float t_max, hit_record& rec) const = 0;

	virtual ~hitable() {}
};

}

#endif // HITABLE_H