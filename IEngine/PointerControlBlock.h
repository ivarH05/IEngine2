#pragma once
#include <type_traits>

namespace IEngine
{
	// forward decl
	template <typename T>
	struct Pointer;

	class Object;

	template <typename T>
	class PointerControlBlock
	{
	public:
		PointerControlBlock(T* object);
		~PointerControlBlock();

		void Disassemble();
		void AddLink();
		void RemoveLink();

		T* _target = nullptr;
		int _linkCount = 0;
	};
}

#include "PointerControlBlock.inl"