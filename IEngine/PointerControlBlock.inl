#pragma once
#include <type_traits>
#include "PointerControlBlock.h"
#include "Object.h"

template <typename T>
PointerControlBlock<T>::PointerControlBlock(T* object) : _linkCount(0), _target(object)
{
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