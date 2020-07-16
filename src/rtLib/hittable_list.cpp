#include "hittable_list.h"


using namespace mathLib;

using namespace rtLib;

hittable_list::hittable_list(const std::shared_ptr<hittable>& obj) {Add(obj);}

void hittable_list::Clear() {objects.clear();}

void hittable_list::Add(const std::shared_ptr<hittable>& obj) {objects.push_back(obj);}

bool hittable_list::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const 
{
	HitRecord tempRec;
	auto hitAnything 		{false};
	auto closestSoFar 		{t_max};

	for (const auto& obj : objects)
	{
		if (obj->Hit(r, t_min, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

