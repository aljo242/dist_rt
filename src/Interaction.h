#ifndef INTERACTION_H
#define INTERACTION_H

#include "defs.h"

struct Shading
{
	Vec3 norm;
	Vec3 dPdU;	// derivative point w.r.t. U 
	Vec3 dPdV;  // derivative point w.r.t. V 
	Vec3 dNdU;  // derivative normal w.r.t. U 
	Vec3 dNdV;  // derivative normal w.r.t. V  
};

struct Interaction
{
	Interaction() : time(0.0f) {}


	Point3 p = Vec3(0, 0, 0);
	float time = 0.0f;
	Vec3 pError = Vec3(0, 0, 0); // estimated error of where point3 p is
	Vec3 norm = Vec3(0, 0, 0);
	Vec3 outgoingDir = Vec3(0, 0, 0);
};


class SurfaceInteraction : public Interaction
{
public:
	Point2 uv; // virtual 2d surface coordinates
	Vec3 dPdU;	// derivative point w.r.t. U 
	Vec3 dPdV;  // derivative point w.r.t. V 
	Vec3 dNdU;  // derivative normal w.r.t. U 
	Vec3 dNdV;  // derivative normal w.r.t. V  
	Shading shading;
	const Shape* shape {nullptr};
	const Primitive* primitive {nullptr};
	Vec3 dPdX;
	Vec3 dPdY;


};

#endif // INTERACTION_H