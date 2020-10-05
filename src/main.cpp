#include <fstream>
#include <iostream>
#include <optional>
#include <spdlog/spdlog.h>
#include "glm/glm.hpp"


#include <omp.h>

// typedefs
using Vec3 = glm::vec3;
using Point3 = glm::vec3;
using Color3 = glm::vec3;

constexpr float epsilon{ 0.000001f };



class Ray3
{
public:
	Ray3(const Vec3& o, const Point3& d)
		: origin(o), dir(d)
	{
		Normalize();
	}

	Ray3(const Vec3& d)
		: origin(0, 0, 0), dir(d)
	{}

	void Normalize() 
	{
		dir =  Vec3(dir.x / dir.length(), dir.y / dir.length(), dir.z / dir.length());
	}

	Vec3 Dir() const
	{
		return dir;
	}

	Point3 Origin() const
	{
		return origin;
	}

private:
	Point3 origin;
	Vec3 dir;
};


class Plane
{
public:
	// two vectors and a point 
	Plane(const Point3& origin, const Vec3& A, const Vec3& B)
	{
		const auto cross	{glm::cross(A, B)};
		norm = Ray3(origin, glm::normalize(cross));
	}

	Vec3 NormVec() const
	{ 
		return norm.Dir(); 
	}

	Point3 NormPoint() const
	{ 
		return norm.Origin(); 
	}
	
	// hold a point and norm
private:
	Ray3 norm{ {0,0,0}, {0,0,0} };
};


std::optional<Color3> IntersectPlane(const Ray3& ray, const Plane& plane)
{
	const auto planeNormal = plane.NormVec();
	const float denom{ glm::dot(planeNormal, ray.Dir()) };
	if (std::fabs(denom) > epsilon)
	{
		const float t = glm::dot((plane.NormPoint() - ray.Origin()), planeNormal) / denom;
		if (t >= 0.0f) // test if intersection is in front of camera, discard if behind
		{
			return { Color3(0.33f, 0.55f, 0.77f) };
		}
	}

	return std::nullopt;
}


int main()
{
	spdlog::critical("Hello World!");

	Ray3 testRay{ {0,0,0}, {2, 2, 2} };
	spdlog::critical("test ray norm: {} {} {}", testRay.Dir().x, testRay.Dir().y, testRay.Dir().z);
	

	Plane testPlane(Point3(5, 5, 5), Vec3(5, 0, 1), Vec3(0, 1, 0) );
	
	auto ret = IntersectPlane(testRay, testPlane);

	if (ret.has_value())
	{
		spdlog::critical("nullopt evaluate to true");
	}


	return 0;
}

