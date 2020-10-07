#ifndef SPHERE_H
#define SPHERE_H

#include "defs.h"
#include "Ray.h"

class Sphere
{
public:
	Sphere(const Point3& cen, const float r);

	bool testIntersect(const Ray3& r, const float tmin, const float tmax) const;

private:
	Point3 center;
	float radius;
};

#endif