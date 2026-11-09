#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Object.h"
#include "Pointer.h"

namespace IEngine
{
	class Transform;
	class Component;

	class GameObject : public Object
	{
	public:
		GameObject();

		template <typename T>
		Pointer<T> AddComponent();

		template <typename T>
		Pointer<T> GetComponent();

		const Pointer<Transform> transform;

	private:
		std::vector<Pointer<Component>> _components;
	};
}

#include "GameObject.inl"