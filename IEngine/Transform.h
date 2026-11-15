#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "MonoBehaviour.h"
#include "Pointer.h"
#include <vector>
#include <string>
#include <iostream>

template <typename T>
using Vector = std::vector<T>;

namespace IEngine
{
	class Transform :
		public MonoBehaviour<Transform>
	{
	public:
		std::string name = "GameObject";

		void SetActive(bool value);
		bool IsActive() const;

		Vector3 GetPosition();
		void SetPosition(const Vector3& value);
		Vector3 GetEulerAngles();
		void SetEulerAngles(const Vector3& value);
		Vector3 GetLossyScale();
		void SetLossyScale(const Vector3& value);
		Quaternion GetRotation();
		void SetRotation(const Quaternion& value);

		Vector3 GetLocalPosition();
		void SetLocalPosition(const Vector3& value);
		Vector3 GetLocalEulerAngles();
		void SetLocalEulerAngles(const Vector3& value);
		Vector3 GetLocalScale();
		void SetLocalScale(const Vector3& value);
		Quaternion GetLocalRotation();
		void SetLocalRotation(const Quaternion& value);

		Matrix4x4 GetMatrix();
		Matrix4x4 GetLocalMatrix();

		Pointer<Transform> GetParent() const;
		void SetParent(const Pointer<Transform> value);

		Pointer<Transform> GetChildAt(int index);
		int ChildCount() const;

		Vector3 TransformPoint(const Vector3& point);
		Vector3 InverseTransformPoint(const Vector3& point);

	private:
		bool _isActive = true;
		bool _isActiveInHierarchy = true;

		Pointer<Transform> _parent = nullptr;
		Vector<Pointer<Transform>> _children = Vector<Pointer<Transform>>();

		Vector3 _position = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 _localPosition = Vector3(0.0f, 0.0f, 0.0f);
		bool _positionDirty = true;
		bool _localPositionDirty = false;

		Vector3 _lossyScale = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 _localScale = Vector3(1.0f, 1.0f, 1.0f);
		bool _lossyScaleDirty = true;
		bool _localScaleDirty = false;

		Quaternion _rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
		Quaternion _localRotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
		bool _rotationDirty = true;
		bool _localRotationDirty = false;

		Matrix4x4 _matrix;
		Matrix4x4 _localMatrix;
		bool _matrixDirty = true;
		bool _localMatrixDirty = true;

		void AddChild(const Pointer<Transform> child);
		void AddChild(const Transform& child);
		void RemoveChild(const Pointer<Transform> child);
		void RemoveChild(const Transform& child);

		void MarkDirty(bool position, bool rotation, bool scale, bool includeSelf = false);
		void SetActiveInHierarchy(bool value);
	};
}