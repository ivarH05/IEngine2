#include "Component.h"

namespace IEngine
{
	bool Component::IsEnabled() const
	{
		return _enabled;
	}
	void Component::SetEnabled(bool enabled)
	{
		_enabled = enabled;
	}
}