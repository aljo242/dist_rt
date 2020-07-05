#include <cfloat>
#include <iostream>
#include <fstream>
#include <string>
#include <spdlog/spdlog.h>
#include "sphere.h"
#include "hitable_list.h"

using namespace mathLib;


vec3 color(const ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.0f, MAXFLOAT, rec))
	{
		return 0.5f * vec3(rec.normal.x() + 1.0f, rec.normal.y() + 1.0f, rec.normal.z() + 1.0f);
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
	constexpr int nx {200};
	constexpr int ny {100};
	constexpr float pixelValScale {255.99f};
	const std::string fileName("output.ppm");

	spdlog::info("Writing to file: {}...", fileName);
	std::ofstream oFile(fileName);
	oFile << "P3\n" << nx << " " << ny <<"\n255\n";

	const vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	const vec3 horizontal(4.0f, 0.0f, 0.0f);
	const vec3 vertical(0.0f, 2.0f, 0.0f);
	const vec3 origin(0.0f, 0.0f, 0.0f);

	hitable* list[2];
	{
		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);
	}
	hitable* world = new hitable_list(list, 2);

	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i <nx; ++i)
		{
			const float u {static_cast<float>(i) / static_cast<float>(nx)};
			const float v {static_cast<float>(j) / static_cast<float>(ny)};
			ray r(origin, lower_left_corner + u*horizontal + v*vertical);

			//vec3 p 			{r.point_at_parameter(2.0f)};
			vec3 col 		{color(r, world)};
			const int ir 	{static_cast<int>(pixelValScale*col.r())};
			const int ig 	{static_cast<int>(pixelValScale*col.g())};
			const int ib 	{static_cast<int>(pixelValScale*col.b())};

			oFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	oFile.close();
	spdlog::info("Closing file: {}", fileName);
	return 0;
} 