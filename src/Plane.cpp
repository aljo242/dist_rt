#include "Plane.h"

Plane::Plane(const Point3& origin, const Vec3& A, const Vec3& B)
{
	const auto cross{ glm::cross(A, B) };
	norm = Ray3(origin, glm::normalize(cross));
}

Vec3 Plane::NormVec() const
{
	return norm.dir;
}

Point3 Plane::NormPoint() const
{
	return norm.origin;
}