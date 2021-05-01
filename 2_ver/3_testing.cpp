#include <iostream>
#include <algorithm>
#include "splay_tree.hpp"

using namespace std;

template <typename T>
void disp(T first, T last)
{
	while(first != last)
	{
		cout << *first << '\t';
		++first;
	}
	cout << '\n';
}

template <typename T>
void test(SplayTree<T> st)
{
	cout << "inorder: "; disp(st.begin(), st.end());
	cout << "size: " << st.size() << "\n";
	// cout << "root: " << st.get_root() << '\n';
}

int main()
{
	cout << boolalpha;

	SplayTree<int> st2;
	SplayTree<int> st1;

	st2.insert(4);
	st2.insert(7);
	st2.insert(7);
	st2.insert(2);

	st2.debug();

	st1.insert(26);
	st1.insert(11);
	st1.insert(1);

	st1.debug();

	// return 0;
	test(st2);
	test(st1);

	// SplayTree<int> joined = st1 + st2;
	//
	// test(joined);
}
