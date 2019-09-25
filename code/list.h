#pragma once
#include <stdexcept>
#include <iostream>

class List
{
public:
// Typedefs
	typedef double value_type;
	typedef unsigned size;
private:
	struct Node
	{
		Node(const value_type& a)
			: item{ a } {};
		Node(void) {};
		value_type item;
		Node *next;
		Node *prev;
	};
public:
	class iterator
	{
	private:
		friend class List;
		iterator(Node *_elem)
			: elem{ _elem } {};
	public:
		// Constructors
		iterator(void)
			: elem{ 0 } {};
		iterator(const iterator &it)
			: elem{ it.elem } {};
		// Operators
		bool operator==(const iterator& it) const
		{
			return (elem == it.elem);
		}
		bool operator!=(const iterator& it) const
		{
			return !(*this == it);
		}
		iterator& operator++(void)
		{
			if (elem != 0)
			{
				elem = elem->next;
			}
			return *this;
		}
		iterator& operator--(void)
		{
			if (elem != 0)
			{
				elem = elem->prev;
			}
			return *this;
		}
		value_type& operator*(void) const
			throw(std::domain_error)
		{
			if (elem != 0)
			{
				return elem->item;
			}
			else
			{
				throw std::domain_error("Null iterator");
			}
		}
	private:
		Node *elem;
	};
// Constructors & Destructor
	List(void) throw(std::bad_alloc);
	List(const value_type&, size = 1) throw(std::bad_alloc);
	List(iterator, iterator) throw(std::bad_alloc);
	List(const List&) throw(std::bad_alloc);
	~List(void) throw();
	List& operator=(const List&) throw(std::bad_alloc);
// Iterators
	iterator begin(void);
	iterator end(void);
	iterator begin(void) const;
	iterator end(void) const;
// Methods
	bool empty(void) const;
	size length(void) const;
	value_type& front(void);
	value_type& back(void);
	iterator find(const value_type&) const;
	void push_front(const value_type&) throw(std::bad_alloc);
	void pop_front(void);
	void push_back(const value_type&) throw(std::bad_alloc);
	void pop_back(void);
	void insert(iterator, const value_type&) throw(std::bad_alloc);
	void erase(iterator);
	void erase(iterator, iterator);
	void remove(const value_type&);
	void swap(List&);
	void clear(void);
	void splice(List&) throw();
	void splice(iterator, List&) throw();
	void sort(void);
	void merge(List&) throw(std::bad_alloc);
private:
	size count;
	Node *Head;
	Node *Tail;
	iterator head, tail;
};