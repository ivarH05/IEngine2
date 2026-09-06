#include "Object.h"
#include "Objectmanager.h"

namespace IEngine
{
	Object::Object() : _controlBlock(nullptr), guid(ObjectManager::GenerateGUID()) {}

	Object::~Object()
	{
		if (_controlBlock != nullptr)
			_controlBlock->Disassemble();
	}
}