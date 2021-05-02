# Splay Tree

## Functionalities

- [Insertion](#Insertion)
- [Removal](#Removal)
- [Joining](#Joining)
- [Splitting](#Splitting)
- [Finding](#Finding)

- <font size="5"> [Iterators](#Iterators) </font>

	- Bidirectional
	- Supported: ```++```, ```--```, ```==```,```!=```,```=```,```*``` (lvalue and rvalue dereference)
	- All std algorithms that work for bidirectional iterators

## Requirements On User Defined Data Type

- Operator ```==```
- Operator ```!=```
- Operator ```<```
- Operator ```<<```

# Usage of Splay Tree

## Inclusion

```c++
#include "splay_tree.hpp"
```

## Declaration

```c++
SplayTree<int> st1;
SplayTree<float> st2;
```
## Insertion

```c++
st1.insert(1);
st2.insert(1.5);
```

## Removal
```c++
st1.remove(1);
st2.remove(1.5);
```

## Joining
> Joining of two splay trees can take place only when the largest element is smaller than the smallest element in the second tree

```c++
// assume two trees of type SplayTree<float> name st1 and st2
SplayTree<float> joined = join(st1, st2);
```
OR
```c++
SplayTree<float> joined = st1 + st2;
```

## Splitting
```c++
// obtaining iterator of element by which to split the tree and then splitting
// assume st1 to be of type SplayTree<int>
SplayTree<int>::iterator it = st1.find(1);
std::pair<SplayTree<int>, SplayTree<int>> st = split(st1, it);
```
OR
```c++
// splitting based on value
std::pair<SplayTree<int>, SplayTree<int>> st = split(st1, 1);
```
```c++
// st.first now provides all elements occurring before it
// st.second now provides all elements occurring after it
// st1 remains unchanged
```

## Finding
```c++
// assume st1 of type SplayTree<int>
SplayTree<int>::iterator it = st1.find(1);
```
OR
```c++
SplayTree<int>::iterator it = std::find(st1.begin(), st1.end(), 1);
```

## Iterators
```c++
// assume st1 of type SplayTree<int>
SplayTree<int>::iterator it = st1.begin();
SplayTree<int>::iterator it2 = st1.end();
```
OR
```c++
SplayTree<int>::iterator it = std::begin(st1);
SplayTree<int>::iterator it2 = std::end(st1);
```
