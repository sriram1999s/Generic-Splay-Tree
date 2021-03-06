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
void rdisp(T last, T first)
{
	while(last != first)
	{
		cout << *last << '\t';
		--last;
	}
	cout << '\n';
}
int main()
{
	SplayTree<int> st;
	st.insert(2);
	st.insert(4);
	// st.insert(3);
	// st.insert(5);
	// st.insert(6);
	// st.insert(1);

	cout << "SIZE st: " << st.size() << endl;

	SplayTree<int> st2;
	st2.insert(10);
	st2.insert(11);
	// st2.insert(12);
	// st2.insert(13);
	// st2.insert(14);

	cout << "st1: "; st.inorder();
	cout << "st2: "; st2.inorder();
	// cout << "root: " << st.get_root() << '\n';
	// cout << "root2: " << st2.get_root() << '\n';

	// SplayTree<int> comb;
	// cout << "h1\n";
	SplayTree<int> comb = join(st, st2);
	// cout << "h2\n";

	// comb.debug();

	// // comb = join(st, st2);
	cout << "comb: "; comb.inorder();
	cout << "root of comb: " << comb.get_root() << '\n';

	cout << "SIZE comb: " << comb.size() << '\n';

	comb.remove(2);

	cout << "comb: "; comb.inorder();
	cout << "SIZE comb after removal: " << comb.size() << '\n';

	cout << "new root of comb: " << comb.get_root() << '\n';

	// comb.find(12);
	// comb.find(13);

	// SplayTree<float> st_float;
	// st_float.insert(2.1);
	// st_float.insert(3.1);
	// st_float.insert(4.1);
	// st_float.insert(5.1);
	// st_float.insert(6.1);
	// st_float.insert(1.1);
	//
	// st_float.inorder();
	//
	// SplayTree<int>::iterator it = st.begin();
	//
	// cout << "*it : " << *it << '\n';
	//
	// cout << "*(it + 3) : " << *(it) << '\n';
	//
	// SplayTree<int>::iterator it2(it);
	//
	// cout << "*it2 : " << *it2 << '\n';
	//
	// auto yt = st.find(5);
	//
	// disp(st.begin(), ++yt);
	//
	// disp(st_float.begin(), st_float.end());
	//
	// SplayTree<int> s;
	// s.insert(1); s.insert(3); s.insert(2);
	//
	// auto test = s.end();
	//
	// disp(s.begin(), s.end());
	// // s.debug();
	//
	// rdisp(--s.end(), --s.begin());

	// cout << "front: " << test.front << '\n';
	// cout << "back: " << test.back << '\n';
	//
	// auto test2 = s.begin();
	// --test2;
	// ++test2;
	// ++test2;
	//
	// cout << "front2: " << test2.front << '\n';
	// cout << "back2: " << test2.back << '\n';
	//
	// rdisp(--s.end(), --s.begin());
}
