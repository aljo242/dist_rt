#ifndef AXIS_ALIGNED_RECT_H
#define AXIS_ALIGNED_RECT_H

#include "hittable.h"

namespace rtLib 
{

class XY_Rect : public hittable
{
public:
    XY_Rect() = default;
    XY_Rect(const double _x0, const double _x1, const double _y0, 
        const double _y1, const double _k, std::shared_ptr<Material> mat)
            :
        x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), pMat(mat) 
    {}

    virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    double x0;
    double x1;
    double y0;
    double y1;
    double k;
    std::shared_ptr<Material> pMat;

};


class XZ_Rect : public hittable
{
public:
    XZ_Rect() = default;
    XZ_Rect(const double _x0, const double _x1, const double _z0, 
        const double _z1, const double _k, std::shared_ptr<Material> mat)
            :
        x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), pMat(mat) 
    {}

    virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    double x0;
    double x1;
    double z0;
    double z1;
    double k;
    std::shared_ptr<Material> pMat;

};


class YZ_Rect : public hittable
{
public:
    YZ_Rect() = default;
    YZ_Rect(const double _y0, const double _y1, const double _z0, 
        const double _z1, const double _k, std::shared_ptr<Material> mat)
            :
        y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), pMat(mat) 
    {}

    virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override final;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override final;

private:
    double y0;
    double y1;
    double z0;
    double z1;
    double k;
    std::shared_ptr<Material> pMat;

};


} // namespace rtLib

#endif