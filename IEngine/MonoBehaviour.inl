#include "MonoBehaviour.h"
#include "MonoBehaviourManager.h"
#include "GameObject.h"

namespace IEngine
{
	template <typename Derived>
	void MonoBehaviour<Derived>::InitializeComponent(Pointer<GameObject> owner)
	{
		static_assert(std::is_base_of_v<MonoBehaviour<Derived>, Derived>, "Derived must inherit from MonoBehaviour<Derived>");

		Pointer<Derived> self = Pointer<Derived>(static_cast<Derived*>(this));
		MonoBehaviourManager::RegisterMonoBehaviour(self);

		gameObject = owner;
		transform = owner->transform;
		CallAwake();
	}

	template <typename Derived>
	void MonoBehaviour<Derived>::CallAwake()
	{
		if constexpr (requires(Derived & value) { value.Awake(); })
			static_cast<Derived*>(this)->Awake();
	}
}