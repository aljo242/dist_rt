#ifndef BOUNDING_H
#define BOUNDING_H

#include <algorithm>

#include "vec3.h"
#include "ray.h"

namespace mathLib
{

class AABB
{
public:
	AABB() = default;
	AABB(const point3& a, const point3& b) : _min(a), _max(b) {}

	point3 min() const {return _min;}
	point3 max() const {return _max;}

	inline bool Hit(const ray& r, double tmin, double tmax) const
	{
		for (size_t i = 0; i < 3; ++i)
		{
			const auto invD {1.0 / r.Direction()[i]};
			auto t0 {(min()[i] - r.Origin()[i]) * invD};
			auto t1 {(max()[i] - r.Origin()[i]) * invD};
			if (invD < 0.0)
			{
				std::swap(t0, t1);
			}
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin)
			{
				return false;
			}
		}
		return true;
	}

private:
	point3 _min;
	point3 _max;

};


AABB SurroundingBox(const AABB& box0, const AABB& box1);

} // namespace mathLib

#endif // BOUNDING_H