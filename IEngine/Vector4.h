#pragma once

namespace IEngine
{
	struct Vector4
	{
	public:
		float x, y, z, w = 0;

		Vector4() :
			x(0), y(0), z(0), w(0)
		{
		}
		Vector4(float x, float y, float z, float w) :
			x(x), y(y), z(z), w(w)
		{
		}
		static Vector4 Zero();
		static Vector4 One();

		Vector4 operator+(const Vector4& other) const;
		Vector4 operator-(const Vector4& other) const;
		Vector4 operator*(float scalar) const;
		Vector4 operator/(float scalar) const;

		constexpr bool operator==(const Vector4& other) const;
		constexpr bool operator!=(const Vector4& other) const;

		constexpr float Dot(const Vector4& other) const;

		float Magnitude() const;
		float DistanceTo(const Vector4 other) const;


		static Vector4 Lerp(const Vector4 a, const Vector4 b, float t);
		static Vector4 LerpUnclamped(const Vector4 a, const Vector4 b, float t);

		static Vector4 Min(const Vector4 a, const Vector4 b);
		static Vector4 Max(const Vector4 a, const Vector4 b);

		static float Distance(const Vector4 a, const Vector4 b);
	};
}