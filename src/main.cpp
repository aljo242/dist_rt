#include <fstream>
#include <iostream>
#include <optional>
#include <array>
#include <vector>
#include <spdlog/spdlog.h>
#include "defs.h"

#include <omp.h>

#ifdef WITH_MPI
#include "parallel.h"
#else
#include "serial.h"
#endif

#include "Ray.h"
#include "Plane.h"
#include "Image.h"
#include "Scene_Object.h"
#include "Sphere.h"
#include "Camera.h"
#include "Timer.h"



class ObjectList
{
public:
	ObjectList()
		: objects(defaultNumObjects)
	{}

	ObjectList(size_t numObjects)
		: objects(numObjects)
	{}

	void AddElement(Scene_Object* so) 
	{
		if (push)
		{
			objects.push_back(so);
			return;
		}
	
		objects[elementsPushed] = so;
		elementsPushed++;

		if ((elementsPushed >= defaultNumObjects) && push == false)
		{
			push = true;
		}
	}

private:
	std::vector<Scene_Object*> objects;
	size_t elementsPushed = 0;
	bool push = false;
};

std::optional<Color3> IntersectPlane(const Ray3& ray, const Plane& plane)
{
	const auto planeNormal = plane.NormVec();
	const float denom{ glm::dot(planeNormal, ray.dir) };
	if (std::fabs(denom) > epsilon)
	{
		const float t = glm::dot((plane.NormPoint() - ray.origin), planeNormal) / denom;
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
	spdlog::critical("test ray norm: {} {} {}", testRay.dir.x, testRay.dir.y, testRay.dir.z);

	Plane testPlane(Point3(5, 5, 5), Vec3(5, 0, 1), Vec3(0, 1, 0) );
	
	auto ret = IntersectPlane(testRay, testPlane);

	if (ret.has_value())
	{
		spdlog::critical("nullopt evaluate to true");
	}

	ConfigInfo config;
	config.imagebufferSize = imageSize;
	config.imagebufferWidth = imageWidth;
	config.imagebufferHeight = imageHeight;
	config.outputFilename = "test_output.png";
	config.samplesPerPixel = 50;
	
	Timer timer;

	timer.Start();
	Render(config);
	const auto rendertime = timer.Stop();
	spdlog::critical("Elapsed Time: {}s", rendertime / 1000.0);

	return 0;
}

