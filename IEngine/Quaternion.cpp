#include "Quaternion.h"
#include "Vector3.h"
#include "Mathf.h"

namespace IEngine
{

	Quaternion Quaternion::operator+(const Quaternion& other) const
	{
		return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const
	{
		return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		return Quaternion(
			w * other.w - x * other.x - y * other.y - z * other.z,
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w
		);
	}

	Quaternion Quaternion::operator*(float scalar) const
	{
		return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
	}

	Quaternion Quaternion::operator/(float scalar) const
	{
		return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
	}

	Vector3 Quaternion::operator*(const Vector3& other) const
	{
		return other * (*this);
	}

	constexpr bool Quaternion::operator==(const Quaternion& other) const
	{
		return w == other.w && x == other.x && y == other.y && z == other.z;
	}

	constexpr bool Quaternion::operator!=(const Quaternion& other) const
	{
		return !(*this == other);
	}


	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Inverse() const
	{
		return Conjugate() / NormSquared();
	}

	Quaternion Quaternion::Normalized() const
	{
		return *this / Norm();
	}

	float Quaternion::Norm() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z + w * w);
	}

	float Quaternion::NormSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Vector3 Quaternion::EulerAngles() const
	{
		float sinr_cosp = 2 * (w * x + y * z);
		float cosr_cosp = 1 - 2 * (x * x + y * y);
		float roll = Mathf::Atan2(sinr_cosp, cosr_cosp);
		float sinp = 2 * (w * y - z * x);
		float pitch;
		if (Mathf::Abs(sinp) >= 1)
			pitch = Mathf::CopySign(Mathf::PI / 2, sinp);
		else
			pitch = Mathf::Asin(sinp);
		float siny_cosp = 2 * (w * z + x * y);
		float cosy_cosp = 1 - 2 * (y * y + z * z);
		float yaw = Mathf::Atan2(siny_cosp, cosy_cosp);
		return Vector3(pitch, yaw, roll) * Mathf::Rad2Deg;
	}

	Quaternion Quaternion::Euler(float pitch, float yaw, float roll)
	{
		float pitchRads = pitch * Mathf::Deg2Rad;
		float yawRads = yaw * Mathf::Deg2Rad;
		float rollRads = roll * Mathf::Deg2Rad;

		float cy = Mathf::Cos(yawRads * 0.5f);
		float sy = Mathf::Sin(yawRads * 0.5f);
		float cp = Mathf::Cos(pitchRads * 0.5f);
		float sp = Mathf::Sin(pitchRads * 0.5f);
		float cr = Mathf::Cos(rollRads * 0.5f);
		float sr = Mathf::Sin(rollRads * 0.5f);
		return Quaternion(
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		);
	}

	Quaternion::operator std::string() const
	{
		return ToString();
	}

	std::string Quaternion::ToString() const
	{
		return "(" + std::to_string(w) + ", " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

}