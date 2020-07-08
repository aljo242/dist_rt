#include "material.h"
#include "casting.h"
#include "rng.h"

using namespace mathLib;
using namespace rtLib;




bool lambertian::scatter(const ray& r, const hit_record& rec,
		vec3& attenuation, ray& scattered) const 
{
	vec3 target {rec.p + rec.normal + random_in_unit_sphere()};
	scattered = ray(rec.p, target-rec.p);
	attenuation = albedo;
	return true;
}


bool metal::scatter(const ray& r, const hit_record& rec,
		vec3& attenuation, ray& scattered) const 
{
	vec3 reflected {reflect(unit_vector(r.direction()), rec.normal)};
	scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0.0f);
}


bool dialectric::scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const
{
	vec3 outwardNorm;
	vec3 reflected  {reflect(r.direction(), rec.normal)};
	float ni_n0;
	attenuation = vec3(1.0f, 1.0f, 0.0f);
	vec3 refracted(0.0f, 0.0f, 0.0f);  
	float reflectProb {0.0f};
	float cosine;
	rando rand;
	if (dot(r.direction(), rec.normal) > 0.0f)
	{
		outwardNorm = -rec.normal;
		ni_n0 = refIdx;
		cosine = dot(r.direction(), rec.normal) / r.direction().length();
		cosine = std::sqrt(1.0f - refIdx * refIdx * (1.0f - cosine * cosine));
	}
	else
	{
		outwardNorm = rec.normal;
		ni_n0 = 1.0f / refIdx;
		cosine =  - dot(r.direction(), rec.normal) / r.direction().length();
	}

	if (refract(r.direction(), outwardNorm, ni_n0, refracted))
	{
		reflectProb = schlick(cosine, refIdx);
	}
	else 
	{
		reflectProb = 1.0f;
	}

	if (static_cast<float>(rand.genRand()) < reflectProb)
	{
		scattered = ray(rec.p, reflected); 
	}
	else 
	{
		scattered = ray(rec.p, refracted);
	}
	return true;
}

