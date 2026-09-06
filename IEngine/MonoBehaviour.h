#pragma once
#include "Component.h"
#include <type_traits>

namespace IEngine
{
	class MonoBehaviourManager;

	template <typename Derived>
	class MonoBehaviour : public Component
	{
	protected:
		friend class GameObject;
		void InitializeComponent(Pointer<GameObject> owner) override final;
	};
}

#include "MonoBehaviour.inl"