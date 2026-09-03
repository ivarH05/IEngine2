#pragma once
#include "Quaternion.h"
#include <string>

namespace IEngine
{
	struct Matrix4x4;

	struct Vector3
	{
	public:
		float x, y, z = 0;

		constexpr Vector3() : x(0), y(0), z(0) { }

		constexpr Vector3(float x, float y, float z) :
			x(x),
			y(y),
			z(z)
		{ }

		static Vector3 Zero();
		static Vector3 One();

		constexpr Vector3 operator+(const Vector3& other) const;
		constexpr Vector3 operator-(const Vector3& other) const;
		constexpr Vector3 operator*(float scalar) const;
		constexpr Vector3 operator/(float scalar) const;
		constexpr bool operator==(const Vector3& other) const;
		constexpr bool operator!=(const Vector3& other) const;

		Vector3 operator*(const Quaternion& quaternion) const;
		Vector3 operator*(const Matrix4x4& m) const;

		constexpr float Dot(const Vector3& other) const;
		constexpr Vector3 Cross(const Vector3& other) const;
		Vector3 Normalized() const;

		float Magnitude() const;
		float DistanceTo(const Vector3 other) const;

		operator std::string() const;
		std::string ToString() const;

		static Vector3 Lerp(const Vector3 a, const Vector3 b, float t);
		static Vector3 LerpUnclamped(const Vector3 a, const Vector3 b, float t);
		static Vector3 Slerp(const Vector3 a, const Vector3 b, float t);
		static Vector3 SlerpUnclamped(const Vector3 a, const Vector3 b, float t);

		static Vector3 Min(const Vector3 a, const Vector3 b);
		static Vector3 Max(const Vector3 a, const Vector3 b);

		static float Distance(const Vector3 a, const Vector3 b);
		static float Dot(const Vector3 a, const Vector3 b);
		static float Cross(const Vector3 a, const Vector3 b);
	};
}