#ifndef BOUNDS_H
#define BOUNDS_H

#include <limits>
#include <algorithm>
#include "defs.h"

class Bounds2
{
public:
	Bounds2();
	Bounds2(const Point2& p);
	Bounds2(const Point2& p1, const Point2& p2);

	Vec2 Diagonal() const;
	float Area() const;
	int32_t MaximumExtent() const;

	inline Point2& operator[](int32_t i);
	bool operator==(const Bounds2& b) const;
	bool operator!=(const Bounds2& b) const;

	Point2 Lerp(const Point2& t) const;

	Vec2 Offset(const Point2& p) const;
	void BoundingSphere(Point2* c, float* rad) const;


public:
	Point2 pMin;
	Point2 pMax;
};

class Bounds3
{
public:
	Bounds3();
	Bounds3(const Point3& p);
	Bounds3(const Point3& p1, const Point3& p2);

	Point3 Corner(int32_t corner) const;
	Vec3 Diagonal() const;
	float SurfaceArea() const;
	float Volume() const;
	int32_t MaximumExtent() const;

	const Point3& operator[](int32_t i) const;
	Point3& operator[](int32_t i);
	bool operator==(const Bounds3& b) const;
	bool operator!=(const Bounds3& b) const;

	Point3 Lerp(const Point3& t) const;

	Vec3 Offset(const Point3& p) const;
	void BoundingSphere(Point3* c, float* rad) const;
	bool IntersectP(const Ray3& ray, float* hitt0 = nullptr, float* hitt1 = nullptr) const;
	inline bool IntersectP(const Ray3& ray, const Vec3& invDir, const int32_t dirIsNeg[3]) const;

public:
	Point3 pMin;
	Point3 pMax;
};


inline Bounds3 Union(const Bounds3& b, const Point3& p)
{
	return {
		Point3(std::min(b.pMin.x, p.x),
			std::min(b.pMin.y, p.y),
			std::min(b.pMin.z, p.z)),
		Point3(std::max(b.pMin.x, p.x),
			std::max(b.pMin.y, p.y),
			std::max(b.pMin.z, p.z))
	};
}

inline Bounds3 Union(const Bounds3& b1, const Bounds3& b2)
{
	return {
		Point3(std::min(b1.pMin.x, b2.pMin.x),
			std::min(b1.pMin.y, b2.pMin.y),
			std::min(b1.pMin.z, b2.pMin.z)),
		Point3(std::max(b1.pMin.x, b2.pMax.x),
			std::max(b1.pMin.y, b2.pMax.y),
			std::max(b1.pMin.z, b2.pMax.z))
	};
}

inline Bounds3 Intersect(const Bounds3& b1, const Bounds3& b2)
{
	return {
		Point3(std::max(b1.pMin.x, b2.pMin.x),
			std::max(b1.pMin.y, b2.pMin.y),
			std::max(b1.pMin.z, b2.pMin.z)),
		Point3(std::min(b1.pMin.x, b2.pMax.x),
			std::min(b1.pMin.y, b2.pMax.y),
			std::min(b1.pMin.z, b2.pMax.z))
	};
}

inline bool Overlaps(const Bounds3& b1, const Bounds3& b2)
{
	const bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
	const bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
	const bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
	return (x && y && z);
}

inline bool Inside(const Point3& p, const Bounds3& b)
{
	return (p.x >= b.pMin.x && p.x <= b.pMax.x &&
		p.y >= b.pMin.y && p.y <= b.pMax.y &&
		p.z >= b.pMin.z && p.z <= b.pMax.z);
}

inline Bounds3 Expand(const Bounds3& b, const float delta)
{
	return { b.pMin - Vec3(delta, delta, delta),
		b.pMax + Vec3(delta, delta, delta) };
}

#endif // BOUNDS_H