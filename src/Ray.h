#ifndef RAY_H
#define RAY_H

#include "defs.h"


constexpr float T_MIN{ 0.0f };
constexpr float T_MAX{ infinity };

class Ray3;
class Medium;

class Ray3
{
public:
	Ray3();
	Ray3(const Vec3& o, const Point3& d);
	Ray3(const Vec3& d);

	void Normalize();
	Point3 At(const float t) const;
	float DirLength() const;

public:
	Point3 origin;
	Vec3 dir;
	float t_max = T_MAX;
	float time = 0.0f;
	Medium* medium {nullptr};
};


class RayDifferential3 : public Ray3
{
public:
	RayDifferential3();
	RayDifferential3(const Vec3& o, const Point3& d);
	bool HasNaNs() const;
	void Scale(float s);
	x 

};

#endif