#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

using namespace mathLib;

namespace rtLib
{
	
class sphere: public hitable
{
public:
	sphere() = default;
	sphere(const vec3& cen, const float r) : center(cen), radius(r) {}

	virtual bool hit(const ray& r, const float t_min, 
		const float t_max, hit_record& rec) const override;
	
protected:
	virtual ~sphere() {}


private:
	vec3 center;
	float radius;
};


} // namespace mathLib

#endif