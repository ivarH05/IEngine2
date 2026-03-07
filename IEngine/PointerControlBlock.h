#pragma once
#include <type_traits>

// forward decl
template <typename T>
struct Pointer;

class Object;

template <typename T>
class PointerControlBlock 
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");

private:
	friend Pointer<T>;
	friend Object;

	PointerControlBlock(T* object);

	void Disassemble();
	void AddLink();
	void RemoveLink();

	T* Get() const;

	T* _target = nullptr;
	int _linkCount = 0;
	bool _objectExists = false;
};

#include "PointerControlBlock.inl"