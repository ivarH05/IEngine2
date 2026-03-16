#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include <string>

namespace IEngine
{
	struct Matrix4x4
	{
	public:
		float 	m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;

		Matrix4x4() :
			m00(0), m01(0), m02(0), m03(0),
			m10(0), m11(0), m12(0), m13(0),
			m20(0), m21(0), m22(0), m23(0),
			m30(0), m31(0), m32(0), m33(0)
		{ }

		Matrix4x4(float m11, float m12, float m13, float m14,
				  float m21, float m22, float m23, float m24,
				  float m31, float m32, float m33, float m34,
				  float m41, float m42, float m43, float m44) :
			m00(m11), m01(m12), m02(m13), m03(m14),
			m10(m21), m11(m22), m12(m23), m13(m24),
			m20(m31), m21(m32), m22(m33), m23(m34),
			m30(m41), m31(m42), m32(m43), m33(m44)
		{ }

		Matrix4x4 operator+(const Matrix4x4& other) const;
		Matrix4x4 operator-(const Matrix4x4& other) const;
		Matrix4x4 operator*(const Matrix4x4& other) const;
		Matrix4x4 operator*(float scalar) const;
		Matrix4x4 operator/(float scalar) const;

		Matrix4x4 operator-() const;

		constexpr bool operator==(const Matrix4x4& other) const;
		constexpr bool operator!=(const Matrix4x4& other) const;

		static Matrix4x4 Identity();

		Matrix4x4 Transpose() const;
		Matrix4x4 Inverse() const;

		Quaternion ToRotation() const;

		Vector4 GetRow(int index) const;
		Vector4 GetColumn(int index) const;

		Vector3 LossyScale() const;

		float Determinant() const;

		bool IsIdentity() const;

		operator std::string() const;
		std::string ToString() const;
	};
}