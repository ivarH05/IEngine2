#include "Pointer.h"
#include "PointerControlBlock.h"
#include "Object.h"

// Copy Constructor
template <typename T>
Pointer<T>::Pointer<T>(const Pointer<T>& other) : _controlBlock(other._controlBlock)
{
	if (_controlBlock == nullptr)
		return;

	_controlBlock->AddLink();
}

// Move Constructor
template <typename T>
Pointer<T>::Pointer<T>(Pointer<T>&& other) : _controlBlock(other._controlBlock)
{
	other._controlBlock = nullptr;
}

// Destructor
template <typename T>
Pointer<T>::~Pointer<T>()
{
	if (_controlBlock == nullptr)
		return;

	_controlBlock->RemoveLink();
}

// Copy
template <typename T> 
Pointer<T>& Pointer<T>::operator=(const Pointer<T>& other) noexcept
{
	_controlBlock = other._controlBlock;

	if (_controlBlock == nullptr)
		return;

	_controlBlock->AddLink();
	return *this;
}

// Move
template <typename T>
Pointer<T>& Pointer<T>::operator=(Pointer<T>&& other) noexcept
{
	_controlBlock = other._controlBlock;
	other._controlBlock = nullptr;
	return *this;
}


// Dereference
template<typename T>
T* Pointer<T>::operator->() const
{
	return _controlBlock->Get();
}

// Constructor
template <typename T>
Pointer<T>::Pointer()
{
	static_assert(!std::is_abstract<T>::value, "Type cannot be abstract");
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
}

template <typename T>
std::string Pointer<T>::ToString() const
{
	std::ostringstream result;

	if (_controlBlock && _controlBlock->object)
		result << "Pointer, references: " << _controlBlock->ref_count << ", Object: " << _controlBlock->object;
	else
		result << "Pointer, NULL";

	return result.str();
}

// Compare to other pointers
template <typename T>
bool Pointer<T>::operator==(const Pointer<T>& other) noexcept
{
	return _controlBlock == other._controlBlock;
}

template <typename T>
bool Pointer<T>::operator!=(const Pointer<T>& other) noexcept
{
	return _controlBlock != other._controlBlock;
}

// Compare to objects
template <typename T>
bool Pointer<T>::operator==(const T* other) noexcept
{
	return _controlBlock->Get() == other;
}

template <typename T>
bool Pointer<T>::operator!=(const T* other) noexcept
{
	return _controlBlock->Get() != other;
}

// Compare to null pointer
template <typename T>
bool Pointer<T>::operator==(std::nullptr_t) noexcept
{
	return _controlBlock == nullptr;
}

template <typename T>
bool Pointer<T>::operator!=(std::nullptr_t) noexcept
{
	return _controlBlock != nullptr;
}


// Assign
template <typename T>
Pointer<T>& Pointer<T>::operator=(T* other) noexcept
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");

	_controlBlock = reinterpret_cast<PointerControlBlock<T>*>(other->_controlBlock);
	_controlBlock->AddLink();
	return *this;
}

// Assign
template <typename T>
Pointer<T>& Pointer<T>::operator=(T other) noexcept
{
	this = *other;
	return this;
}

// Assign
template <typename T>
T* Pointer<T>::Get() const
{
	return _controlBlock->Get();
}

template <typename T>
Pointer<T>::Pointer(T* other) 
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
	_controlBlock = reinterpret_cast<PointerControlBlock<T>*>(other->_controlBlock);
	_controlBlock->AddLink();
}