#pragma once
#include <type_traits>
#include <string>
#include "Object.h"

template <typename T>
class PointerControlBlock;

template <typename T>
struct Pointer 
{
public:
	Pointer();
	Pointer(std::nullptr_t) noexcept : _controlBlock(nullptr) {}
	Pointer<T>(const T* other);
	Pointer<T>(const Pointer<T>& other);
	Pointer<T>(Pointer<T>&& other);

	template <typename U>
		requires std::derived_from<U, T>
	Pointer<T>(const U* other);

	template <typename U>
		requires std::derived_from<U, T>
	Pointer<T>(const Pointer<U>& other);

	template <typename U>
		requires std::derived_from<U, T>
	Pointer<T>(Pointer<U>&& other);

	~Pointer<T>();

	Pointer<T>& operator=(const Pointer<T>& other) noexcept;
	Pointer<T>& operator=(Pointer<T>&& other) noexcept;
	Pointer<T>& operator=(T* other) noexcept;
	Pointer<T>& operator=(T other) noexcept;

	static Pointer<T> Create();
	inline PointerControlBlock<T>* GetControlBlock() const;

	explicit operator bool() const;

	T* operator->() const;
	inline T* Get() const;

	bool operator==(const Pointer<T>& other) const noexcept;
	bool operator!=(const Pointer<T>& other) const noexcept;

	bool operator==(const T* other) const noexcept;
	bool operator!=(const T* other) const noexcept;

	bool operator==(std::nullptr_t) const noexcept;
	bool operator!=(std::nullptr_t) const noexcept;

	std::string ToString() const;

private:
	PointerControlBlock<T>* _controlBlock = nullptr;

	inline bool ControlBlockExists() const;
	inline bool TargetExists() const;
	inline void LinkControlBlock();
	inline void UnlinkControlBlock();
	inline void SetControlBlock(PointerControlBlock<T>* newBlock);
};

#include "Pointer.inl"