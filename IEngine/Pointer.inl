#include "Pointer.h"
#include "PointerControlBlock.h"
#include "Object.h"

// Constructor base
template <typename T>
Pointer<T>::Pointer()
{
	static_assert(!std::is_abstract<T>::value, "Type cannot be abstract");
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
}


// Constructor with instant assignment
template <typename T>
Pointer<T>::Pointer(const T* other)
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
	_controlBlock = reinterpret_cast<PointerControlBlock<T>*>(other->_controlBlock);
	_controlBlock->AddLink();
}

// Copy Constructor
template <typename T>
Pointer<T>::Pointer(const Pointer<T>& other) : _controlBlock(other._controlBlock)
{
	LinkControlBlock();
}

// Move Constructor
template <typename T>
Pointer<T>::Pointer(Pointer<T>&& other) : _controlBlock(other._controlBlock)
{
	other._controlBlock = nullptr;
}


// Constructor with instant assignment
template <typename T>
template <typename U>
	requires std::derived_from<U, T>
Pointer<T>::Pointer(const U* other)
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
	_controlBlock = reinterpret_cast<PointerControlBlock<T>*>(other->_controlBlock);
	_controlBlock->AddLink();
}

// Copy Constructor
template <typename T>
template <typename U>
	requires std::derived_from<U, T>
Pointer<T>::Pointer(const Pointer<U>& other) : _controlBlock(reinterpret_cast<PointerControlBlock<T>*>(other.GetControlBlock()))
{
	LinkControlBlock();
}

// Move Constructor
template <typename T>
template <typename U>
	requires std::derived_from<U, T>
Pointer<T>::Pointer(Pointer<U>&& other) : _controlBlock(other._controlBlock)
{
	other._controlBlock = nullptr;
}

template <typename T>
Pointer<T> Pointer<T>::Create()
{
	static_assert(!std::is_abstract<T>::value, "Type cannot be abstract");
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");

	Pointer<T> pointer;
	T* object = new T();

	pointer.SetControlBlock(new PointerControlBlock<T>(object));

	return pointer;
}

// Destructor
template <typename T>
Pointer<T>::~Pointer()
{
	UnlinkControlBlock();
}

// Copy
template <typename T> 
Pointer<T>& Pointer<T>::operator=(const Pointer<T>& other) noexcept
{
	SetControlBlock(other._controlBlock);
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
	return _controlBlock->_target;
}

template <typename T>
std::string Pointer<T>::ToString() const
{
	if (TargetExists())
		return "Pointer, references: " << _controlBlock->ref_count << ", Object: " << _controlBlock->_target;
	else
		return "Pointer, NULL";
}


// Compare to other pointers
template <typename T>
bool Pointer<T>::operator==(const Pointer<T>& other) const noexcept
{
	return _controlBlock == other._controlBlock;
}

template <typename T>
bool Pointer<T>::operator!=(const Pointer<T>& other) const noexcept
{
	return _controlBlock != other._controlBlock;
}

// Compare to objects
template <typename T>
bool Pointer<T>::operator==(const T* other) const noexcept
{
	return ControlBlockExists() && Get() == other;
}

template <typename T>
bool Pointer<T>::operator!=(const T* other) const noexcept
{
	return ControlBlockExists() && Get() != other;
}

// Compare to null pointer
template <typename T>
bool Pointer<T>::operator==(std::nullptr_t) const noexcept
{
	return !TargetExists();
}

template <typename T>
bool Pointer<T>::operator!=(std::nullptr_t) const noexcept
{
	return TargetExists();
}


// Assign
template <typename T>
Pointer<T>& Pointer<T>::operator=(T* other) noexcept
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");

	if (other == nullptr)
		SetControlBlock(nullptr);
	else
		SetControlBlock(reinterpret_cast<PointerControlBlock<T>*>(other->_controlBlock));

	return *this;
}

// Assign
template <typename T>
Pointer<T>& Pointer<T>::operator=(T other) noexcept
{
	this = *other;
	return this;
}


template<typename T>
Pointer<T>::operator bool() const
{
	return _controlBlock != nullptr && _controlBlock->_target != nullptr;;
}

template <typename T>
inline T* Pointer<T>::Get() const
{
	return _controlBlock->_target;
}

template<typename T>
inline bool Pointer<T>::ControlBlockExists() const
{
	return _controlBlock != nullptr;
}

template<typename T>
inline bool Pointer<T>::TargetExists() const
{
	return ControlBlockExists() && _controlBlock->_target != nullptr;
}

template<typename T>
inline void Pointer<T>::LinkControlBlock()
{
	if (ControlBlockExists())
		_controlBlock->AddLink();
}

template<typename T>
inline void Pointer<T>::UnlinkControlBlock()
{
	if (ControlBlockExists())
		_controlBlock->RemoveLink();
}

template<typename T>
inline void Pointer<T>::SetControlBlock(PointerControlBlock<T>* newBlock)
{
	UnlinkControlBlock();
	_controlBlock = newBlock;
	LinkControlBlock();
}

template<typename T>
inline PointerControlBlock<T>* Pointer<T>::GetControlBlock() const
{
	return _controlBlock;
}