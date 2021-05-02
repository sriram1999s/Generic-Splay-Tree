#include <iostream>
#include <algorithm>
#include "../splay_tree.hpp"

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

	st2.insert(-1);
	st2.insert(-2);
	st2.insert(-4);
	st2.insert(-3);

	st1.insert(-8);
	st1.insert(-5);
	st1.insert(-16);

	test(st2);
	test(st1);

	SplayTree<int> joined = st1 + st2;

	test(joined);
}
