#pragma once
#include <type_traits>
#include "PointerControlBlock.h"
#include "Object.h"

template <typename T>
PointerControlBlock<T>::PointerControlBlock(T* object) : _linkCount(0), _objectExists(true), _target(object)
{
}

template <typename T>
void PointerControlBlock<T>::Disassemble()
{
	_target = nullptr;
	_objectExists = false;
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
	Disassemble();
}


template <typename T>
T* PointerControlBlock<T>::Get() const
{
	return _target;
}