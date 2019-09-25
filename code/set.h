#pragma once
#include "list.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

class Set
{
public:
// Typedefs
	typedef unsigned UINT;
	typedef List::value_type value_type;
	typedef List::iterator iterator;
// Constructors & Destructor
	Set(void);
	Set(iterator, iterator) throw(std::bad_alloc);
	Set(const Set&) throw(std::bad_alloc);
	~Set(void) throw();
// Operators
	Set& operator=(const Set&);
	friend std::ostream& operator<<(std::ostream&, const Set&);
// Methods
	bool empty(void) const;
	void insert(const value_type&);
	UINT size(void) const;
	void erase(const value_type &item);
	bool isContain(const value_type&) const;
	bool isContain(const Set&) const;
// Iterators
	iterator begin(void);
	iterator end(void);
	iterator begin(void) const;
	iterator end(void) const;
// Friends
	friend Set association(const Set&, const Set&);
	friend Set intersection(const Set&, const Set&);
	friend Set difference(const Set&, const Set&);
private:
	List data;
};