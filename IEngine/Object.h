#pragma once
#include "PointerControlBlock.h"

namespace IEngine
{
	template <typename T>
	struct Pointer;

	class Object
	{
	public:
		Object();
		~Object();
		const std::size_t guid;

		PointerControlBlock<Object>* _controlBlock;

		virtual void OnDestroy() {}
	};
}