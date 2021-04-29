#include <iostream>
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
	cout << "inorder: "; st.inorder();
	cout << "size: " << st.size() << "\t\t";
	cout << "root: " << st.get_root() << '\n';
}

int main()
{
	cout << boolalpha;

	SplayTree<float> st2;
	SplayTree<float> st1;

	st2.insert(1.10);
	st2.insert(9.1);
	st2.insert(5.1);
	st2.insert(6.1);

	test(st2);

	st1.insert(0.1);
	st1.insert(0.4);
	st1.insert(0.2);
	st1.insert(0.3);

	test(st1);

	auto joined = st1 + st2;

	test(joined);

	auto beg = joined.begin();
	auto end = joined.end();

	cout << "beg: " << *beg << '\n';
	cout << "end: " << *end << '\n';
}
