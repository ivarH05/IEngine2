#include "Mathf.h"
#include <cmath>


namespace IEngine
{
	const float Mathf::Deg2Rad = 0.01745329251994329576923690768489f;
	const float Mathf::Rad2Deg = 57.295779513082320876798154814105f;
	const float Mathf::PI = 3.1415926535897932384626433832795f;

	float Mathf::Sqrt(float value)
	{
		return std::sqrt(value);
	}

	float Mathf::Abs(float value)
	{
		return std::abs(value);
	}

	float Mathf::Pow(float base, float exponent)
	{
		return std::pow(base, exponent);
	}


	float Mathf::Sin(float angle)
	{
		return std::sin(angle);
	}

	float Mathf::Cos(float angle)
	{
		return std::cos(angle);
	}

	float Mathf::Tan(float angle)
	{
		return std::tan(angle);
	}


	float Mathf::Asin(float f)
	{
		return std::asin(f);
	}

	float Mathf::Acos(float f)
	{
		return std::acos(f);
	}

	float Mathf::Atan(float f)
	{
		return std::atan(f);
	}


	float Mathf::Atan2(float y, float x)
	{
		return std::atan2(y, x);
	}

	float Mathf::CopySign(float magnitude, float sign)
	{
		return std::copysign(magnitude, sign);
	}


	float Mathf::Clamp01(float value)
	{
		return value < 0 ? 0 : value > 1 ? 1 : value;
	}
	float Mathf::Clamp(float value, float min, float max)
	{
		return value < min ? min : value > max ? max : value;
	}

	float Mathf::Min(float a, float b)
	{
		return a < b ? a : b;
	}
	float Mathf::Max(float a, float b)
	{
		return a > b ? a : b;
	}
}