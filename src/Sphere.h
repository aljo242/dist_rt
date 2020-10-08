#ifndef SPHERE_H
#define SPHERE_H


#include "defs.h"
#include "Scene_Object.h"

// fwd dec
class Ray3;

class Sphere : public Scene_Object
{
public:
	Sphere(const Point3& cen, const float r);

	virtual bool Intersect(const Ray3& r, const float tmin, const float tmax) const;

private:
	Point3 center;
	float radius;
};


#endif