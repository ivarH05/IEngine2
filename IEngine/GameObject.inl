#include "GameObject.h"

namespace IEngine
{
	template <typename T>
	Pointer<T> GameObject::AddComponent()
	{
		static_assert(!std::is_abstract<T>::value, "Type cannot be abstract");
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");
		
		Pointer<T> comp = new T();
		_components.push_back(comp);
		comp->InitializeComponent(Pointer<GameObject>(this));
		return comp;
	}
}