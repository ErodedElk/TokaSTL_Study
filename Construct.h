#ifndef _TOKAMEINE_STL_CONSTRUCT_H_
#define _TOKAMEINE_STL_CONSTRUCT_H_



namespace TokameinE {
	template<class T>
	inline void construct(T* ptr,T val)
	{
		new(ptr) T(val);
	}

	template<class T>
	inline void destory(T* ptr)
	{
		ptr->~T();
	}
	template<class T>
	inline void destory(T* first,T* last)
	{
		for(;first!=last;++first)
			first->~T();
	}








}
#endif