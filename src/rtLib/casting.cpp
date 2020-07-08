#include "casting.h"
#include "hitable_list.h"
#include "rng.h"
#include "material.h"

using namespace mathLib;
using namespace rtLib;


vec3 rtLib::random_in_unit_sphere()
{
	rando rand;
	vec3 p;
	do 
	{
		p = 2.0 * vec3(static_cast<float>(rand.genRand()), 
			static_cast<float>(rand.genRand()),
			static_cast<float>(rand.genRand())) - vec3(1.0f, 1.0f, 1.0f);
	}   while (p.squared_length() >= 1.0f);
	return p;
}



vec3 rtLib::color(const ray& r, hitable* world, const int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
	{
		ray scattered;
		vec3 attenuation;
		if ((depth < 50) && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return {attenuation * color(scattered, world, depth + 1)};
		}
		else
		{
			return {0.0f, 0.0f, 0.0f};
		}
	}
	else
	{
		vec3 unit_direction {unit_vector(r.direction())};
		const float t {0.5f * (unit_direction.y() + 1.0f)};
		return ((1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f));
	}
}


vec3 rtLib::reflect(const vec3& vec, const vec3& normal)
{
	return {vec - 2.0f * dot(vec,normal) * normal};
}


bool rtLib::refract(const vec3& vec, const vec3& normal, const float refractRatio, vec3& refracted)
{
	const vec3 uv {unit_vector(vec)};
	const float dt {dot(uv, normal)};
	const float discriminant {1.0f - (refractRatio * refractRatio * (1.0f - dt*dt))};
	if (discriminant > 0.0f)
	{
		refracted = (refractRatio * (uv - normal * dt)) - normal * std::sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}

}



float rtLib::schlick(const float cosine, const float refIdx)
{
	const float r0{ ((1.0f - refIdx) / (1.0f + refIdx)) * ((1.0f - refIdx) / (1.0f + refIdx)) }; // squared val
	return {0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f)};
}


