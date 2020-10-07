#ifndef DEFS_H
#define DEFS_H


#define GLM_FORCE_CXX17
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/scalar_multiplication.hpp>

#include <cstdint>
#include <limits>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385;

inline float Length(const glm::vec3& vec) 
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// typedefs
using Vec3 = glm::vec3;
using Point3 = glm::vec3;
using Color3 = glm::vec3;

#endif