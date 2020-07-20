#include "bounding.h"

using namespace mathLib;

AABB mathLib::SurroundingBox(const AABB& box0, const AABB& box1)
{
	point3 small(std::fmin(box0.min().x(), box1.min().x()),
				 std::fmin(box0.min().y(), box1.min().y()),
				 std::fmin(box0.min().z(), box1.min().z())
				 );

	point3 big(std::fmax(box0.max().x(), box1.max().x()),
				std::fmax(box0.max().y(), box1.max().y()),
				std::fmax(box0.max().z(), box1.max().z())
				);

	return {small, big};

}

