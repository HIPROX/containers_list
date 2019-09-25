#include "set.h"

Set::Set(void) = default;

Set::Set(iterator begin, iterator end)
	throw(std::bad_alloc)
	: data{ begin, end } {};

Set::Set(const Set &other)
	throw(std::bad_alloc)
	: data{ other.data } {};

Set::~Set(void) throw() = default;

Set& Set::operator=(const Set&) = default;

std::ostream& operator<<(std::ostream &os, const Set &rhs)
{
	for (List::iterator it = rhs.begin(); it != rhs.end(); ++it)
	{
		os << *it << ' ';
	}
	return os;
}

Set::iterator Set::begin(void)
{
	return this->data.begin();
}

Set::iterator Set::end(void)
{
	return this->data.end();
}

Set::iterator Set::begin(void) const
{
	return this->data.begin();
}

Set::iterator Set::end(void) const
{
	return this->data.end();
}

void Set::insert(const Set::value_type &item)
{
	if (!this->isContain(item))
	{
		iterator it = this->begin();
		for (; it != this->end(); ++it)
		{
			if (item < *it)
			{
				break;
			}
		}
		if (it == this->begin())
		{
			this->data.push_front(item);
		}
		else
		{
			this->data.insert(--it, item);
		}
	}
}

void Set::erase(const Set::value_type &item)
{
	this->data.remove(item);
}

bool Set::isContain(const Set::value_type &item) const
{
	return (this->end() != data.find(item));
}

bool Set::isContain(const Set &other) const
{
	for (iterator ot = other.begin(); ot != other.end(); ++ot)
	{
		if (!this->isContain(*ot))
		{
			return false;
		}
	}
	return true;
}

Set::UINT Set::size(void) const
{
	return this->data.length();
}

Set association(const Set &lhs, const Set &rhs)
{
	Set res{ lhs };
	for (List::iterator it = rhs.begin(); it != rhs.end(); ++it)
	{
		res.insert(*it);
	}
	return res;
}

Set intersection(const Set &lhs, const Set &rhs)
{
	Set res{};
	for (List::iterator it = lhs.begin(); it != lhs.end(); ++it)
	{
		if (rhs.isContain(*it))
		{
			res.insert(*it);
		}
	}
	return res;
}

Set difference(const Set &lhs, const Set &rhs)
{
	Set res{};
	for (List::iterator it = lhs.begin(); it != lhs.end(); ++it)
	{
		if (!rhs.isContain(*it))
		{
			res.insert(*it);
		}
	}
	return res;
}

bool Set::empty(void) const
{
	return data.empty();
}