#pragma once
#include <type_traits>
#include "PointerControlBlock.h"
#include "Object.h"

namespace IEngine
{

	template <typename T>
	PointerControlBlock<T>::PointerControlBlock(T* object) : _linkCount(0), _target(object)
	{
		static_assert(!std::is_abstract<T>::value, "Type cannot be abstract");
		static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
	}

	template <typename T>
	PointerControlBlock<T>::~PointerControlBlock()
	{
		if (_target != nullptr)
			delete _target;
	}

	template <typename T>
	void PointerControlBlock<T>::Disassemble()
	{
		_target = nullptr;
	}


	template <typename T>
	void PointerControlBlock<T>::AddLink()
	{
		_linkCount++;
	}

	template <typename T>
	void PointerControlBlock<T>::RemoveLink()
	{
		_linkCount--;

		if (_linkCount > 0)
			return;

		delete this;
	}
}