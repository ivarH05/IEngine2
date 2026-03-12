#pragma once
#include <type_traits>

// forward decl
template <typename T>
struct Pointer;

class Object;

template <typename T>
class PointerControlBlock 
{
private:
	friend Pointer<T>;
	friend Object;

	PointerControlBlock(T* object);
	~PointerControlBlock();

	void Disassemble();
	void AddLink();
	void RemoveLink();

	T* _target = nullptr;
	int _linkCount = 0;
};

#include "PointerControlBlock.inl"