#include "Axis_Aligned_Rect.h"

bool rtLib::XY_Rect::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
    const auto t        {(k - r.Origin().z()) / r.Direction().z()};
    if (t < t_min || t > t_max)
    {
        return false;
    }

    const auto x        {r.Origin().x() + t*r.Direction().x()};
    const auto y        {r.Origin().y() + t*r.Direction().y()};
    if ( x < x0 || x > x1 || y < y0 || y > y1 )
    {
        return false;
    }

    rec.u =             (x - x0)/(x1 - x0);
    rec.v =             (y - y0)/(y1 - y0);
    rec.t =             t;
    // TODO : make this NOT fixed
    const auto outwardNorm  {vec3(0, 0, 1)}; 
    rec.SetFaceNormal(r, outwardNorm);
    rec.pMat =          this->pMat;
    rec.p =             r.At(t);
    return true;
}

bool rtLib::XY_Rect::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
    constexpr double Z_PAD {0.0001};
    // BB must have non-zero width in each dim, so pad
    outputBox = AABB(point3(x0, y0, k - Z_PAD), point3(x1, y1, k + Z_PAD));
    return true;
}



bool rtLib::XZ_Rect::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
    const auto t        {(k - r.Origin().y()) / r.Direction().y()};
    if (t < t_min || t > t_max)
    {
        return false;
    }

    const auto x        {r.Origin().x() + t*r.Direction().x()};
    const auto z        {r.Origin().z() + t*r.Direction().z()};
    if ( x < x0 || x > x1 || z < z0 || z > z1 )
    {
        return false;
    }

    rec.u =             (x - x0)/(x1 - x0);
    rec.v =             (z - z0)/(z1 - z0);
    rec.t =             t;
    // TODO : make this NOT fixed
    const auto outwardNorm  {vec3(0, 1, 0)}; 
    rec.SetFaceNormal(r, outwardNorm);
    rec.pMat =          this->pMat;
    rec.p =             r.At(t);
    return true;
}

bool rtLib::XZ_Rect::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
    constexpr double Y_PAD {0.0001};
    // BB must have non-zero width in each dim, so pad
    outputBox = AABB(point3(x0, k - Y_PAD, z0), point3(x1, k + Y_PAD, z1));
    return true;
}


bool rtLib::YZ_Rect::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
    const auto t        {(k - r.Origin().x()) / r.Direction().x()};
    if (t < t_min || t > t_max)
    {
        return false;
    }

    const auto y        {r.Origin().y() + t*r.Direction().y()};
    const auto z        {r.Origin().z() + t*r.Direction().z()};
    if ( y < y0 || y > y1 || z < z0 || z > z1 )
    {
        return false;
    }

    rec.u =             (y - y0)/(y1 - y0);
    rec.v =             (z - z0)/(z1 - z0);
    rec.t =             t;
    // TODO : make this NOT fixed
    const auto outwardNorm  {vec3(1, 0, 0)}; 
    rec.SetFaceNormal(r, outwardNorm);
    rec.pMat =          this->pMat;
    rec.p =             r.At(t);
    return true;
}

bool rtLib::YZ_Rect::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
    constexpr double X_PAD {0.0001};
    // BB must have non-zero width in each dim, so pad
    outputBox = AABB(point3(k - X_PAD, y0, z0), point3(k + X_PAD, y1, z1));
    return true;
}