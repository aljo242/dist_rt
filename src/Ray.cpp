#include "Ray.h"

Ray3::Ray3(const Vec3& o, const Point3& d)
	: origin(o), dir(d)
{
	Normalize();
}

Ray3::Ray3(const Vec3& d)
	: origin(0, 0, 0), dir(d)
{}

Ray3::Ray3()
	: origin(0, 0, 0), dir(1,1,1)
{}

void Ray3::Normalize()
{
	const float length = DirLength();
	dir = Vec3(dir.x / length, dir.y / length, dir.z / length);
}


Point3 Ray3::At(const float t) const
{
	return { origin + t * dir };
}

float Ray3::DirLength() const
{
	return  std::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
}

