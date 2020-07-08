#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

using namespace mathLib;

namespace rtLib
{
	
class sphere: public hitable
{
public:
	sphere() = default;
	sphere(const vec3& cen, const float r, material* p) : center(cen), radius(r), mat_ptr(p) {}

	virtual bool hit(const ray& r, const float t_min, 
		const float t_max, hit_record& rec) const override;
	
protected:
	virtual ~sphere() = default;



private:
	vec3 center;
	float radius;
	material* mat_ptr;
};


} // namespace mathLib

#endif