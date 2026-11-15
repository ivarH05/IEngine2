#include "Transform.h"
#include "Mathf.h"
#include <iostream>

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
		AddChild(Pointer<Transform>(const_cast<Transform*>(&child)));
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
		RemoveChild(Pointer<Transform>(const_cast<Transform*>(&child)));
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
		if (value == this)
			throw std::invalid_argument("Cannot set parent to self.");

		if (_parent == value)
			return;
		if (_parent != nullptr)
			_parent->RemoveChild(*this);
		if (value != nullptr)
			value->AddChild(*this);
		_parent = value;

		MarkDirty(true, true, true, true);
	}

	Vector3 Transform::TransformPoint(const Vector3& point)
	{
		return point * GetMatrix();
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
		if (!_rotationDirty)
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
		if (!_lossyScaleDirty)
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
		_localMatrix = Matrix4x4::TRS(GetLocalPosition(), GetLocalRotation(), GetLocalScale());

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

	void Transform::SetActiveInHierarchy(bool value)
	{
		if (_isActiveInHierarchy == value)
			return;
		_isActiveInHierarchy = value;

		if (!_isActive)
			return;

		for (auto& child : _children)
			child->SetActiveInHierarchy(value);
	}

	void Transform::SetActive(bool value)
	{
		if (_isActive == value)
			return;
		_isActive = value;

		if (!_isActiveInHierarchy)
			return;

		for (auto& child : _children)
			SetActiveInHierarchy(value);
	}

	bool Transform::IsActive() const
	{
		return _isActive && _isActiveInHierarchy;
	}
}