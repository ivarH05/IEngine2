#include "Object.h"

Object::Object() : _controlBlock(new PointerControlBlock<Object>(this)) { }

Object::~Object()
{
	_controlBlock->Disassemble();
}