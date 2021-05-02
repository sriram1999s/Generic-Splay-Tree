#include<iostream>
using namespace std;
#include "rect.hpp"
#include "splay_tree.hpp"

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
  SplayTree<Rect> st_rect;

  Rect r1(2, 4);
  Rect r2(3, 11);
  Rect r3(8, 1);
  Rect r4(4, 2);
  Rect r5(6, 9);

  st_rect.insert(r1);
  st_rect.insert(r2);
  st_rect.insert(r3);
  st_rect.insert(r4);
  st_rect.insert(r5);

  test(st_rect);
}
