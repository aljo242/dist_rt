#include "Translate.h"

bool rtLib::Translate::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
    ray movedRay(r.Origin() - offset, r.Direction(), r.Time());
    if (!ptr->Hit(movedRay, t_min, t_max, rec))
    {
        return false;
    }

    rec.p +=        offset;
    rec.SetFaceNormal(movedRay, rec.normal);

    return true;
}

bool rtLib::Translate::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
    if (!ptr->BoundingBox(t0, t1, outputBox))
    {
        return false;
    }

    outputBox =     AABB(outputBox.min() + offset, outputBox.max() + offset);

    return true;
}