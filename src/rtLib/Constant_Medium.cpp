#include "Constant_Medium.h"

bool rtLib::Constant_Medium::Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const
{
    #if defined(_DEBUG)
    const bool debugPrint {RandDouble() < 0.00001};
    #endif

    HitRecord rec1;
    HitRecord rec2;
    constexpr auto CHECK_OFFSET      {0.0001};

    if (!boundary->Hit(r, -infinity, infinity, rec1))
    {
        return false;
    }

    if (!boundary->Hit(r, rec1.t + CHECK_OFFSET, infinity, rec2))
    {
        return false;
    }

    // print samples when debugging
    #if defined(_DEBUG)
    if (debugPrint)
    {
        spdlog::debug("t0 = {}, t1 = {}", rec1.t, rec2.t);
    }
    #endif

    // CLAMP
    if (rec1.t < t_min)
    {
        rec1.t = t_min;
    }
    if (rec2.t > t_max)
    {
        rec2.t = t_max;
    }

    if (rec1.t >= rec2.t)
    {
        return false;
    }

    if (rec1.t < 0)
    {
        rec1.t = 0;
    }

    const auto rayLength        {r.Direction().Length()};
    const auto distInsideBound  {(rec2.t - rec1.t) * rayLength};
    const auto hitDist          {negInverseDensity * std::log(RandDouble())};

    if (hitDist > distInsideBound)
    {
        return false;
    }

    rec.t = rec1.t + hitDist / rayLength;
    rec.p = r.At(rec.t);

    #if defined(_DEBUG)
    if (debugPrint)
    {
        spdlog::debug("Hit Distance : {}\nHit Time : {}\nHit Point : {}", hitDist, rec.t, rec.p);
    }
    #endif

    rec.normal = vec3(1, 0, 0);         // arbitrary
    rec.frontFace = true;               // arbitrary
    rec.pMat = phaseFunction;

    return true;
}

bool rtLib::Constant_Medium::BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const
{
    return boundary->BoundingBox(t0, t1, outputBox);
}