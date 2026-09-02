#pragma once
#include "Pointer.h"
#include "GameObject.h"

namespace IEngine
{
    class Transform;

    class Component :
        public Object
    {
    public:
        Pointer<GameObject> gameObject;
		Pointer<Transform> transform;
    };
}