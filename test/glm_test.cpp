#include "../src/defs.h"
#include <spdlog/spdlog.h>
#include <iostream>

int main()
{
	Quaternion a_quat(1, 1, 1, 1);
	Quaternion b_quat(0, 1, 0, 1);

	const auto c_quat_dot = glm::dot(a_quat, b_quat);
	const auto c_quat_norm = glm::normalize(a_quat);

	Mat4 a_mat(1);
	Mat4 b_mat(2);

	const auto c_mat = a_mat * b_mat;
	const auto c_mat_scaled = glm::scale(c_mat, Vec3(c_quat_dot));

	Vec3 a_vec(1, 0, 0);
	Vec3 b_vec(0, 0, 1);

	const auto c_vec_dot = glm::dot(a_vec, b_vec);
	const auto c_vec_cross = glm::dot(a_vec, b_vec);

	return 0;
}