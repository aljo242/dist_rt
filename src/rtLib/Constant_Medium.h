#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "common.h"
using namespace mathLib;

#include "hittable.h"
#include "Material.h"
#include "Texture.h"


namespace rtLib
{

class Constant_Medium : public hittable
{
public:
    explicit Constant_Medium(std::shared_ptr<hittable> bound, 
        const double density, std::shared_ptr<Texture> alb)
        :  
        boundary(bound), 
        negInverseDensity(-1/density),  
        phaseFunction(std::make_shared<Isotropic>(alb))
    {}

    explicit Constant_Medium(std::shared_ptr<hittable> bound, 
        const double density, color3 col)
        :
        boundary(bound), 
        negInverseDensity(-1/density),  
        phaseFunction(std::make_shared<Isotropic>(col))
    {}

    virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    std::shared_ptr<hittable> boundary; 
    double negInverseDensity;
    std::shared_ptr<Material> phaseFunction;

};

} // namespace rtLib



#endif //CONSTANT_MEDIUM_H