#include "Transform.h"
#include "Mathf.h"

namespace IEngine
{
	void Transform::AddChild(const Pointer<Transform> child)
	{
		if (child == nullptr)
			return;
		if (std::find(_children.begin(), _children.end(), child) != _children.end())
			return;
		_children.push_back(child);
	}

	void Transform::AddChild(const Transform& child)
	{
		AddChild(Pointer<Transform>(&child));
	}

	void Transform::RemoveChild(const Pointer<Transform> child)
	{
		if (child == nullptr)
			return;
		auto it = std::find(_children.begin(), _children.end(), child);
		if (it != _children.end())
			_children.erase(it);
	}

	void Transform::RemoveChild(const Transform& child)
	{
		RemoveChild(Pointer<Transform>(&child));
	}

	Pointer<Transform> Transform::GetParent() const
	{
		return Pointer<Transform>(_parent);
	}

	Pointer<Transform> Transform::GetChildAt(int index)
	{
		if (index < 0 || index >= _children.size())
			return nullptr;
		return Pointer<Transform>(_children[index]);
	}

	int Transform::ChildCount() const
	{
		return static_cast<int>(_children.size());
	}

	void Transform::SetParent(const Pointer<Transform> value)
	{
		if (_parent == value)
			return;
		if (_parent != nullptr)
			_parent->RemoveChild(*this);
		if (value != nullptr)
			value->AddChild(*this);

		MarkDirty(true, true, true, true);
	}

	Vector3 Transform::TransformPoint(const Vector3& point)
	{
		Vector3 position = GetPosition();
		Quaternion rotation = GetRotation();
		Vector3 lossyScale = GetLossyScale();

		Vector3 scaledPoint = Vector3(point.x * lossyScale.x, point.y * lossyScale.y, point.z * lossyScale.z);
		Vector3 rotatedPoint = scaledPoint * rotation;
		return position + rotatedPoint;
	}

	Vector3 Transform::InverseTransformPoint(const Vector3& point)
	{
		Vector3 position = GetPosition();
		Quaternion rotation = GetRotation();
		Vector3 lossyScale = GetLossyScale();

		Vector3 translatedPoint = point - position;
		Vector3 rotatedPoint = translatedPoint * rotation.Inverse();
		return Vector3(rotatedPoint.x / lossyScale.x, rotatedPoint.y / lossyScale.y, rotatedPoint.z / lossyScale.z);
	}

	Vector3 Transform::GetPosition()
	{
		if (!_positionDirty)
			return _position;

		if (_parent == nullptr)
			_position = _localPosition;
		else
			_position = _parent->TransformPoint(_localPosition);

		_positionDirty = false;
		return _position;
	}

	void Transform::SetPosition(const Vector3& value)
	{
		MarkDirty(true, false, true);
		_localPositionDirty = true;
		_positionDirty = false;

		_localMatrixDirty = true;

		_position = value;
	}

	Vector3 Transform::GetLocalPosition()
	{
		if (!_localPositionDirty)
			return _localPosition;

		if (_parent == nullptr)
			_localPosition = _position;
		else
			_localPosition = _parent->InverseTransformPoint(_position);

		_localPositionDirty = false;
		return _localPosition;
	}

	void Transform::SetLocalPosition(const Vector3& value)
	{
		MarkDirty(true, false, true);
		_positionDirty = true;
		_localPositionDirty = false;

		_localMatrixDirty = true;

		_localPosition = value;
	}

	Quaternion Transform::GetRotation()
	{
		if(!_rotationDirty)
			return _rotation;

		if (_parent == nullptr)
			_rotation = _localRotation;
		else
			_rotation = _parent->GetRotation() * _localRotation;

		_rotationDirty = false;
		return _rotation;
	}

	void Transform::SetRotation(const Quaternion& value)
	{
		MarkDirty(true, true, true);
		_localRotationDirty = true;
		_rotationDirty = false;

		_localMatrixDirty = true;

		_rotation = value;
	}

	Quaternion Transform::GetLocalRotation()
	{
		if (!_localRotationDirty)
			return _localRotation;

		if (_parent == nullptr)
			_localRotation = _rotation;
		else
			_localRotation = _parent->GetRotation().Inverse() * _rotation;

		_localRotationDirty = false;
		return _localRotation;
	}

	void Transform::SetLocalRotation(const Quaternion& value)
	{
		MarkDirty(true, true, true);
		_localRotationDirty = false;
		_rotationDirty = true;

		_localMatrixDirty = true;

		_localRotation = value;
	}
	
	Vector3 Transform::GetEulerAngles()
	{
		Quaternion q = GetRotation();

		return q.EulerAngles();
	}

	void Transform::SetEulerAngles(const Vector3& value)
	{
		Quaternion q = Quaternion::Euler(value.x, value.y, value.z);
		SetRotation(q);
	}

