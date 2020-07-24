#include "material.h"
#include "casting.h"
#include "common.h"

using namespace mathLib;
using namespace rtLib;


double rtLib::Schlick(const double cosine, const double refIdx)
{
	constexpr double SCHLICK_FACTOR {5.0};
	auto r0 { (1.0 - refIdx) / (1.0 + refIdx) };
	r0 = r0 * r0;
	return r0 + (1.0 - r0) * std::pow((1.0 - cosine), SCHLICK_FACTOR);
}


bool Lambertian::Scatter(const ray& r, const HitRecord& rec,
		vec3& attenuation, ray& scattered) const 
{
	const vec3 scatterDir {rec.normal + RandUnitVec()};
	scattered = ray(rec.p, scatterDir, r.Time());
	attenuation = albedo->Value(rec.u, rec.v, rec.p);
	return true;
}


bool Metal::Scatter(const ray& r, const HitRecord& rec,
		vec3& attenuation, ray& scattered) const 
{
	const vec3 reflected {Reflect(UnitVector(r.Direction()), rec.normal)};
	scattered = ray(rec.p, reflected + fuzz * RandInUnitSphere(), r.Time());
	attenuation = albedo;
	return (Dot(scattered.Direction(), rec.normal) > 0.0);
}


bool Dielectric::Scatter(const ray& r, const HitRecord& rec, vec3& attenuation, ray& scattered) const
{
	attenuation = color3(1.0, 1.0, 1.0);
	const double refRatio {(rec.frontFace) ? (1.0/refIdx) : (refIdx)};
	const auto unitDir {UnitVector(r.Direction())};

	const double cosTheta {std::fmin(Dot(-unitDir, rec.normal), 1.0)};
	const double sinTheta {std::sqrt(1.0 - cosTheta * cosTheta)};

	if(refRatio * sinTheta > 1.0)
	{
		const vec3 reflected {Reflect(unitDir, rec.normal)};
		scattered = ray(rec.p, reflected, r.Time());
		return true;
	}

	const auto reflectProb {Schlick(cosTheta, refRatio)};
	if (RandDouble() < reflectProb)
	{
		const vec3 reflected {Reflect(unitDir, rec.normal)};
		scattered = ray(rec.p, reflected, r.Time());
		return true;
	}

	const vec3 refracted {Refract(unitDir, rec.normal, refRatio)};
	scattered = ray(rec.p, refracted, r.Time());
	return true;

}


bool Diffuse_Light::Scatter(const ray& r, const HitRecord& rec, vec3& attenuation, ray& scattered) const
{
	return false;
}

color3 Diffuse_Light::Emitted(const double u, const double v, const point3& p) const
{
	return emit->Value(u,v,p);
}
