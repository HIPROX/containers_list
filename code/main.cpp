#include "set.h"
#include <iostream>
#include <iomanip>

int main(void)
{
	std::cout << "\tTest Set" << std::endl;

	Set s{};
	s.insert(5);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.erase(3);

	Set s2{};

	s2.insert(5);
	s2.insert(4);

	std::cout << " s: " << s << std::endl;
	std::cout << "s2: " << s2 << std::endl;
	std::cout << std::endl;
	std::cout << "s.empty(): " << std::boolalpha << s.empty() << std::endl;
	std::cout << "s2.empty(): " << s2.empty() << std::endl;
	std::cout << "s.isContain(s2): " << s.isContain(s2) << std::endl;
	std::cout << " s.size(): " << s.size() << std::endl;
	std::cout << "s2.size(): " << s2.size() << std::endl;
	std::cout << std::endl;
	Set s3 = intersection(s, s2);
	std::cout << "Intersection(s, s2): " << s3 << std::endl;
	s3 = association(s, s2);
	std::cout << "Association(s, s2): " << s3 << std::endl;
	s3 = difference(s, s2);
	std::cout << "Differense(s, s2): " << s3 << std::endl;

	
	std::cout << std::endl << "\t Test List" << std::endl;
	
	List a{}, b{};
	for (unsigned i{}; i < 10; ++i)
	{
		a.push_back(i);
		b.push_front(i * i);
	}
	
	std::cout << "a: ";
	for (List::iterator it = a.begin(); it != a.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	
	std::cout << "b: ";
	for (List::iterator it = b.begin(); it != b.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl << std::endl;

	List::iterator it = a.begin();
	for (unsigned i{ 1 }; i < 4; ++i, ++it);

	a.splice(it, b);
	std::cout << "Method List::splice complete!" << std::endl << std::endl;

	std::cout << "a: ";
	for (List::iterator it = a.begin(); it != a.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\na.length(): " << a.length()
		<< "\ta.empty(): " << a.empty() << std::endl << std::endl;
	
	std::cout << "b: ";
	for (List::iterator it = b.begin(); it != b.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nb.length(): " << b.length()
		<< "\tb.empty(): " << b.empty() << std::endl << std::endl;

	if (!b.empty())
	{
		throw;
	}

	std::cin.clear();
	while (std::cin.get() != '\n');
	std::cin.get();
}