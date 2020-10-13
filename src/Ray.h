#ifndef RAY_H
#define RAY_H

#include "defs.h"


constexpr float T_MIN{ 0.0f };
constexpr float T_MAX{ infinity };

class Ray3;

struct HitRecord
{
public:
	// we will assume all collisions occur on to the "outward normal"  
	// of the geometry
	Point3 point;
	Vec3 normal;
	float t;			// distance cast into the scene
};


class Ray3
{
public:
	Ray3();
	Ray3(const Vec3& o, const Point3& d);
	Ray3(const Vec3& d);

	void Normalize();
	Vec3 Dir() const;
	Point3 Origin() const;
	Point3 At(const float t) const;
	float DirLength() const;
	void ModifyHitRecord(const Ray3& n, const float t);

private:
	Point3 origin;
	Vec3 dir;
	HitRecord hr;
	float time = 0.0f;
};

#endif