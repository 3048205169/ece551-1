  
#include "bstmap.h"
#include <string>
#include <sstream>
#include <iostream>

class TestBstMap : public BstMap<int, int> {
	/*
	void dumpNode(const Node *n, std::ostream &os) const
	{
		os << '(';
		if (n != NULL) {
			os << n->key << ':' << n->value;
			dumpNode(n->left, os);
			dumpNode(n->right, os);
		}
		os << ')';
	}
	*/
	/*
public:
	friend std::ostream& operator<< (std::ostream &, const TestBstMap&);
	*/
};
/*
std::ostream& operator<< (std::ostream &os, const TestBstMap &m)
{
	m.dumpNode(m.root, os);
	return os;
}
*/
int main()
{
	TestBstMap m;
	static int seq[] = {
		3, 9, 2, 6, 3,
		-1/*, 8, 9, 7, 9, -1, 2, 3, 8, 4,
		6, 2, 6, 4, 3, 3, 8, 3, 2, 7,
		9, 5, 0, 2, 8, 8, 4, 1, 9, 7,
		1, 6, 9,
	-1*/};
	int has[10] = {0};
	int n;
	for (int i = 0; (n = seq[i]) != -1; i++) {
		std::stringstream ss;
		ss << n;
		if (has[n]) {
			std::cout << "remove: " << seq[i] << std::endl;
			m.remove(seq[i]);
		} else {
			std::cout << "add : " << seq[i] << " " << i << std::endl;
			m.add(seq[i], i);
		}
		has[n] = !has[n];
		std::cout << ss.str() << std::endl;
		//std::cout << m << std::endl;
	}
	/*
	try {
		std::cout << m.lookup("guess what?");
	} catch (const std::invalid_argument &e) {
		std::cout << "yeah, " << e.what() << "...\n";
	}
	{
		TestBstMap *evilCopy = new TestBstMap(m);
		Map<std::string, int> *p = evilCopy;

		std::cout << (*evilCopy = *evilCopy) << std::endl;
		delete p;
	}
	*/
	return 0;
}
