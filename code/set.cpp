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
	for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
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

Set::const_iterator Set::cbegin(void) const
{
	return this->data.cbegin();
}

Set::const_iterator Set::cend(void) const
{
	return this->data.cend();
}

void Set::insert(const Set::value_type &item)
{
	if (!this->isContain(item))
	{
		auto it = this->begin();
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
	return (this->cend() != data.find(item));
}

bool Set::isContain(const Set &other) const
{
	for (auto ot = other.cbegin(); ot != other.cend(); ++ot)
	{
		if (!this->isContain(*ot))
		{
			return false;
		}
	}
	return true;
}

Set::size_type Set::size(void) const
{
	return this->data.length();
}

Set association(const Set &lhs, const Set &rhs)
{
	Set res{ lhs };
	for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
	{
		res.insert(*it);
	}
	return res;
}

Set intersection(const Set &lhs, const Set &rhs)
{
	Set res{};
	for (auto it = lhs.cbegin(); it != lhs.cend(); ++it)
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
	for (auto it = lhs.cbegin(); it != lhs.cend(); ++it)
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