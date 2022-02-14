#ifndef _TOKAMEINE_STL_LIST_H_
#define _TOKAMEINE_STL_LIST_H_

#include "Alloc.h"
#include"Construct.h"
#include <type_traits>



namespace TokameinE {
	template<class T>
	struct ListNode {
		T data;
		void* prve;
		void* next;
		ListNode(const T& dat, ListNode* p, ListNode* n) :data(dat), prve(p), next(n) {};
	};

	template<class T>
	struct List_iterator {
		typedef List_iterator<T> iterator;
		//typedef List_iterator<T> self;

		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef size_t size_type;
		typedef ptrdiff_t	difference_type;
		typedef ListNode<T>* link_type;


		link_type node;

		List_iterator(){}
		List_iterator(link_type x):node(x) {}
		List_iterator(const iterator&x):node(x.node){}

		reference operator*()const { return (*node).data; }
		pointer operator->()const { return &(operator*()); }
		iterator& operator++() {
			node = (link_type)(*node).next;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp = *this;
			++*this();
			return tmp;
		}
		iterator& operator--()
		{
			node = (link_type)(*node).prve;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			--* this;
			return tmp;
		}
		bool operator==(const iterator&x)const{return node == x.node;}
		bool operator!=(const iterator& x)const { return node != x.node; }
	};

	template<class T,class Alloc=Allocator<ListNode<T>>>
	class list{
	public:
		typedef ListNode<T> List_Node;
		typedef List_Node* link_type;

		typedef List_iterator<T> iterator;
		typedef List_iterator<T> self;
		typedef T* pointer;
		typedef T& reference;

		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	private:
		link_type nodepointer;

	public:
	public:
		list() { init_empty_list(); }
		list(size_type n, const value_type& val = value_type()) {}
		template <class InputIterator>
		list(InputIterator first, InputIterator last);
		list(const list& l);
		~list(){
			link_type first = (link_type)(*nodepointer).next;
			link_type last = nodepointer;
			link_type next = (link_type)first->next;
			while (first!=last)
			{
				ruin_node(first);
				first = next;
			}
			ruin_node(last);
		};

	protected:
		void init_empty_list() {
			nodepointer=create_a_node();
			(*nodepointer).next = nodepointer;
			(*nodepointer).prve = nodepointer;
		}
		template<class Allocw = Alloc>
		link_type create_a_node() {
			return Allocw::allocate();
		}
		link_type active_node(const T& x) {
			link_type p = create_a_node();
			construct(&p->data, x);
			return p;
		}
		template<class Allocw = Alloc>
		void destroy_a_node(link_type p) {
			Allocw::deallocate(p);
		}
		void ruin_node(link_type p)
		{
			destory(&p->data);
			destroy_a_node(p);
		}

	public:
		iterator begin() { return (link_type)(*nodepointer).next; }
		iterator end() { return nodepointer; }

		reference front() { return begin()->data; }
		reference back() { return (--end())->data; }

		bool empty() { return nodepointer == nodepointer->next; }
		size_type size()const {
			size_type result = 0;
			link_type temp = (link_type)(*nodepointer).next;
			while (temp != nodepointer)
			{
				++result;
				++temp;
			}
			return result;
		}

		iterator insert(iterator pos, const T& val)
		{
			link_type tmp = active_node(val);


			tmp->next = pos.node;
			tmp->prve = pos.node->prve;
			((link_type)(pos.node->prve))->next = tmp;
			pos.node->prve = tmp;
			return tmp;
		}
		void push_back(const T& x) { insert(end(), x); }
		void push_front(const T& x) { insert(begin(), x); }
		iterator erase(iterator pos)
		{
			link_type prvenode = (link_type)pos.node->prve;
			link_type nextnode = (link_type)pos.node->next;
			prvenode->next = nextnode;
			nextnode->prve = prvenode;
			ruin_node(pos.node);
			return nextnode;
		}
		void pop_back() { erase(--(end())); }
		void pop_front() { erase(begin()); }
		void remove(const T& x) {
			iterator first = begin();
			iterator last = end();
			while (first != last)
			{
				iterator next = first;
				++next;
				if (*first == x)
					erase(first);
				first = next;
			}
		}
		void clear()
		{
			link_type cur = (link_type)(*nodepointer).next;
			while (cur != nodepointer)
			{
				link_type tmp = cur;
				cur = (link_type)cur->next;
				ruin_node(tmp);
			}
			nodepointer->next = nodepointer;
			nodepointer->prve = nodepointer;
		}
		void unique()
		{
			if (empty())return;
			iterator first = begin();
			iterator last = end();

			iterator next = first;
			while (++next != last)
			{
				if (*first == *next)
					erase(next);
				else
					first = next;
				next = first;
			}
		}
	};







}




#endif