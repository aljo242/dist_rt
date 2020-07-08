#include "hitable_list.h"


using namespace mathLib;

using namespace rtLib;

bool hitable_list::hit(const ray& r, const float t_min, 
		const float t_max, hit_record& rec) const 
{
	hit_record temp_rec;
	bool hit_anything {false};
	float closest_so_far {t_max};
	for (size_t i = 0; i < list_size; ++i)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}