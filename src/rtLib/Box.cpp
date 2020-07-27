#include "Box.h"


rtLib::Box::Box(const point3& p0, const point3& p1, std::shared_ptr<Material> mat)
    :   boxMin(p0), boxMax(p1)
{
    faces.Add(std::make_shared<XY_Rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), mat));
    faces.Add(std::make_shared<XY_Rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), mat));

    faces.Add(std::make_shared<XZ_Rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), mat));
    faces.Add(std::make_shared<XZ_Rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), mat));

    faces.Add(std::make_shared<YZ_Rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), mat));
    faces.Add(std::make_shared<YZ_Rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), mat));
}


bool rtLib::Box::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
    return faces.Hit(r, t_min, t_max, rec);
}


bool rtLib::Box::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
    outputBox = AABB(boxMin, boxMax);
    return true;
}