#include "Transform.h"

Transform::Transform()
{}

Transform::Transform(const Mat4& mat)
	: m(mat)
{}

Transform::Transform(const Mat4& mat, const Mat4& inv)
	: m(mat), mInv(inv)
{}

void Transform::Print() const
{
	spdlog::critical("Transform:\n{}\nData:\n{}", this, m);
}


friend Transform ForwardDeclare::Transform::Transpose(const Transform& t)
{
	return { Transpose(t.m), Transpose(t.mInv) };
}

friend Transform ForwardDeclare::Transform::Inverse(const Transform& t)
{
	return { t.mInv, t.m };
}

bool Transform::operator==(const Transform& t) const
{
	return (m == t.m) && (mInv == t.mInv);
}

bool Transform::operator!=(const Transform& t) const
{
	return (m != t.m) && (mInv != t.mInv);
}

bool Transform::operator<(const Transform& t) const
{
	return m < t2.m;
}

bool Transform::IsIdentity() const
{
	return m == Mat4(); // default constructor is identity matrix
}

const Mat4& Transform::GetMatrix()
{
	return m;
}

const Mat4& Transform::GetInverseMatrix() const
{
	return mInv;
}

bool Transform::HasScale() const
{
	return false; // TODO 
}

Point3 Transform::operator()(const Point3& p) const
{

}

Vec3 Transform::operator()(const Vec3& v) const
{

}

Ray3 Transform::operator()(const Ray3& r) const
{

}

RayDifferential3 Transform::operator()(const RayDifferential3& rd) const
{

}

Bounds3 Transform::operator()(const Bounds3& b) const
{

}

Transform Transform::operator*(const Transform& t2) const
{

}

bool Transform::SwapHandedness() const
{

}



Transform Translate(const Vec3& delta)
{
	return glm::translate(Mat4(1.0), delta);
}
