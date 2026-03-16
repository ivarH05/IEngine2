#include "Vector3.h";
#include "Mathf.h"

namespace IEngine
{
	Vector3 Vector3::One()
	{
		return Vector3(1, 1, 1);
	}

	Vector3 Vector3::Zero()
	{
		return Vector3(0, 0, 0);
	}

	constexpr Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	constexpr Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	constexpr Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	constexpr Vector3 Vector3::operator/(float scalar) const
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	constexpr bool Vector3::operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	constexpr bool Vector3::operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}


	Vector3 Vector3::operator*(Quaternion quaternion) const
	{
		const Quaternion v(x, y, z, 0.0f);
		const Quaternion result = quaternion * v * quaternion.Conjugate();

		return Vector3{ result.x, result.y, result.z };
	}



	constexpr float Vector3::Dot(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	constexpr Vector3 Vector3::Cross(const Vector3& other) const
	{
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	Vector3 Vector3::Normalized() const
	{
		float mag = Magnitude();
		if (mag == 0.0f)
			return Vector3::Zero(); // can't normalize a zero vector
		return *this / mag;
	}

	float Vector3::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z);
	}

	float Vector3::DistanceTo(const Vector3 other) const
	{
		return (other - *this).Magnitude();
	}

	Vector3::operator std::string() const
	{
		return ToString();
	}

	std::string Vector3::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	Vector3 Vector3::Lerp(const Vector3 a, const Vector3 b, float t)
	{
		t = Mathf::Clamp01(t);
		return LerpUnclamped(a, b, t);
	}

	Vector3 Vector3::LerpUnclamped(const Vector3 a, const Vector3 b, float t)
	{
		return a + (b - a) * t;
	}

	Vector3 Vector3::Slerp(const Vector3 a, const Vector3 b, float t)
	{
		t = Mathf::Clamp01(t);
		return SlerpUnclamped(a, b, t);
	}

	Vector3 Vector3::SlerpUnclamped(const Vector3 a, const Vector3 b, float t)
	{
		float magA = a.Magnitude();
		float magB = b.Magnitude();

		if (magA == 0.0f || magB == 0.0f)
			return Vector3::LerpUnclamped(a, b, t);

		Vector3 na = a / magA;
		Vector3 nb = b / magB;

		float dot = Vector3::Dot(na, nb);

		dot = Mathf::Max(-1.0f, Mathf::Min(1.0f, dot));

		float theta = Mathf::Acos(dot) * t;
		Vector3 relative = (nb - na * dot).Normalized();

		Vector3 resultDir = na * Mathf::Cos(theta) + relative * Mathf::Sin(theta);
		float mag = magA + (magB - magA) * t;

		return resultDir * mag;
	}

	Vector3 Vector3::Min(const Vector3 a, const Vector3 b)
	{
		return Vector3(
			Mathf::Min(a.x, b.x),
			Mathf::Min(a.y, b.y),
			Mathf::Min(a.z, b.z)
		);
	}

	Vector3 Vector3::Max(const Vector3 a, const Vector3 b)
	{
		return Vector3(
			Mathf::Max(a.x, b.x),
			Mathf::Max(a.y, b.y),
			Mathf::Max(a.z, b.z)
		);
	}

	float Vector3::Distance(const Vector3 a, const Vector3 b)
	{
		return (a - b).Magnitude();
	}

	float Vector3::Dot(const Vector3 a, const Vector3 b)
	{
		return a.Dot(b);
	}

	float Vector3::Cross(const Vector3 a, const Vector3 b)
	{
		return a.Cross(b).Magnitude();
	}
}