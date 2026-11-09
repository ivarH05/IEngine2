#include "MonoBehaviourManager.h"
#include "Transform.h"
#include <iostream>

namespace IEngine
{
	template <typename T, typename Callback>
	void MonoBehaviourManager::RegisterCallback(Pointer<T> monoBehaviour, Event<>& event, Callback&& callback, bool once)
	{
		auto& connections = _registeredDelegates[monoBehaviour->guid];
		if (once)
			connections.emplace_back(event.ConnectOnce(std::forward<Callback>(callback)));
		else
			connections.emplace_back(event.Connect(std::forward<Callback>(callback)));
	}

	template <typename T>
	void MonoBehaviourManager::RegisterMonoBehaviour(Pointer<T> monoBehaviour)
	{
		static_assert(std::is_base_of_v<MonoBehaviour<T>, T>, "T must inherit from MonoBehaviour<T>");
		static_assert(!std::is_abstract<T>::value, "T cannot be abstract");

		UnregisterMonoBehaviour(monoBehaviour);

		RegisterStart(monoBehaviour);
		RegisterUpdate(monoBehaviour);
		RegisterLateUpdate(monoBehaviour);
		RegisterFixedUpdate(monoBehaviour);
		RegisterRender(monoBehaviour);
	}

	template <typename T>
	void MonoBehaviourManager::UnregisterMonoBehaviour(Pointer<T> monoBehaviour)
	{
		static_assert(std::is_base_of_v<MonoBehaviour<T>, T>, "T must inherit from MonoBehaviour<T>");
		static_assert(!std::is_abstract<T>::value, "T cannot be abstract");

		_registeredDelegates.erase(monoBehaviour->guid);
	}

	template <typename T>
	void MonoBehaviourManager::RegisterStart(Pointer<T> monoBehaviour)
	{
		if constexpr (requires(T & value) { value.Start(); })
		{
			auto startDelegate = [monoBehaviour]() mutable
				{
					if (monoBehaviour->transform->IsActive() && monoBehaviour->IsEnabled())
						monoBehaviour->Start();
				};
			RegisterCallback(monoBehaviour, _updateEvent, std::move(startDelegate), true);
		}
	}

	template <typename T>
	void MonoBehaviourManager::RegisterUpdate(Pointer<T> monoBehaviour)
	{
		if constexpr (requires(T & value) { value.Update(); })
		{
			auto updateDelegate = [monoBehaviour]() mutable
				{
					if (monoBehaviour->transform->IsActive() && monoBehaviour->IsEnabled())
						monoBehaviour->Update();
				};
			RegisterCallback(monoBehaviour, _updateEvent, std::move(updateDelegate));
		}
	}

	template <typename T>
	void MonoBehaviourManager::RegisterLateUpdate(Pointer<T> monoBehaviour)
	{
		if constexpr (requires(T & value) { value.LateUpdate(); })
		{
			auto lateUpdateDelegate = [monoBehaviour]()
				{
					if (monoBehaviour->transform->IsActive() && monoBehaviour->IsEnabled())
						monoBehaviour->LateUpdate();
				};
			RegisterCallback(monoBehaviour, _lateUpdateEvent, std::move(lateUpdateDelegate));
		}
	}

	template <typename T>
	void MonoBehaviourManager::RegisterFixedUpdate(Pointer<T> monoBehaviour)
	{
		if constexpr (requires(T & value) { value.FixedUpdate(); })
		{
			auto fixedUpdateDelegate = [monoBehaviour]()
				{
					if (monoBehaviour->transform->IsActive() && monoBehaviour->IsEnabled())
						monoBehaviour->FixedUpdate();
				};
			RegisterCallback(monoBehaviour, _fixedUpdateEvent, std::move(fixedUpdateDelegate));
		}
	}

	template <typename T>
	void MonoBehaviourManager::RegisterRender(Pointer<T> monoBehaviour)
	{
		std::cout << "aaa";
		if constexpr (requires(T & value) { value.OnRender(); })
		{
			std::cout << "bbb";
			auto renderDelegate = [monoBehaviour]()
				{
					if (monoBehaviour->transform->IsActive() && monoBehaviour->IsEnabled())
						monoBehaviour->OnRender();
				};
			RegisterCallback(monoBehaviour, _renderEvent, std::move(renderDelegate));
		}
	}
}