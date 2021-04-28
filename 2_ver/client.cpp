#include <iostream>
#include "splay_tree.hpp"

using namespace std;

int main()
{
	SplayTree<int> st;
	st.insert(2);
	st.insert(4);
	st.insert(3);
	st.insert(5);
	st.insert(6);
	st.insert(1);

	SplayTree<int> st2;
	st2.insert(10);
	st2.insert(11);
	st2.insert(12);
	st2.insert(13);
	st2.insert(14);

	st.inorder();
	st2.inorder();
	cout << "root: " << st.get_root() << '\n';
	cout << "root2: " << st2.get_root() << '\n';


	// SplayTree<int> comb;
	SplayTree<int> comb = join(st, st2);
	// // comb = join(st, st2);
	comb.inorder();
	cout << "root comb: " << comb.get_root() << '\n';

	comb.remove(12);
	comb.inorder();
	cout << "root comb new: " << comb.get_root() << '\n';

	comb.find(12);
	comb.find(13);

	SplayTree<float> st_float;
	st_float.insert(2.1);
	st_float.insert(3.1);
	st_float.insert(4.1);
	st_float.insert(5.1);
	st_float.insert(6.1);
	st_float.insert(1.1);

	st_float.inorder();
}
