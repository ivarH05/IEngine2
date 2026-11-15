#include "MonoBehaviourManager.h"
#include <iostream>

namespace IEngine
{
	Event<> MonoBehaviourManager::_updateEvent;
	Event<> MonoBehaviourManager::_lateUpdateEvent;
	Event<> MonoBehaviourManager::_fixedUpdateEvent;
	Event<> MonoBehaviourManager::_renderEvent;
	std::unordered_map<std::size_t, std::vector<Event<>::Connection>> MonoBehaviourManager::_registeredDelegates;

	void MonoBehaviourManager::UpdateComponents()
	{
		_updateEvent.Invoke();
	}

	void MonoBehaviourManager::LateUpdateComponents()
	{
		_lateUpdateEvent.Invoke();
	}

	void MonoBehaviourManager::FixedUpdateComponents()
	{
		_fixedUpdateEvent.Invoke();
	}

	void MonoBehaviourManager::RenderComponents()
	{
		_renderEvent.Invoke();
	}
}