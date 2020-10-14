#ifndef PARALLEL_H
#define PARALLEL_H

#ifdef WITH_MPI

#include "defs.h"
#include "Ray.h"
#include "Plane.h"
#include "Image.h"
#include "Scene_Object.h"
#include "Sphere.h"
#include "Camera.h"
#include "Tiling.h"

#include <mpi.h>


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
	MPI_Init(NULL, NULL);
	int worldRank;
	int worldSize;
	

	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
	const auto u_worldRank = static_cast<uint32_t>(worldRank);
	const auto u_worldSize = static_cast<uint32_t>(worldSize);

	auto bufferSize = static_cast<size_t>(config.imagebufferSize * config.imageNumChannels);
	const auto imagebufferWidth = config.imagebufferWidth;
	const auto imagebufferHeight = config.imagebufferHeight;
	const auto imagebufferSize = config.imagebufferSize;

	TileInfo tileInfo;
	fillTileInfo(u_worldSize, config, tileInfo);
	TileGrid grid(tileInfo);

	bufferSize = static_cast<size_t>(imagebufferSize * config.imageNumChannels);

	ViewPort vp;
	vp.origin = Point3(0, 0, 0);
	vp.horizontal = Vec3(viewportWidth, 0, 0);
	vp.vertical = Vec3(0, viewportHeight, 0);
	vp.lowerLeftCorner = vp.origin - vp.horizontal / 2 - vp.vertical / 2 - Vec3(0, 0, 1.0);
	Camera cam(vp);

	Sphere testSphere(Point3(0.0, 0.0, -1.0), 0.5f);

	std::vector<uint8_t> image;

	if (worldRank == MASTER)
	{
		image.reserve(bufferSize);
	}
	else
	{
		image.reserve(tileInfo.tileSize * config.imageNumChannels);
	}

	const auto gridIndices = grid.indices[u_worldRank];
	const auto startIndex_X = gridIndices.first;
	const auto stopIndex_X = startIndex_X + tileInfo.tileWidth;
	const auto startIndex_Y = gridIndices.second;
	const auto stopIndex_Y = startIndex_Y + tileInfo.tileHeight;
	spdlog::critical("X: ({}, {}), Y: ({}, {})", startIndex_X, stopIndex_X, startIndex_Y, stopIndex_Y);

	size_t index = 0;
	for (uint32_t j = startIndex_Y; j < stopIndex_Y; ++j)
	{
		for (uint32_t i = startIndex_X; i < stopIndex_X; ++i)
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

			//spdlog::critical("{}", index);
			if (worldRank == MASTER)
			{
				index = static_cast<size_t>(i * config.imageNumChannels + j * imagebufferWidth * config.imageNumChannels);
				image[index] = ir;
				image[index + 1] = ig;
				image[index + 2] = ib;
			}
			else
			{
				image[index++] = ir;
				image[index++] = ig;
				image[index++] = ib;
			}
		}
	}
	
	if (worldRank != MASTER)
	{
		//MPI_Send();
	}
	else
	{
		for (int i = 1; i < worldSize; ++i)
		{
			//MPI_Recv();
			spdlog::critical("MASTER node recieving from node {}", i);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

	writePNG(config.outputFilename, imagebufferWidth, imagebufferHeight, config.imageNumChannels, image);
}


#endif // WITH_MPI


#endif