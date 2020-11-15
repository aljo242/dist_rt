#ifndef DEFS_H
#define DEFS_H


#define GLM_FORCE_CXX17
#include <glm/vec2.hpp>           // vec2
#include <glm/vec3.hpp>           // vec3
#include <glm/mat3x3.hpp>         // mat3
#include <glm/mat4x4.hpp>         // mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/scalar_multiplication.hpp>
#include <glm/gtc/quaternion.hpp>

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

inline float LengthSquared(const glm::vec2& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

inline float LengthSquared(const glm::vec3& vec)
{
	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

inline float Distance(const glm::vec2& v1, const glm::vec2& v2)
{
	return Length(v1 - v2);
}

inline float Distance(const glm::vec3& v1, const glm::vec3& v2)
{
	return Length(v1 - v2);
}

inline float DistanceSquared(const glm::vec2& v1, const glm::vec2& v2)
{
	return LengthSquared(v1 - v2);
}

inline float DistanceSquared(const glm::vec3& v1, const glm::vec3& v2)
{
	return LengthSquared(v1 - v2);
}

// typedefs
using Vec2 = glm::vec2;
using Point2 = glm::vec2;

using Vec3 = glm::vec3;
using Point3 = glm::vec3;
using Color3 = glm::vec3;

using Mat3 = glm::mat3x3;
using Mat4= glm::mat4x4;

using Quaternion = glm::quat;

struct ViewPort
{
	Point3 origin;
	Vec3 horizontal;
	Vec3 vertical;
	Point3 lowerLeftCorner;
};


struct ConfigInfo
{
	uint32_t imagebufferSize;
	uint32_t imagebufferWidth;
	uint32_t imagebufferHeight;
	uint32_t imageNumChannels = 3;
	uint32_t samplesPerPixel;
	uint32_t numTiles;
	const char* inputFilename;
	const char* outputFilename;
};


constexpr uint32_t imageWidth{ 2560 };
constexpr uint32_t imageHeight{ static_cast<int>(imageWidth / aspectRatio) };
constexpr uint32_t numChannels{ 3 };
constexpr uint32_t imageSize{ imageHeight * imageWidth };

constexpr size_t defaultNumObjects = 1000;

// Distributed variables
constexpr int MASTER = 0;


// fwd declarations
class Camera;
class Medium;
struct MediumInterface;
class VMesh;
class Ray3;
class Bounds3;
class RayDifferential3;
struct Interaction;
class MediumInteraction;
class SurfaceInteraction;
class Shape;
class Material;
struct CartCoord;
class Sampler;
class Texture;
class Spectrum;
class PhaseFunction;
struct Shading;
struct Primitive;

#endif