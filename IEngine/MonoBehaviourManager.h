#pragma once
#include "MonoBehaviour.h"
#include "Event.h"

#include <functional>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace IEngine
{
	class MonoBehaviourManager
	{
	public:
		template <typename T>
		static void RegisterMonoBehaviour(Pointer<T> monoBehaviour);

		template <typename T>
		static void UnregisterMonoBehaviour(Pointer<T> monoBehaviour);

		static void UpdateComponents();
		static void LateUpdateComponents();
		static void FixedUpdateComponents();
		static void RenderComponents();

	private:
		static Event<> _updateEvent;
		static Event<> _lateUpdateEvent;
		static Event<> _fixedUpdateEvent;
		static Event<> _renderEvent;

		static std::unordered_map<std::size_t, std::vector<Event<>::Connection>> _registeredDelegates;

		template <typename T, typename Callback>
		static void RegisterCallback(Pointer<T> monoBehaviour, Event<>& event, Callback&& callback, bool once = false);

		template <typename T>
		static void RegisterStart(Pointer<T> monoBehaviour);

		template <typename T>
		static void RegisterUpdate(Pointer<T> monoBehaviour);


		template <typename T>
		static void RegisterLateUpdate(Pointer<T> monoBehaviour);


		template <typename T>
		static void RegisterFixedUpdate(Pointer<T> monoBehaviour);


		template <typename T>
		static void RegisterRender(Pointer<T> monoBehaviour);
	};
}

#include "MonoBehaviourManager.inl"