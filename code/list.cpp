#include "list.h"

List::List(void)
	throw(std::bad_alloc)
	: Head{ new Node{} }, Tail{ Head }, count{ 0 }
{
	Tail->next = Tail->prev = 0;
	head = iterator{ Head };
	tail = iterator{ Tail };
}

List::List(const value_type& a, size_type n)
	throw(std::bad_alloc)
{
	List tmp{};
	for (List::size_type i{}; i < n; ++i)
	{
		tmp.push_front(a);
	}
	this->swap(tmp);
}

List::List(iterator first, iterator last)
	throw(std::bad_alloc)
{
	Head = Tail = nullptr;
	List tmp{};
	for (iterator it = first; it != last; ++it)
	{
		tmp.push_back(*it);
	}
	this->swap(tmp);
}

List::List(const List& r)
	throw(std::bad_alloc)
{
	Head = Tail = nullptr;
	*this = r;
}

List::~List(void) throw()
{
	Node *delete_Node = Head;
	for (Node *p = Head; p != Tail;)
	{
		p = p->next;
		delete delete_Node;
		--count;
		delete_Node = p;
	}
	delete delete_Node;
}

List& List::operator=(const List& rhs)
	throw(std::bad_alloc)
{
	if (this != &rhs)
	{
		List tmp{};
		for (auto rhs_it = rhs.cbegin(); rhs_it != rhs.cend(); ++rhs_it)
		{
			tmp.push_back(*rhs_it);
		}
		this->swap(tmp);
	}
	return *this;
}

List::iterator List::begin(void)
{
	return head;
}

List::iterator List::end(void)
{
	return tail;
}

List::const_iterator List::cbegin(void) const
{
	return head;
}

List::const_iterator List::cend(void) const
{
	return tail;
}

bool List::empty(void) const
{
	return (Head == Tail);
}

List::size_type List::length(void) const
{
	return count;
}

List::value_type& List::front(void)
{
	return *begin();
}

List::value_type& List::back(void)
{
	return *(--end());
}

const List::value_type& List::front(void) const
{
	return *cbegin();
}

const List::value_type& List::back(void) const
{
	return *(--cend());
}

List::iterator List::find(const value_type& a)
{
	for (auto it = begin(); it != end(); ++it)
	{
		if (*it == a)
		{
			return it;
		}
	}
	return this->end();
}

List::const_iterator List::find(const value_type& a) const
{
	for (auto it = cbegin(); it != cend(); ++it)
	{
		if (*it == a)
		{
			return it;
		}
	}
	return this->cend();
}

void List::push_front(const value_type &value)
	throw(std::bad_alloc)
{
	Node *new_Node = new Node{ value };
	new_Node->prev = nullptr;
	new_Node->next = Head;
	Head->prev = new_Node;
	Head = new_Node;
	head = iterator{ Head };
	++count;
}

void List::pop_front(void) 
{
	if (!empty())
	{
		Node *del = Head;
		Node *nextel = del->next;
		nextel->prev = nullptr;
		delete del;
		Head = nextel;
		head = iterator{Head};
		--count;
	}
}

void List::push_back(const value_type &value)
	throw(std::bad_alloc)
{
	if (!length())
	{
		push_front(value);
	}
	else
	{
		Node *new_Node = new Node{ value };
		Node *prevel = Tail->prev;
		prevel->next = new_Node;
		new_Node->prev = prevel;
		new_Node->next = Tail;
		Tail->prev = new_Node;
		++count;
	}
}

void List::pop_back(void)
{
	if (!empty())
	{
		Node *del = Tail->prev;
		Node *prevel = del->prev;
		Node *nextel = del->next;
		if (del == Head)
		{
			Head = Tail;
			head = iterator{ Head };
		}
		else if (prevel != nullptr)
		{
			prevel->next = nextel;
		}
		nextel->prev = prevel;
		delete del;
		--count;
	}
}

void List::insert(iterator it, const value_type &r)
	throw(std::bad_alloc)
{
	Node *el = it.elem;
	if (it == --end())
	{
		push_back(r);
	}
	else
	{
		Node *nextel = it.elem->next;
		Node *p = new Node{ r };
		p->next = nextel;
		p->prev = el;
		nextel->prev = p;
		el->next = p;
		++count;
	}
}

void List::erase(iterator it)
{
	if (it == begin())
	{
		pop_front();
	}
	else if (it == --end())
	{
		pop_back();
	}
	else
	{
		Node *el = it.elem;
		Node *prevel = it.elem->prev;
		Node *nextel = it.elem->next;
		prevel->next = nextel;
		nextel->prev = prevel;
		delete el;
		--count;
	}
}

void List::erase(iterator first, iterator last)
{
	while (first != last)
	{
		erase(first);
	}
}

void List::remove(const value_type &value)
{
	for (auto it = begin(); it != end();)
	{
		if (*it == value)
		{
			auto delElement = it;
			++it;
			erase(delElement);
		}
		else
		{
			++it;
		}
	}
}

void List::swap(List &other)
{
	if (this != &other)
	{
		std::swap(this->count, other.count);
		std::swap(this->Head, other.Head);
		std::swap(this->Tail, other.Tail);
		std::swap(this->head, other.head);
		std::swap(this->tail, other.tail);
	}
}

void List::clear(void)
{
	while (!empty())
	{
		pop_front();
	}
}

void List::splice(List &other) throw()
{
	if (!this->empty())
	{
		Node *other_front = other.begin().elem;
		Node *other_back = (--other.end()).elem;
		Node *this_prev = (--this->end()).elem;
		Node *this_next = this->end().elem;
		this_prev->next = other_front;
		other_front->prev = this_prev;
		this_next->prev = other_back;
		other_back->next = this_next;
	}
	else
	{
		Node *other_front = other.begin().elem;
		Node *other_back = (--other.end()).elem;
		Node *this_next = (this->end().elem);
		this_next->prev = other_back;
		other_back->next = this_next;
		Head = other_front;
		head = iterator{ Head };
	}
	other.Head = other.end().elem;
	other.head = iterator{ other.Head };
	this->count += other.count;
	other.count = 0;
}

void List::splice(iterator first, List &other) throw()
{
	if (!this->empty())
	{
		Node *other_front = other.begin().elem;
		Node *other_back = (--other.end()).elem;
		Node *this_prev = first.elem;
		Node *this_next = first.elem->next;
		this_prev->next = other_front;
		other_front->prev = this_prev;
		this_next->prev = other_back;
		other_back->next = this_next;
	}
	else
	{
		Node *other_front = other.begin().elem;
		Node *other_back = (--other.end()).elem;
		Node *this_next = (this->end().elem);
		this_next->prev = other_back;
		other_back->next = this_next;
		Head = other_front;
		head = iterator{ Head };
	}
	other.Head = other.end().elem;
	other.head = iterator{ other.Head };
	this->count += other.count;
	other.count = 0;
}

void List::sort(void)
{
	auto end = this->end();
	for (auto it = this->begin(); it != this->end(); ++it)
	{
		auto tmp_it = it;
		for (auto ot = this->begin(); ot != --end; ++ot)
		{
			if (*it < *ot)
			{
				std::swap(*it, *ot);
			}
		}
	}
}

void List::merge(List &other)
	throw(std::bad_alloc)
{
	for (auto ot = other.cbegin(); ot != other.cend(); ++ot)
	{
		auto it = this->cbegin();
		for (; it != this->cend(); ++it)
		{
			if (*ot < *it)
			{
				break;
			}
		}
		if (it == begin())
		{
			push_front(*ot);
		}
		else
		{
			this->insert(--it, *ot);
		}
	}
}