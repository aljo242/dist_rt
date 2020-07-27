#ifndef BOX_H
#define BOX_H

#include "Axis_Aligned_Rect.h"
#include "hittable_list.h"
using namespace mathLib;

namespace rtLib
{

class Box : public hittable
{
public:
    Box() = default;
    Box(const point3& p0, const point3& p1, std::shared_ptr<Material> mat);

    virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    point3              boxMin;
    point3              boxMax;
    hittable_list       faces;
};

} // namespace rtLib

#endif // BOX_H