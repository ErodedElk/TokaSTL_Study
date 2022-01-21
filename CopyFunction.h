#ifndef _TOKAMEINE_STL_COPY_FUNCTION_H_
#define _TOKAMEINE_STL_COPY_FUNCTION_H_
#include"Vector.h"
#include"TypeTraits.h"
#include"Construct.h"
namespace TokameinE {


	//uninitialized_copy
	template<class ForwardIterator,class NoInitIterator>
	inline NoInitIterator uninitialized_copy(ForwardIterator first, ForwardIterator last,NoInitIterator dest)
	{
		return uninitialized_copy_aux(first, last, dest, TokameinE::_type_traits<ForwardIterator>::has_trivial_copy_constructor());
	}
	template<class ForwardIterator, class NoInitIterator>
	NoInitIterator uninitialized_copy_aux(ForwardIterator first, ForwardIterator last, NoInitIterator dest, TokameinE::_false_type)
	{
		for (;first!=last;++first,++dest)
		{
			construct(dest, *first);
		}
		return dest;
	}
	template<class ForwardIterator, class NoInitIterator>
	NoInitIterator uninitialized_copy_aux(ForwardIterator first, ForwardIterator last, NoInitIterator dest, TokameinE::_true_type)
	{
		memcpy(dest, first, (last - first) * sizeof(*first));
		return dest + (last - first);
	}
	//copy
	template<class ForwardIterator, class NoInitIterator>
	NoInitIterator copy(ForwardIterator first, ForwardIterator last, NoInitIterator dest)
	{
		return copy_aux(first, last, dest, TokameinE::_type_traits<ForwardIterator>::is_POD_type());
	}
	template<class ForwardIterator, class NoInitIterator>
	NoInitIterator copy_aux(ForwardIterator first, ForwardIterator last, NoInitIterator dest, TokameinE::_true_type)
	{
		memcpy(dest,first,last-first);
		return dest + (last-first)+1;
	}
	template<class ForwardIterator, class NoInitIterator>
	NoInitIterator copy_aux(ForwardIterator first, ForwardIterator last, NoInitIterator dest, TokameinE::_false_type)
	{
		while (first != last) {
			*dest = *first;
			++dest;
			++first;
		}
		return dest;
	}

}



#endif