#pragma once
#include "Pointer.h"

namespace IEngine
{
    class Transform;
    class GameObject;

    class Component :
        public Object
    {
    public:
        bool IsEnabled() const;
        void SetEnabled(bool enabled);


        Pointer<GameObject> gameObject;
		Pointer<Transform> transform;

    protected:
		friend class GameObject;
        virtual void InitializeComponent(Pointer<GameObject> owner) = 0;

    private:
		bool _enabled = true;
    };
}