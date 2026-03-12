#pragma once
#include <type_traits>
#include "PointerControlBlock.h"
#include "Object.h"

template <typename T>
PointerControlBlock<T>::PointerControlBlock(T* object) : _linkCount(0), _target(object)
{
}

template <typename T>
void PointerControlBlock<T>::Disassemble()
{
	_target = nullptr;
}


template <typename T>
void PointerControlBlock<T>::AddLink()
{
	std::cout << "Link added\n";
	_linkCount++;
}

template <typename T>
void PointerControlBlock<T>::RemoveLink()
{
	std::cout << "Link removed\n";
	_linkCount--;

	if (_linkCount > 0)
		return;

	if (_target != nullptr)
		delete _target;

	delete this;
}


template <typename T>
T* PointerControlBlock<T>::Get() const
{
	return _target;
}