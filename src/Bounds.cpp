#include "Bounds.h"
#include <algorithm>

Bounds2::Bounds2()
{
	constexpr auto minNum = std::numeric_limits<float>::lowest();
	constexpr auto maxNum = std::numeric_limits<float>::max();
	pMin = Point2(maxNum, minNum);
	pMax = Point2(minNum, minNum); // init to invalid state
}

Bounds2::Bounds2(const Point2& p)
	: pMin(p), pMax(p)
{}

Bounds2::Bounds2(const Point2& p1, const Point2& p2)
{
	pMin = Point2(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
	pMax = Point2(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
}

Vec2 Bounds2::Diagonal() const
{
	return pMax - pMin;
}

float Bounds2::Area() const
{
	const auto diag = pMax - pMin;
	return (diag.x * diag.y);
}

int32_t Bounds2::MaximumExtent() const
{
	const auto diag = pMax - pMin;
	if (diag.x > diag.y) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

Point2& Bounds2::operator[](int32_t i)
{
	assert(i == 0 || i == 1);
	return (i == 0) ? pMin : pMax;
}

Point2 Bounds2::Lerp(const Point2& t) const
{
	return Point2(glm::mix(pMin.x, pMax.x, t.x), glm::mix(pMin.y, pMax.y, t.y));
}

Vec2 Bounds2::Offset(const Point2& p) const
{
	auto o = p - pMin;
	if (pMax.x > pMin.x)
	{
		o.x /= pMax.x - pMin.x;
	}
	if (pMax.y > pMin.y)
	{
		o.y /= pMax.y - pMin.y;
	}
	
	return o;
}

void Bounds2::BoundingSphere(Point2* c, float* rad) const
{
	// TODO
}

bool Bounds2::operator!=(const Bounds2& b) const
{
	return (b.pMin != pMin) || (b.pMax != pMax);
}

bool Bounds2::operator==(const Bounds2& b) const
{
	return (b.pMin == pMin) && (b.pMax == pMax);
}


//////////////////////////////////////////////////


Bounds3::Bounds3()
{
	constexpr auto minNum = std::numeric_limits<float>::lowest();
	constexpr auto maxNum = std::numeric_limits<float>::max();
	pMin = Point3(maxNum, maxNum, maxNum);
	pMax = Point3(minNum, minNum, minNum); // init to invalid state
}

Bounds3::Bounds3(const Point3& p)
	: pMin(p), pMax(p)
{}

Bounds3::Bounds3(const Point3& p1, const Point3& p2)
{
	pMin = Point3(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
	pMax = Point3(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
}

Point3 Bounds3::Corner(int32_t corner) const
{
	return Point3((*this)[(corner & 1)].x,
		(*this)[(corner & 2) ? 1 : 0].y,
		(*this)[(corner & 4) ? 1 : 0].z);
}

Vec3 Bounds3::Diagonal() const
{
	return pMax - pMin;
}

float Bounds3::SurfaceArea() const
{
	auto d = pMax - pMin;
	return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
}

float Bounds3::Volume() const
{
	auto d = pMax - pMin;
	return d.x * d.y * d.z;
}

int32_t Bounds3::MaximumExtent() const
{
	auto d = pMax - pMin;
	if (d.x > d.y && d.x > d.z)
	{
		return 0;
	}
	else if (d.y > d.z)
	{
		return 1;
	}
	
	return 2;
}

Point3& Bounds3::operator[](int32_t i)
{
	assert(i == 0 || i == 1);
	return (i == 0) ? pMin : pMax;
}

const Point3& Bounds3::operator[](int32_t i) const
{
	assert(i == 0 || i == 1);
	return (i == 0) ? pMin : pMax;
}

Point3 Bounds3::Lerp(const Point3& t) const
{
	return {
		glm::mix(pMin.x, pMax.x, t.x),
		glm::mix(pMin.y, pMax.y, t.y),
		glm::mix(pMin.z, pMax.z, t.z)
	};
}

Vec3 Bounds3::Offset(const Point3& p) const
{
	auto o = p - pMin;
	if (pMax.x > pMin.x)
	{
		o.x /= pMax.x - pMin.x;
	}
	if (pMax.y > pMin.y)
	{
		o.y /= pMax.y - pMin.y;
	}
	if (pMax.z > pMin.z)
	{
		o.z /= pMax.z - pMin.z;
	}
	
	return o;
}

void Bounds3::BoundingSphere(Point3* c, float* rad) const
{
	*c = (pMin + pMax) / 2.0f;
	*rad = Inside(*c, *this) ? Distance(*c, pMax) : 0;
}


bool Bounds3::operator!=(const Bounds3& b) const
{
	return b.pMin != pMin || b.pMax != pMax;
}

bool Bounds3::operator==(const Bounds3& b) const
{
	return b.pMin == pMin && b.pMax == pMax;
}
