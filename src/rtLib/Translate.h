#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "hittable.h"
using namespace mathLib;

namespace rtLib
{

class Translate : public hittable
{
public:
    Translate(std::shared_ptr<hittable> p, const vec3& displacement)
        : ptr(p), offset(displacement)
    {}

	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    std::shared_ptr<hittable>   ptr;
    vec3                        offset;
};

} // namespace rtLib

#endif // TRANSLATE_H