#include <iostream>
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
	cout << "disp: "; disp(st.begin(), st.end());
	cout << "size: " << st.size() << "\n";
}

int main()
{
	SplayTree<int> st1;
	st1.insert(5);
	st1.insert(3);
	st1.insert(4);

	cout << "ST1: \n";
	test(st1);

	SplayTree<int> st2 = st1;

	cout << "ST2: \n";
	test(st2);

	if (st1 == st2) {
		cout << "st1 is equal to st2\n";
	} else {
		cout << "negative\n";
	}
}
