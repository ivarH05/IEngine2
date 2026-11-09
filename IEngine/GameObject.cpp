#include "GameObject.h"
#include "Transform.h"

namespace IEngine
{

	GameObject::GameObject() : transform(new Transform())
	{
		_components.push_back(Pointer<Component>(transform));
		transform->InitializeComponent(Pointer<GameObject>(this));
	}
}