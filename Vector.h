#ifndef _TOKAMEINE_STL_VECTOR_H_
#define _TOKAMEINE_STL_VECTOR_H_

#include <type_traits>
#include "Alloc.h"
#include"Construct.h"
#include"CopyFunction.h"
namespace TokameinE {

	template<class T, class Alloc = Allocator<T>>
	class vector {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t	difference_type;
		typedef pointer iterator;

	protected:
		iterator start;
		iterator finish;
		iterator endOfStorage;
		typedef Alloc dataAllocator;

	public:
		vector() :start(0), finish(0), endOfStorage(0) {};
		vector(const size_type n, const value_type& value);
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(vector&& v);
		~vector();

		vector& operator=(const vector& v);
		vector& operator=(vector&& v);
		bool operator==(const vector<T, Alloc>& x)const;
		bool operator!=(const vector&)const;
		reference operator[](size_type n)const;

		//Iterators
		iterator begin() { return start; };
		iterator end() { return finish; };

		//Capacity
		difference_type size()const { return (finish - start); };
		difference_type capacity() { return endOfStorage - start; };
		bool empty() { return (start == finish ? 1 : 0); };


		//Modifiers
		void push_back(const value_type& value);
		void pop_back();
		void insert(iterator position, const_reference val);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector<T, Alloc>& obj);
		void clear();
		reference front(){ return *begin(); };
		reference back(){ return *end();};

		//Allocator
		Alloc get_allocator() { return dataAllocator; };


	private:
		void destroyAllVector();
		void insert_aux(iterator position, const_reference x);
	};

	template<class T, class Alloc>
	void vector<T,Alloc>::push_back(const value_type& value) {
		if (finish != endOfStorage)//Ã»Âú
		{
			construct(finish, value);
			++finish;
		}
		else
		{
			insert_aux(end(),value);
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::insert_aux(iterator position, const_reference x)
	{
		if (finish != endOfStorage)
		{
			construct(finish, *(finish-1));
			++finish;
			std::copy_backward(position,finish-2,finish-1);
			*position = x;
			//value_type temp = x;
			//*position = temp;
			//why not do *position=x?
		}
		else
		{
			const size_type old_size = size();
			const size_type len = old_size == 0 ? 1 : 2 * old_size;
			iterator new_start = dataAllocator::allocate(len);
			iterator new_finish = new_start;
			try {
				new_finish = TokameinE::uninitialized_copy(start,position,new_start);
				construct(new_finish, x);
				++new_finish;
				new_finish = TokameinE::uninitialized_copy(position, finish, new_finish);
			}
			catch(...){
				destory(new_start,new_finish);
				dataAllocator::deallocate(new_start,len);
				throw;
			}
			destory(start, finish);
			dataAllocator::deallocate(start);
			start = new_start;
			finish = new_finish;
			endOfStorage = new_start + len;
		}
	}


	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back() {
		--finish;
		dataAllocator::deallocate(finish);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, const_reference val) 
	{
		insert_aux(position, val);
	}




	//
	template<class T, class Alloc>
	vector<T, Alloc>::~vector() {
		destroyAllVector();
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::destroyAllVector() 
	{
		dataAllocator::destroy(start, finish);
		dataAllocator::deallocate(start, capacity());
	}


	template<class T, class Alloc>
	void vector<T, Alloc>::clear()
	{
		dataAllocator::destroy(start, finish);
		finish = start;
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
	{
		if (position + 1 != end())
		{
			TokameinE::copy(position + 1, finish, position);
		}
		--finish;
		destory(finish);
		return position;
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		iterator i = TokameinE::copy(last, finish, first);
		destory(i, finish);
		finish = finish - (last - first);
		return first;
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::swap(vector<T, Alloc>& obj) {
		iterator temp_start = start;
		iterator temp_finish = finish;
		iterator temp_end = endOfStorage;
		start = obj.start;
		finish = obj.finish;
		endOfStorage = obj.endOfStorage;

		obj.start = temp_start;
		obj.finish = temp_finish;
		obj.endOfStorage = temp_end;
	}

	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v) {
		if (*this != v)
		{
			destroyAllVector();
			start = dataAllocator::allocate(v.endOfStorage - v.start);
			finish = TokameinE::uninitialized_copy(v.start, v.finish, start);
			endOfStorage = start+(v.endOfStorage-v.start);
		}
		return *this;
	}
	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& v) {
		destroyAllVector();
		start = v.start;
		finish = v.finish;
		endOfStorage = v.endOfStorage;
		v.start = v.finish = v.endOfStorage = 0;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n)const
	{
		return *(begin() + n);
	}
	template<class T, class Alloc>
	bool vector<T, Alloc>::operator==(const vector<T, Alloc>& v)const
	{
		if (size() != v.size())
			return false;
		else
		{
			auto ptr1 = start;
			auto ptr2 = v.start;
			for (; ptr1!=finish&&ptr2!=v.finish; ++ptr1, ++ptr2)
			{
				if (*ptr1 != *ptr2)
					return false;
			}
			return true;
		}
	}
	template<class T, class Alloc>
	bool vector<T, Alloc>::operator!=(const vector& v)const
	{
		return !(v==*this);
	}

	template<class T, class Alloc>
	bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {
		return v1.operator==(v2);
	}

}
#endif
