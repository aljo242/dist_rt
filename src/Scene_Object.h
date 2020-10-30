#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

class Ray3; // fwd declaration

class Scene_Object
{
public:
	Scene_Object() = default;
	virtual ~Scene_Object() = default;

	virtual bool Intersect(const Ray3& r, const float tmin, const float tmax) const = 0;
};

#endif //SCENE_OBJECT_H