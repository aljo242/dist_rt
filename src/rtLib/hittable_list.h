#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"

using namespace mathLib;

namespace rtLib
{
	
class hittable_list : public hittable
{
public:
	hittable_list() = default;
	explicit hittable_list(const std::shared_ptr<hittable>& obj);

	void Clear();
	void Add(const std::shared_ptr<hittable>& obj);


	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override;

	virtual ~hittable_list() = default;


	std::vector<std::shared_ptr<hittable>> objects;
};

} // namespace rtLib

#endif