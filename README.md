# Splay Tree

## Functionalities

- Insertion
- Removal
- Joining
- Splitting
- Finding

- ## Iterator

	- Bidirectional
	- Supported: ```++```, ```--```, ```==```,```!=```,```=```,```*``` (lvalue and rvalue dereference)
	- All std algorithms that work for bidirectional iterators

# Usage of Splay Tree

## Inclusion

```cpp
#include "splay_tree.hpp"
```

## Declaration

```cpp
SplayTree<int> st1;
SplayTree<float> st2;
```
## Insertion

```cpp
st1.insert(1);
st2.insert(1.5);
```

## Removal
```cpp
st1.remove(1);
st2.remove(1.5);
```

## Joining
```cpp
// assume two trees of type SplayTree<float> name st1 and st2
SplayTree<float> joined = join(st1, st2);
```
OR
```cpp
SplayTree<float> joined = st1 + st2;
```

## Splitting
```cpp
// obtaining iterator of element by which to split the tree (assume st1 is of type SplayTree<int>)
SplayTree<int>::iterator it = st1.find(1);

// splitting
std::pair<SplayTree<int>, SplayTree<int>> st = split(st1, it);

// st.first now provides all elements occurring before it
// st.second now provides all elements occurring after it
// st1 remains unchanged
```

## Finding
```cpp
// assume st1 of type SplayTree<int>
SplayTree<int>::iterator it = st1.find(1);
```
OR
```cpp
SplayTree<int>::iterator it = std::find(st1.begin(), st1.end(), 1);
```

## Iterators
```cpp
// assume st1 of type SplayTree<int>
SplayTree<int>::iterator it = st1.begin();
SplayTree<int>::iterator it2 = st1.end();
```
OR
```cpp
SplayTree<int>::iterator it = std::begin(st1);
SplayTree<int>::iterator it2 = std::end(st1);
```
