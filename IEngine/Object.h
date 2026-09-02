#pragma once
#include "PointerControlBlock.h"

template <typename T>
struct Pointer;

class Object
{
public:
	Object();
	~Object();

	PointerControlBlock<Object>* _controlBlock;
private:
};