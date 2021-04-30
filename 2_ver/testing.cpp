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
	cout << "disp: "; disp(st.begin(), st.end());
	cout << "size: " << st.size() << "\t\n";
	// cout << "root: " << st.get_root() << '\n';
}

int main()
{
	cout << boolalpha;

	SplayTree<float> st2;
	SplayTree<float> st1;

	st2.insert(-1.10);
	st2.insert(-9.1);
	st2.insert(-5.1);
	st2.insert(-6.1);

	// test(st2);

	st1.insert(-0.1);
	st1.insert(-0.4);
	st1.insert(-0.2);
	st1.insert(-0.3);

	// test(st1);

	auto joined = st1 + st2;

	test(joined);

	joined = join(st2, st1);

	// test(joined);

	auto beg = joined.begin();
	auto end = joined.end();
	joined.insert(0.0);

	// cout << "beg: " << *beg << '\n';
	// cout << "end: " << *end << '\n';

	SplayTree<float> st_empty;

	test(joined);

	// auto it = joined.find(0.3);
	auto it = find(joined.begin(), joined.end(), (float)-0.3);
	// cout << "count: " << count(joined.begin(), joined.end(), (float)0.3) << '\n';
	// auto it = begin(joined);
	// auto it2 = joined.find(0.4);
	//
	float a = *it;

	cout << "*it: " << *it << '\n';

	test(joined);

	auto st = split(joined, it);
	//
	test(st.first);
	test(st.second);

	SplayTree<char> char_st;

	// disp(st.first.begin(), st.first.end());
	// disp(st.second.begin(), st.second.end());
}
