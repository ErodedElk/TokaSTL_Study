#ifndef _TOKAMEINE_STL_ALLOC_H_
#define _TOKAMEINE_STL_ALLOC_H_



#include<new>
#include<cstddef>
#include<cstdlib>
#include<climits>
#include<iostream>

namespace TokameinE {
	template<class T>
	class Allocator {
	public:
		typedef T type_value;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<class U>
		struct rebind {
			typedef Allocator<U> other;
		};


		static T* allocate();
		static T* allocate(size_type n);
		static void deallocate(pointer ptr);
		static void deallocate(pointer ptr, size_type n);

		static void construct(pointer ptr);
		static void construct(pointer ptr, const_reference val);
		static void destroy(pointer ptr);
		static void destroy(pointer first, pointer last);

	};
	template<class T>
	T* Allocator<T>::allocate() {
		//int sizettt = sizeof(T);
		T* ptr = (T*)malloc(sizeof(T));
		if (!ptr)
		{
			std::cerr << "out of mem";
			exit(1);
		}
		return ptr;
	}
	template<class T>
	T* Allocator<T>::allocate(size_type n) {
		if (0 == n)return 0;
		T* ptr = (T*)malloc(n * sizeof(T));
		if (!ptr)
		{
			std::cerr << "out of mem";
			exit(1);
		}
		return ptr;
	}

	template<class T>
	void Allocator<T>::deallocate(pointer ptr) {
		free(ptr);
	}
	template<class T>
	void Allocator<T>::deallocate(pointer ptr, size_type n) {
		free(ptr);//do something
	}

	template<class T>
	void Allocator<T>::construct(pointer ptr) {
		new(ptr) T();
	}

	template<class T>
	void Allocator<T>::construct(pointer ptr, const_reference val) {
		new(ptr) T(val);
	}

	template<class T>
	void Allocator<T>::destroy(pointer ptr) {
		ptr->~T();
	}
	template<class T>
	void Allocator<T>::destroy(pointer first, pointer last) {
		pointer temphead = first;
		for (; temphead != last; ++temphead)
			temphead->~T();//test
	}
}

#endif