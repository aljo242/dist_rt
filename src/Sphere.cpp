#include "Sphere.h"
#include "Ray.h"


Sphere::Sphere(const Point3& cen, const float r)
	: center(cen), radius(r)
{}

bool Sphere::Intersect(const Ray3& r, const float tmin, const float tmax) const
{
	const Vec3 OriginToCenter = r.Origin() - center;
	const auto a = r.DirLength() * r.DirLength();
	const auto half_b = glm::dot(OriginToCenter, r.Dir());
	const auto c = Length(OriginToCenter) * Length(OriginToCenter) - radius * radius;
	const auto discriminant = half_b * half_b - a * c;

	//Vec3 outwardNormal;

	if (discriminant > 0)
	{
		const auto root = std::sqrt(discriminant);
		auto temp = (-half_b - root) / a;
		if (temp < tmax && temp > tmin)
		{
			return true;
		}

		temp = (-half_b + root) / a;
		if (temp < tmax && temp > tmin)
		{
			return true;
		}
		}

	return false;
}
