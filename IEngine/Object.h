#pragma once
#include "PointerControlBlock.h"

class Object
{
public:
	Object();
	~Object();

	PointerControlBlock<Object>* _controlBlock;
private:
};