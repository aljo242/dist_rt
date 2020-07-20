#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include "common.h"
#include "vec3.h"
#include "ray.h"
#include "bounding.h"


using namespace mathLib;

namespace rtLib
{

class Material;

struct HitRecord
{
	point3 p;
	vec3 normal;
	bool frontFace;
	double t; 							// hit count
	double u; 							// texcoord
	double v; 							// texcoord
	std::shared_ptr<Material> pMat;

	inline void SetFaceNormal(const ray& r, const vec3& outwardNorm)
	{
		frontFace = Dot(r.Direction(), outwardNorm) < 0.0;
		normal = frontFace ? outwardNorm : -outwardNorm;
	}
};

class hittable
{
public:
	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const = 0;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const = 0;

	virtual ~hittable() = default;

};

}

#endif // HITABLE_H
