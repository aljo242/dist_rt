#include "Camera.h"

Camera::Camera()
{
	vp.origin = Point3(0,0,0);
	vp.horizontal = Vec3(viewportWidth, 0, 0);
	vp.vertical = Vec3(0, viewportHeight, 0);
	vp.lowerLeftCorner = vp.origin - vp.horizontal / 2.0f + vp.vertical / 2.0f - Vec3(0, 0, focalLength);
}

Camera::Camera(const ViewPort& viewport)
	: vp(viewport)
{}
	

Ray3 Camera::getRay(const float u, const float v) const
{
	return Ray3(vp.origin, vp.lowerLeftCorner + u * vp.horizontal + v * vp.vertical - vp.origin);
}
