#ifndef DEFS_H
#define DEFS_H


#define GLM_FORCE_CXX17
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/scalar_multiplication.hpp>

#include <cstdint>
#include <limits>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

constexpr float epsilon{ 0.000001f };
constexpr auto aspectRatio{ 16.0f / 9.0f };
constexpr auto viewportHeight{ 2.0f };
constexpr auto viewportWidth{ viewportHeight * aspectRatio };
constexpr auto focalLength{ 1.0f };

inline float Length(const glm::vec2& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

inline float Length(const glm::vec3& vec) 
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// typedefs
using Vec2 = glm::vec2;
using Point2 = glm::vec2;

using Vec3 = glm::vec3;
using Point3 = glm::vec3;
using Color3 = glm::vec3;

struct ViewPort
{
	Point3 origin;
	Vec3 horizontal;
	Vec3 vertical;
	Point3 lowerLeftCorner;
};


#endif