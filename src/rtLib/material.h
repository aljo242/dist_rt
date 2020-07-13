#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"

namespace rtLib
{


double Schlick(const double cosine, const double refIdx);


class Material
{
public:
	virtual bool Scatter(const ray& r, const HitRecord& rec,
		vec3& attenuation, ray& scattered) const = 0;

	virtual ~Material() = default;

};



class Lambertian : public Material
{
public:
	explicit Lambertian(const color3& a) : albedo(a) {}
	bool Scatter(const ray& r, const HitRecord& rec,
		vec3& attenuation, ray& scattered) const override final;

	virtual ~Lambertian() = default;

	color3 albedo;
};



class Metal : public Material
{
public:
	explicit Metal(const color3& a, const double f) : albedo(a), fuzz(f < 1.0 ? f : 1.0) {}
	bool Scatter(const ray& r, const HitRecord& rec,
		vec3& attenuation, ray& scattered) const override final;

	virtual ~Metal() = default;

	color3 albedo;
	double fuzz;
};



class Dielectric : public Material
{
public:
	explicit Dielectric(const double ri) : refIdx(ri)  {}
	bool Scatter(const ray& r, const HitRecord& rec,
		vec3& attenuation, ray& scattered) const override final;

	virtual ~Dielectric() = default;


	double refIdx;
};


} // namespace rtLib


#endif // MATERIAL_H