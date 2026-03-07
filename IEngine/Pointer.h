#pragma once
#include <type_traits>
#include <string>

template <typename T>
class PointerControlBlock;

class Object;

template <typename T>
struct Pointer 
{
	static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");

public:
	Pointer();
	Pointer(T* other);
	Pointer<T>(const Pointer<T>&);
	Pointer<T>(Pointer<T>&&);

	~Pointer<T>();

	Pointer<T>& operator=(const Pointer<T>&) noexcept;
	Pointer<T>& operator=(Pointer<T>&&) noexcept;
	Pointer<T>& operator=(T*) noexcept;
	Pointer<T>& operator=(T) noexcept;

	static Pointer<T> Create();

	T* operator->() const;
	T* Get() const;

	bool operator==(const Pointer<T>& other) noexcept;
	bool operator!=(const Pointer<T>& other) noexcept;

	bool operator==(const T* other) noexcept;
	bool operator!=(const T* other) noexcept;

	bool operator==(std::nullptr_t) noexcept;
	bool operator!=(std::nullptr_t) noexcept;

	std::string ToString() const;

private:
	PointerControlBlock<T>* _controlBlock = nullptr;
};

#include "Pointer.inl"