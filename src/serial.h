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
	int bufferSize = config.imagebufferSize * config.imageNumChannels;
	const int imagebufferWidth = config.imagebufferWidth;
	const int imagebufferHeight = config.imagebufferHeight;
	int imagebufferSize = config.imagebufferSize;

	int worldSize = 4;
	int worldRank = 0;

	TileInfo tileInfo;
	fillTileInfo(worldSize, config, tileInfo);
	spdlog::critical("Tile size: {}\nTile width: {}\nTile height {}",
		tileInfo.tileSize, tileInfo.tileWidth, tileInfo.tileHeight);

	bufferSize = imagebufferSize * config.imageNumChannels;

	ViewPort vp;
	vp.origin = Point3(0, 0, 0);
	vp.horizontal = Vec3(viewportWidth, 0, 0);
	vp.vertical = Vec3(0, viewportHeight, 0);
	vp.lowerLeftCorner = vp.origin - vp.horizontal / 2 - vp.vertical / 2 - Vec3(0, 0, 1.0);
	Camera cam(vp);

	Sphere testSphere(Point3(0.0, 0.0, -1.0), 0.5f);

	std::vector<uint8_t> image(bufferSize);
	size_t index = 0;

	for (int j = 0; j < imagebufferHeight; ++j)
	{
		for (int i = 0; i < imagebufferWidth; ++i)
		{
			const auto u = static_cast<float>(i) / (imagebufferWidth - 1);
			const auto v = static_cast<float>(j) / (imagebufferHeight - 1);

			Color3 pixelColor;
			Ray3 r = cam.getRay(u, v);

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

	writePNG(config.outputFilename, imagebufferWidth, imagebufferHeight, config.imageNumChannels, image);
}


#endif // SERIAL_H