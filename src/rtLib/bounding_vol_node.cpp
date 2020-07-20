#include "bounding_vol_node.h"

#include "common.h"
using namespace mathLib;


rtLib::BVH_Node::BVH_Node(
 	std::vector<std::shared_ptr<hittable>>& objects,
 	const size_t start, const size_t end, const double t0, const double t1)
 {
 	const int axis {RandomInt(0,2)};
 	auto comparator {(axis == 0) ? BoxCompareX
 					: (axis == 1) ? BoxCompareY
 					: BoxCompareZ };

 	const size_t objectSpan {end - start};

 	if (objectSpan == 1)
 	{
 		left = right = objects[start];
 	}
 	else if (objectSpan == 2)
 	{
 		if (comparator(objects[start], objects[start+1]))
 		{
 			left = 		objects[start];
 			right = 	objects[start+1];
 		}
 		else
 		{
 			left = 		objects[start+1];
 			right = 	objects[start];
 		}
 	}
 	else
 	{
 		std::sort(objects.begin() + start, objects.begin() + end, comparator);

 		const auto mid 	{start + objectSpan/2};
 		left = std::make_shared<BVH_Node>(objects, start, mid, t0, t1);
 		right = std::make_shared<BVH_Node>(objects, mid, end, t0, t1);
 	}

 	AABB boxLeft;
 	AABB boxRight;

 	if (!left->BoundingBox(t0, t1, boxLeft) || !right->BoundingBox(t0, t1, boxRight))
 	{
 		spdlog::info("No bounding box in BVH_Node constuctor");
 	}

 	box = SurroundingBox(boxLeft, boxRight);
 }



bool rtLib::BVH_Node::Hit(const ray& r, const double t_min, 
	const double t_max, HitRecord& rec) const
{
	if (!box.Hit(r, t_min, t_max))
	{
		return false;
	}

	const bool hitLeft 	{left->Hit(r, t_min, t_max, rec)};
	const bool hitRight	{right->Hit(r, t_min, hitLeft ? rec.t : t_max, rec)};

	return hitLeft || hitRight;
}

bool rtLib::BVH_Node::BoundingBox(const double t0, const double t1, 
	AABB& outputBox) const
{
	outputBox = box;
	return true;
}