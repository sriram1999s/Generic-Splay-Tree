#include<iostream>
#include <algorithm>
using namespace std;
#include "rect.hpp"
#include "../splay_tree.hpp"

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
	SplayTree<Rect> st1;

	Rect r1(2, 4);
	Rect r2(3, 11);
	Rect r3(8, 1);
	Rect r4(4, 2);
	Rect r5(6, 9);

	st1.insert(r1);
	st1.insert(r2);
	st1.insert(r3);
	st1.insert(r4);
	st1.insert(r5);

	cout << "---------- ST1 ---------- \n";
	test(st1);

	auto it = find(begin(st1), end(st1), Rect(4, 2));

	cout << *it << '\n';

	SplayTree<Rect> st2;

	st2.insert(Rect(0, 1));
	st2.insert(Rect(1, 1));
	st2.insert(Rect(2, 1));

	cout << "---------- ST2 ---------- \n";
	test(st2);

	SplayTree<Rect> joined = st1 + st2;

	cout << "---------- JOINED ---------- \n";
	test(joined);

	joined = st2 + st1;

	cout << "---------- JOINED ---------- \n";
	test(joined);

	auto s = split(joined, Rect(1, 8));

	test(s.first);
	test(s.second);
}
