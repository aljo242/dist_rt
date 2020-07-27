#include "Rotate.h"

// rotate about the y axis
rtLib::Rotate_Y::Rotate_Y(std::shared_ptr<hittable> p, const double angle) 
    : ptr(p)
{
    const auto radians      {DegreesToRadians(angle)};
    sinTheta =              std::sin(radians);
    cosTheta =              std::cos(radians);
    hasBox =                ptr->BoundingBox(0.0, 1.0, boundBox);

    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                const auto x {i*boundBox.max().x() + (1-i)*boundBox.min().x()};
                const auto y {j*boundBox.max().y() + (1-j)*boundBox.min().y()};
                const auto z {k*boundBox.max().z() + (1-k)*boundBox.min().z()};

                const auto newX   { cosTheta * x + sinTheta * z};
                const auto newZ   {-sinTheta * x + cosTheta * z};

                vec3 testVec(newX, y, newZ);

                for (int comp = 0; comp < 3; ++comp)
                {
                    min[comp] = std::fmin(min[comp], testVec[comp]);
                    max[comp] = std::fmax(max[comp], testVec[comp]);
                }
            }
        }
    }

    boundBox = AABB(min, max);
}

bool rtLib::Rotate_Y::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
    auto origin       {r.Origin()};
    auto dir          {r.Direction()};

    origin[0] = cosTheta * r.Origin().x() - sinTheta * r.Origin().z();
    origin[2] = sinTheta * r.Origin().x() + cosTheta * r.Origin().z();

    dir[0] =    cosTheta * r.Direction().x() - sinTheta * r.Direction().z();
    dir[2] =    sinTheta * r.Direction().x() + cosTheta * r.Direction().z();

    const ray rotated(origin, dir, r.Time());

    if (!ptr->Hit(rotated, t_min, t_max, rec))
    {
        return false;
    }

    auto p            {rec.p};
    auto normal       {rec.normal};

    p[0] =  cosTheta * rec.p.x() + sinTheta * rec.p.z();
    p[2] = -sinTheta * rec.p.x() + cosTheta * rec.p.z();

    normal[0] =  cosTheta * rec.normal.x() + sinTheta * rec.normal.z();
    normal[2] = -sinTheta * rec.normal.x() + cosTheta * rec.normal.z();

    rec.p = p;
    rec.SetFaceNormal(rotated, normal);

    return true;
}

bool rtLib::Rotate_Y::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
    outputBox = boundBox;
    return hasBox;
}