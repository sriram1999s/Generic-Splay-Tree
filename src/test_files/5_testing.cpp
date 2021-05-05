#include <iostream>
#include "../splay_tree.hpp"

using namespace std;

#include<algorithm>


template <typename T>
void disp(T first, T last)
{
	while(first != last)
	{
		cout << *first << ' ';
		++first;
	}
	cout << '\n';
}

template <typename T>
void test(SplayTree<T> st)
{
	cout << "disp: "; disp(st.begin(), st.end());
	cout << "size: " << st.size() << "\n";
	cout << "root: " << st.get_root() << '\n';
}

int main()
{
	SplayTree<int> st1;
	st1.insert(5);
	st1.insert(3);
	st1.insert(4);

	cout << "ST1: \n";
	test(st1);
	cout << '\n';

	SplayTree<int> st2;
	st2.insert(1);
	st2.insert(0);
	st2.insert(2);

	cout << "ST2: \n";
	test(st2);
	cout << '\n';

	auto joined = st2 + st1;

	cout << "joined: \n";
	test(joined);
	cout << '\n';

	// joined = st1 + st2;
	// joined = st2 + st1;

	// test(joined);

	// joined = SplayTree<int>();
	cout << '\n';
	cout << "std::min_elt: " << *min_element(joined.begin(), joined.end()) << '\n';
	test(joined);

	cout << '\n';
	cout << "std::max_elt: " << *max_element(joined.begin(), joined.end()) << '\n';
	test(joined);

	cout << '\n';
	cout << "min_elt: " << *joined.min_element() << '\n';
	test(joined);

	cout << '\n';
	cout << "max_elt: " << *joined.max_element() << '\n';
	test(joined);




	cout << '\n';
	SplayTree<int> max_tree = max(st1, st2);
	test(max_tree);
	cout << '\n';
	SplayTree<int> min_tree = min(st1, st2);
	test(min_tree);
	cout << '\n';
	max_tree = std::max(st1, st2);
	test(max_tree);
	cout << '\n';
	min_tree = std::min(st1, st2);
	test(min_tree);
}
