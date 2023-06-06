#pragma once
#include <iostream>
#include <memory>
#include <map>

template <typename T, size_t N>
class CastAlloc {
public:
	using value_type = T;
	using propagate_on_copy_assignment = std::true_type;
	using propagate_on_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	template <typename U>
	struct rebind {
		using other = CastAlloc<U, N>;
	};
	void* block;	//Указатель на начало блока
	size_t pos;		//Размер типа объекта

	CastAlloc() {
		pos = 0;
		block=::operator new(sizeof(T) * N);
		if (!block)
			throw std::bad_alloc();

	}

	template<typename U>
	CastAlloc(const CastAlloc<U, N>& obj)noexcept :block(obj.block) {
		pos = obj.pos;
	}

	~CastAlloc() { ::operator delete(block); }

	T* allocate(size_t num) {
		if (num>N-pos)
			throw std::bad_alloc();
		auto p = (T*)block + pos;
		pos += num;
		return p;
	}
	void deallocate(T*, size_t) {}
};

template <class T, class U, size_t N>
constexpr bool operator== (const CastAlloc<T, N>& a1, const CastAlloc<U, N>& a2) noexcept{
	return a1.block == a2.block;
}

template <class T, class U, size_t N>
constexpr bool operator!= (const CastAlloc<T, N>& a1, const CastAlloc<U, N>& a2) noexcept{
	return a1.block != a2.block;
}





