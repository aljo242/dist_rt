#ifndef ROTATE_H
#define ROTATE_H

#include "hittable.h"

namespace rtLib{

class Rotate_Y : public hittable 
{
public:
    explicit Rotate_Y(std::shared_ptr<hittable> p, const double angle);

    virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    std::shared_ptr<hittable> ptr;
    double sinTheta;
    double cosTheta;
    bool hasBox;
    AABB boundBox;
}; 

} // namespace rtLib

#endif // ROTATE_H