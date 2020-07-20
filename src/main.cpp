#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

#include "color.h"
#include "common.h"
#include "ray.h"
#include "vec3.h"
using namespace mathLib;

#include "Material.h"
#include "Texture.h"
#include "camera.h"
#include "casting.h"
#include "hittable_list.h"
#include "sphere.h"
using namespace rtLib;

constexpr double T0 {0.0};
constexpr double T1 {1.0};

hittable_list GenerateRandomScene()
{
	hittable_list world;
	const auto checkerFloor {std::make_shared<CheckerBoard>(
		std::make_shared<Solid_Color>(0.2, 0.3, 0.1),
		std::make_shared<Solid_Color>(0.9, 0.9, 0.9)
		)};

	const auto groundMat {std::make_shared<Lambertian>(checkerFloor)};
	world.Add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, groundMat));

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			const auto chooseMat {RandDouble()};
			const point3 center(a + 0.9*RandDouble(), 0.2, b + 0.9*RandDouble());

			if ((center - point3(4, 0.2, 0)).Length() > 0.9)
			{
				std::shared_ptr<Material> sphereMat;

				if (chooseMat < 0.8)
				{
					// lambertian
					const auto al 	{color3::Random() * color3::Random()};
					sphereMat = std::make_shared<Lambertian>(std::make_shared<Solid_Color>(al.r(), al.g(), al.b()));

					const auto center2	{center + vec3(0.0, RandDouble(0.0, 0.5), 0.0)};
					world.Add(std::make_shared<moving_sphere>(center, center2, T0, T1, 0.2, sphereMat));
				}
				else if (chooseMat < 0.95)
				{
					// metal
					const auto albedo 	{color3::Random(0.5, 1)};
					const auto fuzz 	{RandDouble(0, 0.5)};
					sphereMat = std::make_shared<Metal>(albedo, fuzz);
					world.Add(std::make_shared<sphere>(center, 0.2, sphereMat));
				}
				else
				{
					// dielectric
					sphereMat = std::make_shared<Dielectric>(1.5);
					world.Add(std::make_shared<sphere>(center, 0.2, sphereMat));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(std::make_shared<Solid_Color>(0.4, 0.2, 0.1));
    world.Add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color3(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));


	return world;
}


hittable_list TwoPerlinSpheres()
{
	hittable_list world;

	const auto perlinTex 	{std::make_shared<Perlin_Noise>(10)};
	world.Add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(perlinTex)));
	world.Add(std::make_shared<sphere>(point3(0, 2, 0), 2, std::make_shared<Lambertian>(perlinTex)));

	return world;
}


color3 RayColor(const ray& r, const hittable& world, const int depth)
{
	HitRecord rec;

	// if depth exceeded, no more light is gathered
	if (depth <= 0)
	{
		return color3(0.0, 0.0, 0.0);
	}


	if (world.Hit(r, 0.001, infinity, rec))
	{
		ray scattered;
		color3 attenuation;
		if (rec.pMat->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * RayColor(scattered, world, depth - 1);
		}
		return color3(0.0, 0.0, 0.0);
	}

	const vec3 unitDir 	{UnitVector(r.Direction())};
	const auto t 		{ 0.5 * (unitDir.y() + 1.0)};
	return (1.0 - t) * color3(1.0, 1.0, 1.0) + t * color3(0.5, 0.7, 1.0);
}


int main()
{
	constexpr double aspectRatio 		{16.0 / 9.0};
	constexpr int imageW 				{1280};
	constexpr int imageH 				{static_cast<int>(imageW / aspectRatio)};
	const std::string fileName			{"output.ppm"};
	constexpr int samplesPerPixel 		{100};
	constexpr int maxDepth 				{50};

	spdlog::info("Writing to file {}...", fileName);

	std::ofstream oFile(fileName);

	oFile << "P3\n" << imageW << ' ' << imageH << ' ' << "\n255\n";

	auto world {TwoPerlinSpheres()};
	
	const point3 lookfrom(13,2,3);
	const point3 lookat(0,0, 0);
	const vec3 vup(0,1,0);
	constexpr auto dist_to_focus 	{10};
	constexpr auto aperture 		{0.0};
	constexpr double FOV			{20};

	camera cam(lookfrom, lookat, vup, FOV, aspectRatio, aperture, dist_to_focus, T0, T1);

	for (int j = imageH; j > 0; --j)
	{
		spdlog::info("Scanlines remaining: {}\n", j);
		for (int i = 0; i < imageW; ++i)
		{
			color3 pixCol(0.0, 0.0, 0.0);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				const double u 		{ (i + RandDouble()) / (imageW - 1) };
				const double v 		{ (j + RandDouble()) / (imageH - 1) };
				const ray r 		{cam.GetRay(u, v)};
				pixCol += RayColor(r, world, maxDepth);
			}
			WriteColor(oFile, pixCol, samplesPerPixel);
		}
	}

	spdlog::info("Closing file {}...", fileName);
	oFile.close();
	return 0;
}


