#pragma once
#include <stdexcept>
#include <iostream>

class List
{
public:
// Typedefs
	typedef double value_type;
	typedef unsigned size_type;
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
	protected:
		friend class Set;
		friend class List;
		iterator(Node *_elem)
			: elem{ _elem } {};
	public:
	// Constructors
		iterator(void)
			: elem{ nullptr } {};
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
			if (elem != nullptr)
			{
				elem = elem->next;
			}
			return *this;
		}
		iterator& operator--(void)
		{
			if (elem != nullptr)
			{
				elem = elem->prev;
			}
			return *this;
		}
		value_type& operator*(void) const
			throw(std::domain_error)
		{
			if (elem != nullptr)
			{
				return elem->item;
			}
			else
			{
				throw std::domain_error("Null iterator");
			}
		}
	protected:
		Node *elem;
	};
	class const_iterator final : public iterator
	{
	private:
		friend class Set;
		friend class List;
		const_iterator(Node *_elem)
			: iterator{ _elem } {};
	public:
		const_iterator(void)
			: iterator{} {};
		const_iterator(const iterator &it)
			: iterator{ static_cast<const iterator&>(it) } {};
		const_iterator(const const_iterator &it)
			: iterator{ static_cast<const iterator&>(it) } {};
		bool operator==(const const_iterator &it) const
		{
			return iterator::operator==(static_cast<const iterator&>(it));
		}
		bool operator!=(const const_iterator &it) const
		{
			return iterator::operator!=(static_cast<const iterator&>(it));
		}
		const_iterator operator++(void)
		{
			if (elem != nullptr)
			{
				elem = elem->next;
			}
			return *this;
		}
		const_iterator& operator--(void)
		{
			if (elem != nullptr)
			{
				elem = elem->prev;
			}
			return *this;
		}
		const value_type& operator*(void) const
		{
			if (elem != nullptr)
			{
				return elem->item;
			}
			else
			{
				throw std::domain_error("Null iterator");
			}
		}
	};
// Constructors & Destructor
	List(void) throw(std::bad_alloc);
	List(const value_type&, size_type = 1) throw(std::bad_alloc);
	List(iterator, iterator) throw(std::bad_alloc);
	List(const List&) throw(std::bad_alloc);
	~List(void) throw();
	List& operator=(const List&) throw(std::bad_alloc);
// Iterators
	iterator begin(void);
	iterator end(void);
	const_iterator cbegin(void) const;
	const_iterator cend(void) const;
// Methods
	bool empty(void) const;
	size_type length(void) const;
	value_type& front(void);
	value_type& back(void);
	const value_type& front(void) const;
	const value_type& back(void) const;
	iterator find(const value_type&);
	const_iterator find(const value_type&) const;
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
	size_type count;
	Node *Head;
	Node *Tail;
	iterator head, tail;
};