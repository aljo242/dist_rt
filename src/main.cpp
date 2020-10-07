#include <fstream>
#include <iostream>
#include <optional>
#include <array>
#include <vector>
#include <spdlog/spdlog.h>
#include "defs.h"

#include <omp.h>

#include "Ray.h"
#include "Plane.h"
#include "Image.h"
#include "Sphere.h"

constexpr float epsilon{ 0.000001f };
constexpr auto aspectRatio{ 16.0f / 9.0f };
constexpr int imageWidth{ 1280 };
constexpr int imageHeight{ static_cast<int>(imageWidth / aspectRatio) };
constexpr int numChannels{ 3 };
constexpr int imageSize{ imageHeight * imageWidth * numChannels};

constexpr auto viewportHeight{ 2.0f };
constexpr auto viewportWidth{ viewportHeight * aspectRatio };


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

Color3 RayColor(const Ray3& ray, const Sphere& s)
{
	Vec3 dir = ray.Dir(); // ray returns normalized vectors
	const auto t = 0.5f * (dir.y + 1.0f);

	if (s.testIntersect(ray, 0, infinity))
	{
		const auto N = ray.At(t) - Vec3(0, 0, -1);
		return 0.5f * Color3(N.x + 1, N.y + 1, N.z + 1);
	}

	return {(1.0f - t) * Color3(1.0f, 1.0f, 1.0f) + t * Color3(0.5f, 0.7f, 1.0f)};
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

	const auto origin = Point3(0, 0, 0);
	const auto horizontal = Vec3(viewportWidth, 0, 0);
	const auto vertical = Vec3(0, viewportHeight, 0);
	const auto leftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, 1.0);

	Sphere testSphere(Point3(0.0, 0.0, -1.0), 0.5f);
	
	std::vector<uint8_t> image(imageSize);
	size_t index = 0;

	for (int j = 0; j < imageHeight; ++j)
	{
		for (int i = 0; i < imageWidth; ++i)
		{
			const auto u = static_cast<float>(i) / (imageWidth - 1);
			const auto v = static_cast<float>(j) / (imageHeight - 1);

			Color3 pixelColor;
			Ray3 r(origin, leftCorner + u * horizontal + v * vertical - origin);

			pixelColor = RayColor(r, testSphere);


			const auto ir = static_cast<uint8_t>(255.99f * pixelColor.r);
			const auto ig = static_cast<uint8_t>(255.99f * pixelColor.g);
			const auto ib = static_cast<uint8_t>(255.99f * pixelColor.b);

			/*
			spdlog::critical("(i, j) = ({}, {})", i, j);
			spdlog::critical("(u, v) = ({}, {})", u, v);
			spdlog::critical("Color = ({}, {}, {})", ir, ig, ib);
			*/

			image[index++] = ir;
			image[index++] = ig;
			image[index++] = ib;
		}
	}
	
	writePNG(filename, imageWidth, imageHeight, numChannels, image);

	return 0;
}

