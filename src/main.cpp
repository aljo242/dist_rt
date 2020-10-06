#include <fstream>
#include <iostream>
#include <optional>
#include <array>
#include <vector>
#include <spdlog/spdlog.h>
#include "glm/glm.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include <omp.h>

// typedefs
using Vec3 = glm::vec3;
using Point3 = glm::vec3;
using Color3 = glm::vec3;

constexpr float epsilon{ 0.000001f };
constexpr int imageWidth{ 512 };
constexpr int imageHeight{ 512 };
constexpr int numChannels{ 3 };
constexpr int imageSize{ imageHeight * imageWidth * numChannels};


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

	const char* filename = "test_output.png";
	
	std::vector<uint8_t> image(imageSize);
	size_t index = 0;
	for (size_t i = 0; i < imageHeight * imageWidth; ++i)
	{
		size_t u = i % imageWidth;
		size_t v = i / imageHeight;
		//spdlog::critical("({}, {})", u, v);
		const auto r = static_cast<float>(u) / (imageWidth - 1);
		const auto g = static_cast<float>(v) / (imageHeight - 1);
		const auto b = 0.25f;

		const auto ir = static_cast<uint8_t>(255.99f * r);
		const auto ig = static_cast<uint8_t>(255.99f * g);
		const auto ib = static_cast<uint8_t>(255.99f * b);

		image[index++] = ir;
		image[index++] = ig;
		image[index++] = ib;
	}
	

	spdlog::critical("Writing to file: {}", filename);
	stbi_write_png(filename, imageWidth, imageHeight, numChannels, image.data(), imageWidth*numChannels);

	return 0;
}

