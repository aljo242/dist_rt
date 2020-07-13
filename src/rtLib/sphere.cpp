#include "sphere.h"

using namespace mathLib;
using namespace rtLib;

bool sphere::Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const 
{
	const auto oc 			{r.Origin() - center};
	const auto a 			{r.Direction().SquaredLength()};
	const auto half_b 		{Dot(oc, r.Direction())};
	const auto c 			{oc.SquaredLength() - radius*radius};
	const auto discriminant {half_b * half_b - a * c};
	if (discriminant > 0.0)
	{
		const auto root {std::sqrt(discriminant)};

		auto temp 		{(-half_b - root) / a};
		if ((temp < t_max) && (temp > t_min))
		{
			rec.t = temp;
			rec.p = r.At(rec.t);
			const vec3 outwardNorm {(rec.p - center) / radius};
			rec.SetFaceNormal(r, outwardNorm);
			// if a ray hits this sphere, set its material pointer to my matieral
			rec.pMat = pMat;	
			return true;
		}

		temp = (-half_b + root) / a;
		if ((temp < t_max) && (temp > t_min))
		{
			rec.t = temp;
			rec.p = r.At(rec.t);
			const vec3 outwardNorm {(rec.p - center) / radius};
			rec.SetFaceNormal(r, outwardNorm);
			// if a ray hits this sphere, set its material pointer to my matieral
			rec.pMat = pMat;
			return true;
		}
	}
	return false;
}