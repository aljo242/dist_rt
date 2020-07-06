#include <cfloat>
#include <iostream>
#include <fstream>
#include <string>
#include <spdlog/spdlog.h>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "rng.h"

using namespace mathLib;
using namespace rtLib;



vec3 random_in_unit_sphere()
{
	rando rand;
	vec3 p;
	do 
	{
		p = 2.0 * vec3(static_cast<float>(rand.genRand()), 
			static_cast<float>(rand.genRand()),
			static_cast<float>(rand.genRand())) - vec3(1.0f, 1.0f, 1.0f);
	}   while (p.squared_length() >= 1.0f);
	return p;
}



vec3 color(const ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.001f, MAXFLOAT, rec))
	{
		vec3 target {rec.p + rec.normal + random_in_unit_sphere()};
		return 0.5f * color(ray(rec.p, target-rec.p), world);
	}
	else
	{
		vec3 unit_direction {unit_vector(r.direction())};
		const float t {0.5f * (unit_direction.y() + 1.0f)};
		return ((1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f));
	}
}







int main()
{
	constexpr int nx {1600};
	constexpr int ny {800};
	constexpr int ns {200};
	constexpr float pixelValScale {255.9999f};
	const std::string fileName("output.ppm");


	spdlog::info("Writing to file: {}...", fileName);
	std::ofstream oFile(fileName);
	oFile << "P3\n" << nx << " " << ny <<"\n255\n";

	hitable* list[2];
	{
		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);
	}
	hitable* world = new hitable_list(list, 2);

	camera cam;
	rando rand;


	//randomizer rand;
	uint64_t counter {0};
	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i <nx; ++i)
		{
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; ++s)
			{
				const float u {(static_cast<float>(i + rand.genRand()))/ static_cast<float>(nx)};
				const float v {(static_cast<float>(j + rand.genRand()))/ static_cast<float>(ny)};
				const ray r {cam.get_ray(u, v)};
				//vec3 p 			{r.point_at_parameter(2.0f)};
				col += color(r, world);
				
			}
			counter += ns;

			col /= static_cast<float>(ns);
			col = vec3(std::sqrt(col.r()), std::sqrt(col.g()), std::sqrt(col.b()));
			const int ir 	{static_cast<int>(pixelValScale*col.r())};
			const int ig 	{static_cast<int>(pixelValScale*col.g())};
			const int ib 	{static_cast<int>(pixelValScale*col.b())};

			oFile << ir << " " << ig << " " << ib << "\n";
		}
		if ((j % 100) == 0 )
		{
			spdlog::info("Completed iter: {}", counter);
		}
	}
	oFile.close();
	spdlog::info("Closing file: {}", fileName);
	{ // cleanup
		delete list[0];
		delete list[1];
		delete world;
	}

	return 0;
} 