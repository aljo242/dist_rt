#ifndef SERIAL_H
#define SERIAL_H

#include "defs.h"
#include "Ray.h"
#include "Plane.h"
#include "Image.h"
#include "Scene_Object.h"
#include "Sphere.h"
#include "Camera.h"
#include "Tiling.h"
#include "VMesh.h"

#include <spdlog/spdlog.h>

Color3 RayColor(const Ray3& ray, const Sphere& s)
{
	Vec3 dir = ray.Dir(); // ray returns normalized vectors
	const auto t = 0.5f * (dir.y + 1.0f);

	if (s.Intersect(ray, 0, infinity))
	{
		const auto N = ray.At(t) - Vec3(0, 0, -1);
		return 0.5f * Color3(N.x + 1, N.y + 1, N.z + 1);
	}

	return { (1.0f - t) * Color3(1.0f, 1.0f, 1.0f) + t * Color3(0.5f, 0.7f, 1.0f) };
}


void Render(const ConfigInfo& config)
{
	auto bufferSize = static_cast<size_t>(config.imagebufferSize * config.imageNumChannels);
	const auto imagebufferWidth = config.imagebufferWidth;
	const auto imagebufferHeight = config.imagebufferHeight;
	auto imagebufferSize = config.imagebufferSize;

	uint32_t numPEs = 4;

	//TileInfo tileInfo;
	//fillTileInfo(numTiles, config, tileInfo);
	//TileGrid grid(tileInfo);


	bufferSize = static_cast<size_t>(imagebufferSize * config.imageNumChannels);


	ViewPort vp;
	vp.origin = Point3(0, 0, 0);
	vp.horizontal = Vec3(viewportWidth, 0, 0);
	vp.vertical = Vec3(0, viewportHeight, 0);
	vp.lowerLeftCorner = vp.origin - vp.horizontal / 2 - vp.vertical / 2 - Vec3(0, 0, 1.0);
	Camera cam(vp);

	Sphere testSphere(Point3(0.0, 0.0, -1.0), 0.5f);

	std::vector<uint8_t> image(bufferSize);

	for (uint32_t n = 0; n < numPEs; ++n)
	{
		VMesh myMesh(numPEs, n, imagebufferSize, imagebufferWidth, imagebufferHeight);
		VMeshDims startIndices{ 0, 0 };
		VMeshDims endIndices{ 0, 0 };

		const auto addr = myMesh.virtualAddress;
		const auto block = myMesh.localDims;
		//const auto data = myMesh.dataDims;

		startIndices = { addr.x * block.x, addr.y * block.y };
		endIndices = { (addr.x + 1) * block.x, (addr.y + 1) * block.y };

		spdlog::critical("X: ({}, {}), Y: ({}, {})", startIndices.x, endIndices.x, startIndices.y, endIndices.y);

		for (uint32_t j = startIndices.y; j < endIndices.y; ++j)
		{
			for (uint32_t i = startIndices.x; i < endIndices.x; ++i)
			{
				Color3 pixelColor = Color3(0, 0, 0);

				for (uint32_t s = 0; s < config.samplesPerPixel; ++s)
				{
					const auto u = (static_cast<float>(i) + randFloat()) / (static_cast<float>(imagebufferWidth - 1));
					const auto v = (static_cast<float>(j) + randFloat()) / (static_cast<float>(imagebufferHeight - 1));

					Ray3 r = cam.getRay(u, v);
					pixelColor += RayColor(r, testSphere);
				}

				// scale by num samples
				const auto scale = 1.0f / static_cast<float>(config.samplesPerPixel);
				const auto r = pixelColor.r * scale;
				const auto g = pixelColor.g * scale;
				const auto b = pixelColor.b * scale;

				const auto ir = static_cast<uint8_t>(255.99f * r);
				const auto ig = static_cast<uint8_t>(255.99f * g);
				const auto ib = static_cast<uint8_t>(255.99f * b);

				const auto index = static_cast<size_t>(i * config.imageNumChannels + j * imagebufferWidth * config.imageNumChannels);
				//spdlog::critical("{}", index);

				image[index] = ir;
				image[index + 1] = ig;
				image[index + 2] = ib;
			}
		}
	}
	writePNG(config.outputFilename, imagebufferWidth, imagebufferHeight, config.imageNumChannels, image);
}


#endif // SERIAL_H