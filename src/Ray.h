#ifndef RAY_H
#define RAY_H

#include "defs.h"

class Ray3
{
public:
	Ray3(const Vec3& o, const Point3& d);
	Ray3(const Vec3& d);

	void Normalize();
	Vec3 Dir() const;
	Point3 Origin() const;
	Point3 At(const float t) const;

private:
	Point3 origin;
	Vec3 dir;
};

#endif