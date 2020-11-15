#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "defs.h"

class Transform
{
public:
	Transform();
	Transform(const Mat4& mat);
	Transform(const Mat4& mat, const Mat4& inv);

	void Print() const;
	friend Transform Inverse(const Transform& t);
	friend Transform Transpose(const Transform& t);

	bool operator==(const Transform& t) const;
	bool operator!=(const Transform& t) const;
	bool operator<(const Transform& t) const;
	bool IsIdentity() const;

	const Mat4& GetMatrix(); const;
	const Mat4& GetInverseMatrix() const;
	
	bool HasScale() const;
	
	inline Point3 operator()(const Point3& p) const;
	inline Vec3 operator()(const Vec3& v) const;
	inline Ray3 operator()(const Ray3& r) const;
	inline RayDifferential3 operator()(const RayDifferential3& rd) const;
	Bounds3 operator()(const Bounds3& b) const;

	Transform operator*(const Transform& t2) const;
	bool SwapHandedness() const;

private:
	Mat4 m;
	Mat4 mInv;
	friend class AnimatedTransform;
	friend struct Quaternion;
};


#endif // TRANSFORM_H

