#include "Matrix4x4.h"
#include <stdexcept>
#include <sstream>

namespace IEngine
{
	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
	{
		return Matrix4x4(
			m00 + other.m00, m01 + other.m01, m02 + other.m02, m03 + other.m03,
			m10 + other.m10, m11 + other.m11, m12 + other.m12, m13 + other.m13,
			m20 + other.m20, m21 + other.m21, m22 + other.m22, m23 + other.m23,
			m30 + other.m30, m31 + other.m31, m32 + other.m32, m33 + other.m33
		);
	}

	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
	{
		return Matrix4x4(
			m00 - other.m00, m01 - other.m01, m02 - other.m02, m03 - other.m03,
			m10 - other.m10, m11 - other.m11, m12 - other.m12, m13 - other.m13,
			m20 - other.m20, m21 - other.m21, m22 - other.m22, m23 - other.m23,
			m30 - other.m30, m31 - other.m31, m32 - other.m32, m33 - other.m33
		);
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
	{
		return Matrix4x4(
			m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
			m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
			m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
			m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,
			m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
			m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
			m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
			m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,
			m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
			m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
			m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
			m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,
			m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
			m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
			m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
			m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33
		);
	}

	Matrix4x4 Matrix4x4::operator*(float scalar) const
	{
		return Matrix4x4(
			m00 * scalar, m01 * scalar, m02 * scalar, m03 * scalar,
			m10 * scalar, m11 * scalar, m12 * scalar, m13 * scalar,
			m20 * scalar, m21 * scalar, m22 * scalar, m23 * scalar,
			m30 * scalar, m31 * scalar, m32 * scalar, m33 * scalar
		);
	}

	Matrix4x4 Matrix4x4::operator/(float scalar) const
	{
		return Matrix4x4(
			m00 / scalar, m01 / scalar, m02 / scalar, m03 / scalar,
			m10 / scalar, m11 / scalar, m12 / scalar, m13 / scalar,
			m20 / scalar, m21 / scalar, m22 / scalar, m23 / scalar,
			m30 / scalar, m31 / scalar, m32 / scalar, m33 / scalar
		);
	}

	Matrix4x4 Matrix4x4::operator-() const
	{
		return Matrix4x4(
			-m00, -m01, -m02, -m03,
			-m10, -m11, -m12, -m13,
			-m20, -m21, -m22, -m23,
			-m30, -m31, -m32, -m33
		);
	}

	Vector3 Matrix4x4::operator*(const Vector3& other) const
	{
		return Vector3(
			m00 * other.x + m01 * other.y + m02 * other.z + m03,
			m10 * other.x + m11 * other.y + m12 * other.z + m13,
			m20 * other.x + m21 * other.y + m22 * other.z + m23
		);
	}

	constexpr bool Matrix4x4::operator==(const Matrix4x4& other) const
	{
		return 
			m00 == other.m00 && m01 == other.m01 && m02 == other.m02 && m03 == other.m03 &&
			m10 == other.m10 && m11 == other.m11 && m12 == other.m12 && m13 == other.m13 &&
			m20 == other.m20 && m21 == other.m21 && m22 == other.m22 && m23 == other.m23 &&
			m30 == other.m30 && m31 == other.m31 && m32 == other.m32 && m33 == other.m33;
	}

	constexpr bool Matrix4x4::operator!=(const Matrix4x4& other) const
	{
		return !(*this == other);
	}

	Matrix4x4 Matrix4x4::Transpose() const
	{
		return Matrix4x4(
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33
		);;
	}

	Matrix4x4 Matrix4x4::Identity()
	{
		return Matrix4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}
	Matrix4x4 Matrix4x4::TRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
	{
		Matrix4x4 translationMatrix(
			1, 0, 0, translation.x,
			0, 1, 0, translation.y,
			0, 0, 1, translation.z,
			0, 0, 0, 1
		);
		Matrix4x4 rotationMatrix = rotation.ToMatrix();
		Matrix4x4 scaleMatrix(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1
		);
		return translationMatrix * rotationMatrix * scaleMatrix;
	}


	Vector4 Matrix4x4::GetRow(int index) const
	{
		switch (index)
		{
		case 0: return Vector4(m00, m01, m02, m03);
		case 1: return Vector4(m10, m11, m12, m13);
		case 2: return Vector4(m20, m21, m22, m23);
		case 3: return Vector4(m30, m31, m32, m33);
		default: throw std::out_of_range("Row index must be between 0 and 3.");
		}
	}

	Vector4 Matrix4x4::GetColumn(int index) const
	{
		switch (index)
		{
		case 0: return Vector4(m00, m10, m20, m30);
		case 1: return Vector4(m01, m11, m21, m31);
		case 2: return Vector4(m02, m12, m22, m32);
		case 3: return Vector4(m03, m13, m23, m33);
		default: throw std::out_of_range("Column index must be between 0 and 3.");
		}
	}

	bool Matrix4x4::IsIdentity() const
	{
		return m00 == 1 && m01 == 0 && m02 == 0 && m03 == 0 &&
			   m10 == 0 && m11 == 1 && m12 == 0 && m13 == 0 &&
			   m20 == 0 && m21 == 0 && m22 == 1 && m23 == 0 &&
			   m30 == 0 && m31 == 0 && m32 == 0 && m33 == 1;
	}


	Matrix4x4::operator std::string() const
	{
		return ToString();
	}

	std::string Matrix4x4::ToString() const
	{
		std::ostringstream ss;

		ss	<< "[" << m00 << "," << m01 << "," << m02 << "," << m03 << "\n"
			<< " " << m10 << "," << m11 << "," << m12 << "," << m13 << "\n"
			<< " " << m20 << "," << m21 << "," << m22 << "," << m23 << "\n"
			<< " " << m30 << "," << m31 << "," << m32 << "," << m33 << "]";

		return ss.str();
	}
}