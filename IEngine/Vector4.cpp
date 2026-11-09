#include "Vector4.h"
#include "Mathf.h"

namespace IEngine
{
	Vector4 Vector4::One()
	{
		return Vector4(1, 1, 1, 1);
	}
	Vector4 Vector4::Zero()
	{
		return Vector4(0, 0, 0, 0);
	}

	Vector4 Vector4::operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vector4 Vector4::operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}	

	Vector4 Vector4::operator/(float scalar) const
	{
		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}
	constexpr bool Vector4::operator==(const Vector4& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	constexpr bool Vector4::operator!=(const Vector4& other) const
	{
		return !(*this == other);
	}

	constexpr float Vector4::Dot(const Vector4& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	float Vector4::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z + w * w);
	}

	float Vector4::DistanceTo(const Vector4 other) const
	{
		return (other - *this).Magnitude();
	}

	Vector4 Vector4::Lerp(const Vector4 a, const Vector4 b, float t)
	{
		t = Mathf::Clamp01(t);
		return LerpUnclamped(a, b, t);
	}

	Vector4 Vector4::LerpUnclamped(const Vector4 a, const Vector4 b, float t)
	{
		return a + (b - a) * t;
	}

	Vector4 Vector4::Min(Vector4 a, Vector4 b)
	{
		return Vector4(
			Mathf::Min(a.x, b.x),
			Mathf::Min(a.y, b.y),
			Mathf::Min(a.z, b.z),
			Mathf::Min(a.w, b.w)
		);
	}

	Vector4 Vector4::Max(Vector4 a, Vector4 b)
	{
		return Vector4(
			Mathf::Max(a.x, b.x),
			Mathf::Max(a.y, b.y),
			Mathf::Max(a.z, b.z),
			Mathf::Max(a.w, b.w)
		);
	}


	float Vector4::Distance(const Vector4 a, const Vector4 b)
	{
		return (b - a).Magnitude();
	}
}