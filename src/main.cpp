#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

#include "color.h"
#include "common.h"
using namespace mathLib;

#include "camera.h"
#include "casting.h"
#include "Scene.h"
#include "Material.h"
using namespace rtLib;

#include <omp.h>


color3 RayColor(const ray& r, const color3& background, const hittable& world, const int depth)
{
	HitRecord rec;

	// if depth exceeded, no more light is gathered
	if (depth <= 0)
	{
		return color3(0.0, 0.0, 0.0);
	}

	if(!world.Hit(r, 0.001, infinity, rec))
	{
		return background;
	}

	ray scattered;
	color3 attenuation;
	color3 emitted 		{rec.pMat->Emitted(rec.u, rec.v, rec.p)};

	if (!rec.pMat->Scatter(r, rec, attenuation, scattered))
	{
		return emitted;
	}

	return emitted + attenuation * RayColor(scattered, background, world, depth - 1);
}


int main()
{
	double aspectRatio 					{16.0 / 9.0};
	int imageW 							{1280};
	const std::string fileName			{"output.ppm"};
	int samplesPerPixel 				{200};
	constexpr int maxDepth 				{50};
	color3 background(0,0,0);			// black background

	spdlog::info("Writing to file {}...", fileName);

	point3 lookfrom;
	point3 lookat;

	auto aperture 					{0.0};
	double FOV						{20};
	int chooseWorld 				{0};

	spdlog::info("Choose the world to generate:\n\n(1)\tLarge world with many objects\n(2)\tSmall world with 2 textured spheres\n(3)\tEarth textured sphere\n(4)\tLight emitting test\n(5)\tCornell Box scene\n(6)\tCornell Box with SMOKE\n(7)\tCrazy Scene");
	std::cin >> chooseWorld;
	hittable_list world;

	switch(chooseWorld)
	{
		spdlog::info({}, chooseWorld);
		case 1:
			spdlog::info("(1)\tLarge world with many objects");
			world = 				GenerateRandomScene();
			background = 			color3(0.7, 0.8, 1.0);
			lookfrom =				point3(13, 2, 3);
			lookat = 				point3(0, 0, 0);
			FOV =					20.0;
			aperture = 				0.1;
			break;
		case 2:
			spdlog::info("(2)\tSmall world with 2 textured spheres");
			world = 				TwoPerlinSpheres();
			background = 			color3(0.7, 0.8, 1.0);
			lookfrom =				point3(13, 2, 3);
			lookat = 				point3(0, 0, 0);
			FOV =					20.0;
			break;
		case 3:
			spdlog::info("(3)\tEarth textured sphere");
			background = 			color3(0.7, 0.8, 1.0);
			world = 				Earth();
			lookfrom = 				point3(0, 0, 12);
			lookat =				point3(0, 0, 0);
			FOV = 					20.0;
			break;
		case 4:
			spdlog::info("(4)\tLight emitting test");
			world = 				SimpleLight();
			samplesPerPixel = 		500;
			background =			color3(0,1.0,0);
			lookfrom =				point3(26, 3, 6);
			lookat = 				point3(0, 2, 0);
			FOV =					20.0;
			break;
		default:
		case 5:
			spdlog::info("(5)\tCornell Box scene");
			world = 				CornellBox();
			samplesPerPixel = 		2000;
			aspectRatio =			1.0;
			imageW = 				600;
			//background =			color3(0,0,0);
			lookfrom =				point3(278, 278, -800);
			lookat = 				point3(278, 278, 0);
			FOV = 					40.0;
			break;
		case 6:
			spdlog::info("(6)\tCornell Box with SMOKE");
			world = 				CornellSmoke();
			samplesPerPixel = 		2000;
			aspectRatio =			1.0;
			imageW = 				600;
			//background =			color3(0,0,0);
			lookfrom =				point3(278, 278, -800);
			lookat = 				point3(278, 278, 0);
			FOV = 					40.0;
			break;
		case 7:
			spdlog::info("(7)\tCrazy Scene");
			world = 				CrazyScene();
			aspectRatio	=			1.0;
			imageW =				800;
			samplesPerPixel	=		20000;
			background =			color3(0, 0, 0);
			lookfrom = 				point3(478, 278, -600);
			lookat = 				point3(278, 278, 0);
			FOV = 					40.0;
		break;		
	}	

	int imageH 							{static_cast<int>(imageW / aspectRatio)};
	const vec3 vup(0,1,0);
	auto dist_to_focus 				{10};
	camera cam(lookfrom, lookat, vup, FOV, aspectRatio, aperture, dist_to_focus, T0, T1);

	std::ofstream oFile(fileName);
	oFile << "P3\n" << imageW << ' ' << imageH << ' ' << "\n255\n";

	#pragma omp parallel
	{
		spdlog::info("{} OMP threads\n", omp_get_num_threads());
	}

	for (int j = imageH - 1; j >= 0; --j)
	{
		spdlog::info("Scanline completed: {}", j);
		for (int i = 0; i < imageW; ++i)
		{
			color3 pixCol(0.0, 0.0, 0.0);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				const double u 		{ (i + RandDouble()) / (imageW - 1) };
				const double v 		{ (j + RandDouble()) / (imageH - 1) };
				const ray r 		{cam.GetRay(u, v)};
				pixCol += RayColor(r, background, world, maxDepth);
			}
			WriteColor(oFile, pixCol, samplesPerPixel);
		}
	}

	spdlog::info("Closing file {}...", fileName);
	oFile.close();
	return 0;
}


