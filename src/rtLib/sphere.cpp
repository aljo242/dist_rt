#include "sphere.h"

#include "common.h"
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


bool sphere::BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const
{
	outputBox = AABB(
		center - vec3(radius, radius, radius),
		center + vec3(radius, radius, radius)
		);
	return true;
}


bool moving_sphere::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const 
{
	const auto oc 			{r.Origin() - center(r.Time())};
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
			const vec3 outwardNorm {(rec.p - center(r.Time())) / radius};
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
			const vec3 outwardNorm {(rec.p - center(r.Time())) / radius};
			rec.SetFaceNormal(r, outwardNorm);
			// if a ray hits this sphere, set its material pointer to my matieral
			rec.pMat = pMat;
			return true;
		}
	}
	return false;
}


bool moving_sphere::BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const
{
	const AABB box0(
		center(t0) - vec3(radius, radius, radius),
		center(t0) + vec3(radius, radius, radius)
		);

	const AABB box1(
		center(t1) - vec3(radius, radius, radius),
		center(t1) + vec3(radius, radius, radius)
		);
 
	outputBox = SurroundingBox(box0, box1);

	return true;
}


point3 moving_sphere::center(const double time) const 
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

// utility
// TODO - refactor to return tuple
void rtLib::GetSphereUV(const vec3& p, double& u, double& v)
{
	const auto phi		{std::atan2(p.z(), p.x())};
	const auto theta	{std::asin(p.y())};
	u = 1.0 - (phi + pi) / (2.0 * pi);
	v = (theta + pi/2.0) / pi;
}
