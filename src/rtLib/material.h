#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"

namespace rtLib
{



class material
{
public:
	virtual bool scatter(const ray& r, const hit_record& rec,
		vec3& attenuation, ray& scattered) const = 0;

	virtual ~material() {}
};


class lambertian : public material
{
public:
	explicit lambertian(const vec3& a) : albedo(a) {}
	bool scatter(const ray& r, const hit_record& rec,
		vec3& attenuation, ray& scattered) const override final;

protected:
	virtual ~lambertian() = default;

private:
	vec3 albedo;
};


class metal : public material
{
public:
	explicit metal(const vec3& a, const float f) : albedo(a) {if(f < 1.0f) {fuzz = f;}}
	bool scatter(const ray& r, const hit_record& rec,
		vec3& attenuation, ray& scattered) const override final;

protected:
	virtual ~metal() = default;

private:
	vec3 albedo;
	float fuzz = 1.0f;
};


class dialectric : public material
{
public:
	explicit dialectric(const float ri) : refIdx(ri)  {}
	bool scatter(const ray& r, const hit_record& rec,
		vec3& attenuation, ray& scattered) const override final;


protected:
	virtual ~dialectric() = default;

private:
	float refIdx;
};


} // namespace rtLib


#endif // MATERIAL_H