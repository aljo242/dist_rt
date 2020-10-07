#ifndef PLANE_H
#define PLANE_H

#include "Ray.h"

class Plane
{
public:
	// two vectors and a point 
	Plane(const Point3& origin, const Vec3& A, const Vec3& B);

	Vec3 NormVec() const;
	Point3 NormPoint() const;

private:
	// hold a point and norm (using Ray)
	Ray3 norm{ {0,0,0}, {0,0,0} };
};

#endif