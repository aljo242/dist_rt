#ifndef CAMERA_H
#define CAMERA_H

#include "defs.h"
#include "utils.h"
#include "Ray.h"


class Camera
{
public:
	Camera();
	Camera(const ViewPort& viewport);
	Ray3 getRay(const float u, const float v) const;

private:
	ViewPort vp;
};

#endif