	Vector3 Transform::GetLocalEulerAngles()
	{
		Quaternion q = GetLocalRotation();

		return q.EulerAngles();
	}

	void Transform::SetLocalEulerAngles(const Vector3& value)
	{
		Quaternion q = Quaternion::Euler(value.x, value.y, value.z);

		SetLocalRotation(q);
	}

	Vector3 Transform::GetLossyScale()
	{
		if(!_lossyScaleDirty)
			return _lossyScale;

		if (_parent == nullptr)
			_lossyScale = _localScale;
		else
		{
			Vector3 parentLossyScale = _parent->GetLossyScale();
			_lossyScale = Vector3(
				parentLossyScale.x * _localScale.x,
				parentLossyScale.y * _localScale.y,
				parentLossyScale.z * _localScale.z
			);
		}

		_lossyScaleDirty = false;
		return _lossyScale;
	}

	void Transform::SetLossyScale(const Vector3& value)
	{
		MarkDirty(true, false, true);
		_lossyScaleDirty = false;
		_localScaleDirty = true;

		_localMatrixDirty = true;

		_lossyScale = value;
	}

	Vector3 Transform::GetLocalScale()
	{
		if (!_localScaleDirty)
			return _localScale;

		if (_parent == nullptr)
			_localScale = _lossyScale;
		else
		{
			Vector3 parentLossyScale = _parent->GetLossyScale();
			_localScale = Vector3(
				_lossyScale.x / parentLossyScale.x,
				_lossyScale.y / parentLossyScale.y,
				_lossyScale.z / parentLossyScale.z
			);
		}

		_localScaleDirty = false;
		return _localScale;
	}

	void Transform::SetLocalScale(const Vector3& value)
	{
		MarkDirty(true, false, true);
		_lossyScaleDirty = true;
		_localScaleDirty = false;

		_localMatrixDirty = true;

		_localScale = value;
	}

	Matrix4x4 Transform::GetMatrix()
	{
		if (!_matrixDirty)
			return _matrix;

		if (_parent == nullptr)
			_matrix = GetLocalMatrix();
		else
			_matrix = _parent->GetMatrix() * GetLocalMatrix();

		_matrixDirty = false;
		return _matrix;
	}

	Matrix4x4 Transform::GetLocalMatrix()
	{
		if (!_localMatrixDirty)
			return _localMatrix;

		Vector3 localPosition = GetLocalPosition();
		Quaternion localRotation = GetLocalRotation();
		Vector3 localScale = GetLocalScale();

		const float x = localRotation.x;
		const float y = localRotation.y;
		const float z = localRotation.z;
		const float w = localRotation.w;

		const float xx = x + x;
		const float yy = y + y;
		const float zz = z + z;

		const float xx2 = x * xx;
		const float yy2 = y * yy;
		const float zz2 = z * zz;

		const float xy = x * yy;
		const float xz = x * zz;
		const float yz = y * zz;

		const float wx = w * xx;
		const float wy = w * yy;
		const float wz = w * zz;

		const float sx = localScale.x;
		const float sy = localScale.y;
		const float sz = localScale.z;

		// Rotation * Scale
		_localMatrix.m00 = (1.0f - (yy2 + zz2)) * sx;
		_localMatrix.m01 = (xy + wz) * sy;
		_localMatrix.m02 = (xz - wy) * sz;
		_localMatrix.m03 = 0.0f;

		_localMatrix.m10 = (xy - wz) * sx;
		_localMatrix.m11 = (1.0f - (xx2 + zz2)) * sy;
		_localMatrix.m12 = (yz + wx) * sz;
		_localMatrix.m13 = 0.0f;

		_localMatrix.m20 = (xz + wy) * sx;
		_localMatrix.m21 = (yz - wx) * sy;
		_localMatrix.m22 = (1.0f - (xx2 + yy2)) * sz;
		_localMatrix.m23 = 0.0f;

		// Translation
		_localMatrix.m30 = localPosition.x;
		_localMatrix.m31 = localPosition.y;
		_localMatrix.m32 = localPosition.z;
		_localMatrix.m33 = 1.0f;

		_localMatrixDirty = false;
		return _localMatrix;
	}

	void Transform::MarkDirty(bool position, bool rotation, bool scale, bool includeSelf)
	{
		if (includeSelf)
		{
			if (position)
			{
				GetLocalPosition();
				_positionDirty = true;
			}
			if (rotation)
			{
				GetLocalRotation();
				_rotationDirty = true;
			}
			if (scale)
			{
				GetLocalScale();
				_lossyScaleDirty = true;
			}
		}

		_matrixDirty = true;

		for (auto& child : _children)
			child->MarkDirty(position, rotation, scale, true);
	}
}