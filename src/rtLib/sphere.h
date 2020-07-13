#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

using namespace mathLib;

namespace rtLib
{

class Material;
	
class sphere: public hittable
{
public:
	sphere() = default;
	explicit sphere(const point3& cen, const double r, std::shared_ptr<Material> p) 
		: center(cen), radius(r), pMat(p) 
	{}

	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override;
	
	virtual ~sphere() = default;

	point3 center;
	double radius;
	std::shared_ptr<Material> pMat;
};


} // namespace mathLib

#endif // SPHERE_H