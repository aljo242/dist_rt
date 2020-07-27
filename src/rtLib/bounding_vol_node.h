#ifndef BOUNDVOL_NODE_H
#define BOUNDVOL_NODE_H
#include <spdlog/spdlog.h>

#include "hittable.h"
#include "hittable_list.h"
using namespace mathLib;

namespace rtLib
{

class BVH_Node : public hittable
{
public:
	BVH_Node() = default;

	BVH_Node(hittable_list& list, const double t0, const double t1)
		: BVH_Node(list.objects, 0, list.objects.size(), t0, t1)
 	{}

 	BVH_Node(
 		std::vector<std::shared_ptr<hittable>>& objects,
 		const size_t start, const size_t end, const double t0, const double t1);

	virtual bool Hit(const ray& r, const double t_min, 
		const double t_max, HitRecord& rec) const override;

	virtual bool BoundingBox(const double t0, const double t1, 
		AABB& outputBox) const override;

	virtual ~BVH_Node() = default;

private:
	std::shared_ptr<hittable> left;
	std::shared_ptr<hittable> right;
	AABB box;
};


inline bool BoxCompare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, const size_t axis)
{
	AABB boxA;
	AABB boxB;

	if (!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB))
	{
		spdlog::info("No bounding box in BVH_Node constuctor");
	}
	return boxA.min()[axis] < boxB.min()[axis];
}

inline bool BoxCompareX(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b)
{
	return BoxCompare(a, b, 0);
}

inline bool BoxCompareY(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b)
{
	return BoxCompare(a, b, 1);
}

inline bool BoxCompareZ(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b)
{
	return BoxCompare(a, b, 2);
}

} // namespace rtLib


#endif // BOUNDVOL_NODE_H