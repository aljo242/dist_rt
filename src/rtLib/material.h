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
};

} // namespace rtLib


#endif // MATERIAL_H