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
		: 
		center(cen), radius(r), pMat(p) 
	{}

	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override;
	
	virtual ~sphere() = default;

	point3 center;
	double radius;
	std::shared_ptr<Material> pMat;
};



class moving_sphere : public hittable
{
public:
	moving_sphere() = default;
	moving_sphere(const point3& cen0, const point3& cen1, const double t0, const double t1,
		const double r, std::shared_ptr<Material> p)
		:
		center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), pMat(p)
	{}

	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override;

	point3 center(const double time) const;

	virtual ~moving_sphere() = default;

public:
	 point3 center0, center1;
	 double time0, time1;
	 double radius;
	 std::shared_ptr<Material> pMat;
};


} // namespace mathLib

#endif // SPHERE_H