#include "sphere.h"

using namespace mathLib;

bool sphere::hit(const ray& r, const float t_min, 
		const float t_max, hit_record& rec) const 
{
	vec3 oc {r.origin() - center};
	const float a {dot(r.direction(), r.direction())};
	const float b {dot(oc, r.direction())};
	const float c {dot(oc, oc) - radius * radius};
	const float discriminant {b * b - a * c};
	if (discriminant > 0.0f)
	{
		float temp {(-b - std::sqrt(discriminant))/a};
		if ((temp < t_max) && (temp > t_min))
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + std::sqrt(discriminant))/a;
		if ((temp < t_max) && (temp > t_min))
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}