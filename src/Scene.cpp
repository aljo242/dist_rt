#include <string>
#include <memory>

#include "Texture.h"
#include "Material.h"
#include "sphere.h"
#include "Box.h"
#include "Translate.h"
#include "Rotate.h"
#include "Constant_Medium.h"
#include "bounding_vol_node.h"

#include "Scene.h"

using namespace mathLib;
using namespace rtLib;


const std::string resFilePath {".."};

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


hittable_list Earth()
{
	hittable_list world;

	const auto earthTex 		{std::make_shared<Image_Tex>("earthmap.jpg")};
	const auto earthSurface 	{std::make_shared<Lambertian>(earthTex)};
	const auto globe			{std::make_shared<sphere>(point3(0,0,0), 2, earthSurface)};
	world.Add(globe);

	return world;
}


hittable_list SimpleLight()
{
	hittable_list world;

	const auto perlinTex		{std::make_shared<Perlin_Noise>(4)};
	world.Add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(perlinTex)));
	world.Add(std::make_shared<sphere>(point3(0, 2, 0), 2, std::make_shared<Lambertian>(perlinTex)));

	const auto diffLight		{std::make_shared<Diffuse_Light>(color3(4,4,4))};
	world.Add(std::make_shared<sphere>(point3(0, 7, 0), 1, diffLight));
	world.Add(std::make_shared<XY_Rect>(3, 5, 1, 3, -2, diffLight));

	return world;
}


hittable_list CornellBox()
{
	hittable_list world;

	auto red		{std::make_shared<Lambertian>(color3(0.65, 0.05, 0.05))};
	auto white		{std::make_shared<Lambertian>(color3(0.73, 0.73, 0.73))};
	auto green		{std::make_shared<Lambertian>(color3(0.12, 0.45, 0.15))};
	auto light		{std::make_shared<Diffuse_Light>(color3(15, 15, 15))};

	world.Add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
	world.Add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
	world.Add(std::make_shared<XZ_Rect>(213, 343, 227, 332, 554, light));
	world.Add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
	world.Add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
	world.Add(std::make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

	std::shared_ptr<hittable> Box1 	{std::make_shared<Box>(point3(0,0,0), point3(165, 330, 165), white)};
	Box1 = 			std::make_shared<Rotate_Y>(Box1, 15.0);
	Box1 = 			std::make_shared<Translate>(Box1, vec3(265, 0, 295));
	world.Add(Box1);

	std::shared_ptr<hittable> Box2 	{std::make_shared<Box>(point3(0,0,0), point3(165, 165, 165), white)};
	Box2 = 			std::make_shared<Rotate_Y>(Box2, -18.0);
	Box2 = 			std::make_shared<Translate>(Box2, vec3(130, 0, 65));
	world.Add(Box2);

	return world;
}


hittable_list CornellSmoke()
{
	hittable_list world;

	auto red		{std::make_shared<Lambertian>(color3(0.65, 0.05, 0.05))};
	auto white		{std::make_shared<Lambertian>(color3(0.73, 0.73, 0.73))};
	auto green		{std::make_shared<Lambertian>(color3(0.12, 0.45, 0.15))};
	auto light		{std::make_shared<Diffuse_Light>(color3(5, 5, 5))};

	world.Add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
	world.Add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
	world.Add(std::make_shared<XZ_Rect>(113, 443, 127, 432, 554, light));
	world.Add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
	world.Add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
	world.Add(std::make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

	std::shared_ptr<hittable> Box1 	{std::make_shared<Box>(point3(0,0,0), point3(165, 330, 165), white)};
	Box1 = 			std::make_shared<Rotate_Y>(Box1, 15.0);
	Box1 = 			std::make_shared<Translate>(Box1, vec3(265, 0, 295));

	std::shared_ptr<hittable> Box2 	{std::make_shared<Box>(point3(0,0,0), point3(165, 165, 165), white)};
	Box2 = 			std::make_shared<Rotate_Y>(Box2, -18.0);
	Box2 = 			std::make_shared<Translate>(Box2, vec3(130, 0, 65));

	world.Add(std::make_shared<Constant_Medium>(Box1, 0.01, color3(0,0,0)));
	world.Add(std::make_shared<Constant_Medium>(Box2, 0.01, color3(1,1,1)));

	return world;
}


hittable_list CrazyScene()
{
	hittable_list boxes1;
	const auto ground 	{std::make_shared<Lambertian>(color3(0.48, 0.83, 0.53))};

	constexpr int boxesPerSide		{20};
	for (int i = 0; i < boxesPerSide; ++i)
	{
		for (int j = 0; j < boxesPerSide; ++j)
		{
			constexpr auto w	{100.0};
			const auto x0		{-1000.0 + i*w};
			const auto z0		{-1000.0 + j*w};
			constexpr auto y0 	{0.0};
			const auto x1		{x0 + w};
			const auto y1		{RandDouble(1, 101)};
			const auto z1 		{z0 + w};

			boxes1.Add(std::make_shared<Box>(point3(x0, y0, z0), point3(x1, y1, z1), ground));
		}
	}

	hittable_list world;

	world.Add(std::make_shared<BVH_Node>(boxes1, 0, 1));

	const auto light 			{std::make_shared<Diffuse_Light>(color3(7, 7, 7))};
	world.Add(std::make_shared<XZ_Rect>(123, 423, 147, 412, 554, light));

	const auto center1 			{point3(400, 400, 200)};
	const auto center2			{point3(center1 + vec3(30, 0, 0))};
	const auto movingSphereMat	{std::make_shared<Lambertian>(color3(0.7, 0.3, 0.1))};
	world.Add(std::make_shared<moving_sphere>(center1, center2, 0, 1, 50, movingSphereMat));

	world.Add(std::make_shared<sphere>(point3(260, 150, 45), 50, std::make_shared<Dielectric>(1.5)));
	world.Add(std::make_shared<sphere>(point3(0, 150, 145), 50, std::make_shared<Metal>(color3(0.8, 0.8, 0.9), 10.0)));

	auto boundary 			{std::make_shared<sphere>(point3(360, 150, 145), 70, std::make_shared<Dielectric>(1.5))};
	world.Add(boundary);
	world.Add(std::make_shared<Constant_Medium>(boundary, 0.2, color3(0.2, 0.4, 0.9)));
	boundary = 				std::make_shared<sphere>(point3(0, 0, 0), 5000, std::make_shared<Dielectric>(1.5));
	world.Add(std::make_shared<Constant_Medium>(boundary, .0001, color3(1, 1, 1)));

	const auto eMat				{std::make_shared<Lambertian>(std::make_shared<Image_Tex>("earthmap.jpg"))};
	world.Add(std::make_shared<sphere>(point3(400, 200, 400), 100, eMat));
	const auto perlinTex		{std::make_shared<Perlin_Noise>(0.1)};
	world.Add(std::make_shared<sphere>(point3(220, 280, 300), 80, std::make_shared<Lambertian>(perlinTex)));

	hittable_list boxes2;
	const auto white 			{std::make_shared<Lambertian>(color3(.73, .73, .73))};
	constexpr int numSamples	{1000};
	for (int j = 0; j < numSamples; ++j)
	{
		boxes2.Add(std::make_shared<sphere>(point3::Random(0, 165), 10, white));
	}
	world.Add(std::make_shared<Translate>(
		std::make_shared<Rotate_Y>(
			std::make_shared<BVH_Node>(boxes2, 0.0, 1.0), 15),
			vec3(-100, 270, 395))
	);

	return world;
}