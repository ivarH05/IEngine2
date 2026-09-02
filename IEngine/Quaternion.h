#pragma once
#include <string>

namespace IEngine
{
	struct Vector3;

	struct Quaternion
	{
	public:
		float w, x, y, z = 0;

		Quaternion() : w(0), x(0), y(0), z(0) { }

		Quaternion(float w, float x, float y, float z) :
			w(w),
			x(x),
			y(y),
			z(z)
		{ }


		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator*(float scalar) const;
		Quaternion operator/(float scalar) const;
		Vector3 operator*(const Vector3& other) const;

		constexpr bool operator==(const Quaternion& other) const;
		constexpr bool operator!=(const Quaternion& other) const;

		Quaternion Conjugate() const;
		Quaternion Inverse() const;
		Quaternion Normalized() const;

		float Norm() const;
		float NormSquared() const;

		Vector3 EulerAngles() const;

		operator std::string() const;
		std::string ToString() const;

		static Quaternion Euler(float pitch, float yaw, float roll);
	};
}