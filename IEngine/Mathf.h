#pragma once

namespace IEngine
{
	class Mathf
	{
	public:
		static float Sqrt(float value);
		static float Abs(float value);
		static float Pow(float base, float exponent);


		static float Sin(float angle);
		static float Cos(float angle);
		static float Tan(float angle);

		static float Asin(float f);
		static float Acos(float f);
		static float Atan(float f);

		static float Atan2(float y, float x);

		static float Clamp01(float value);
		static float Clamp(float value, float min, float max);

		static float Min(float a, float b);
		static float Max(float a, float b);

		static float CopySign(float magnitude, float sign);

		static const float Deg2Rad;
		static const float Rad2Deg;

		static const float PI;
	};
}