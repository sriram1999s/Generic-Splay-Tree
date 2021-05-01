#include <iostream>
#include <cassert>
#include <cstddef>
#include "node.hpp"

template<typename T>
class SplayTree
{
	public:
		class iterator;
	private:
		Node<T> *end_;
		Node<T> *root_;
		int size_;
		inline void create_root_(const T& val);
		void _inorder(Node<T> *head);
		void splay(Node<T> *ptr);
		void zig(Node<T> *ptr);
		void zig_zag(Node<T> *ptr);
		void zag_zig(Node<T> *ptr);
		void copy(Node<T> *h1, const Node<T> *h2);
		void _deallocate(Node<T> *node);
		inline Node<T>* _find(Node<T>*, const T&) const;
		SplayTree(const Node<T> *head);
		void debug();
		void inorder();
		T get_root();
	public:
		SplayTree();
		~SplayTree();
		SplayTree(const SplayTree&);
		SplayTree& operator=(const SplayTree&);
		template <typename U> friend SplayTree<U> operator+(const SplayTree<U>& st1, const SplayTree<U>& st2);
		void insert(const T& value);
		void remove(const T& value);  // overload for iterator -> pending
		int size();
		iterator find(const T& elt);
		template <typename U> friend SplayTree<U> join(const SplayTree<U>& st1, const SplayTree<U>& st2);
		template <typename U> friend std::pair<SplayTree<U>, SplayTree<U>> split(const SplayTree<U>& st1, const typename SplayTree<U>::iterator& it);
		template <typename U> friend std::pair<SplayTree<U>, SplayTree<U>> split(const SplayTree<U>& st1, const U& elt);

		class iterator
		{
			private:
				Node<T>* p_;
				int front;
				int back;
				// bool reverse;
			public:
				using iterator_category = std::bidirectional_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = T;
				using pointer = T*;
				using reference = T&;

				iterator(Node<T> *p = nullptr, int front = 0, int back = 0) : p_(p), front(front), back(back) { }
				~iterator() {}
				iterator(const iterator& rhs)
				{
					p_ = rhs.p_;
					front = rhs.front;
					back = rhs.back;
					// reverse = rhs.reverse;
				}

				friend bool operator==(const iterator& lhs, const iterator& rhs)
				{
					return (lhs.p_ == rhs.p_ && lhs.front == rhs.front && lhs.back == rhs.back);
				}

				friend bool operator!=(const iterator& lhs, const iterator& rhs)
				{
					return !(lhs==rhs);
				}

				iterator& operator=(const iterator& rhs)
				{
					if (this != &rhs) {
						p_ = rhs.p_;
						front = rhs.front;
						back = rhs.back;
						// reverse = rhs.reverse;
					}
					return *this;
				}

				T& operator*() const
				{
					return p_->value;
				}

				iterator& operator++()
				{
					if (p_->end || front > 0) {
						++front;
					}
					else if (back > 0) {
						--back;
					}
					else {
						if(p_->right)
						{
							p_ = p_->right;
							while(p_->left) p_ = p_->left;
						}
						else
						{
							while(p_->parent && !p_->parent->end && !(p_->parent->value > p_->value)) p_ = p_->parent;
							p_ = p_->parent;
						}
					}
					return *this;
				}

				iterator operator++(int)
				{
					iterator temp(*this);
					++*this;
					return temp;
				}

				iterator& operator--()
				{
					if(front > 0)
					{
						--front;
					}
					else if (back > 0) {
						++back;
					}
					else
					{
						if(p_->left)
						{
							p_ = p_->left;
							while(p_->right) p_ = p_->right;
						}
						else
						{
							Node<T> *copy = p_;
							while (copy->parent && copy->parent->left == copy) {
								copy = copy->parent;
							}
							if (!copy->end) {
								while(p_->parent && !p_->parent->end && (p_->parent->value > p_->value)) p_ = p_->parent;
								p_ = p_->parent;
							} else {
								back = 1;
							}
						}
					}
					return *this;
				}

				iterator operator--(int)
				{
					iterator temp(*this);
					--*this;
					return temp;
				}
				// template <typename U> friend void SplayTree<U>::splay(Node<U>*);
		};
		iterator begin() const;
		iterator end() const;
};

// debug func

template <typename T>
void SplayTree<T>::debug() {}

/* -------------- Iterator friend functions -------------------- */
/* -------------- Iterator friend functions end ---------------- */


/* -------------- SplayTree iterator functions ----------------- */

template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::begin() const
{
	if(!root_)
	{
		return iterator(end_);
	}
	Node<T> *trav = root_;
	while(trav->left)
	{
		trav = trav->left;
	}
	return iterator(trav);
}

template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::end() const
{
	return iterator(end_);
}

/* -------------- SplayTree iterator functions ends ------------ */

/* -------------- SplayTree friend functions ------------------- */

template <typename T>
SplayTree<T> join(const SplayTree<T>& st1, const SplayTree<T>& st2)
{
	if (!st1.root_ && !st2.root_) {
		return SplayTree<T>();
	}

	if (!st1.root_) return SplayTree<T>(st2);
	if (!st2.root_) return SplayTree<T>(st1);

	// Node<T> *rightmost_st1 = st1.root_;
	// while (rightmost_st1->right) {
	// 	rightmost_st1 = rightmost_st1->right;
	// }

	SplayTree<T> combined(st1);

	Node<T> *rightmost_combined = combined.root_;
	while (rightmost_combined->right) {
		rightmost_combined = rightmost_combined->right;
	}

	Node<T> *leftmost_st2 = st2.root_;
	while (leftmost_st2->left) {
		leftmost_st2 = leftmost_st2->left;
	}

	// if (!(rightmost_st1->value < leftmost_st2->value)) {
	// 	return SplayTree<T>();
	// }

	if (!(rightmost_combined->value < leftmost_st2->value)) {
		return SplayTree<T>();
	}

	SplayTree<T> temp(st2);

	combined.splay(rightmost_combined);

	assert (combined.root_->right == nullptr &&
			combined.end_->left == combined.root_);

	combined.root_->right = new Node<T>(temp.root_->value);
	combined.root_->right->parent = combined.root_;
	++combined.size_;
	combined.copy(combined.root_->right, temp.root_);

	return combined;
}

template <typename T>
std::pair<SplayTree<T>, SplayTree<T>> split(const SplayTree<T>& st1, const typename SplayTree<T>::iterator& it)
{
	if (!st1.root_) return std::pair<SplayTree<T>, SplayTree<T>>();

	SplayTree<T> temp(st1);

	if (it == st1.end()) {
		return std::pair<SplayTree<T>, SplayTree<T>>({temp, SplayTree<T>()});
	}

	Node<T> *elt_ptr = temp._find(temp.root_, *it);

	if (elt_ptr) {
		temp.splay(elt_ptr);
		SplayTree<T> right_sub(temp.root_->right);
		temp._deallocate(temp.root_->right);
		temp.root_->right = nullptr;
		return std::pair<SplayTree<T>, SplayTree<T>>({temp, right_sub});
	} else {
		return std::pair<SplayTree<T>, SplayTree<T>>({temp, SplayTree<T>()});
	}
}


template <typename T>
std::pair<SplayTree<T>, SplayTree<T>> split(const SplayTree<T>& st1, const T& elt)
{
	if (!st1.root_) return std::pair<SplayTree<T>, SplayTree<T>>();

	SplayTree<T> temp(st1);
	Node<T> *elt_ptr = temp._find(temp.root_, elt);

	if (elt_ptr && !elt_ptr->end) {
		temp.splay(elt_ptr);
		SplayTree<T> right_sub(temp.root_->right);
		temp._deallocate(temp.root_->right);
		temp.root_->right = nullptr;
		return std::pair<SplayTree<T>, SplayTree<T>>({temp, right_sub});
	} else {
		return std::pair<SplayTree<T>, SplayTree<T>>({temp, SplayTree<T>()});
	}
}

template <typename T>
SplayTree<T> operator+(const SplayTree<T>& st1, const SplayTree<T>& st2)
{
	return join(st1, st2);
}

/* -------------- SplayTree friend functions end --------------- */


/* -------------- SplayTree member function -------------------- */

template <typename T>
inline void SplayTree<T>::create_root_(const T& val)
{
	root_ = new Node<T>(val);
	end_->left = root_;
	root_->parent = end_;
	++size_;
}

template <typename T>
T SplayTree<T>::get_root()
{
	if (!root_) return T();
	return root_->value;
}

template <typename T>
int SplayTree<T>::size()
{
	return size_;
}

template<typename T>
SplayTree<T>::SplayTree() : end_(new Node<T>(T(), true)), root_(nullptr), size_(0) {}

template <typename T>
SplayTree<T>::SplayTree(const SplayTree& rhs) : end_(new Node<T>(T(), true)), root_(nullptr), size_(0)
{
	if (rhs.root_) {
		create_root_(rhs.root_->value);
		copy(root_, rhs.root_);
	}
}

template <typename T>
SplayTree<T>::SplayTree(const Node<T> *head) : end_(new Node<T>(T(), true)), root_(nullptr), size_(0)
{
	if (head) {
		create_root_(head->value);
		copy(root_, head);
	}
}

template <typename T>
SplayTree<T>& SplayTree<T>::operator=(const SplayTree& rhs)
{
	// check for self assignment pending
	if (this != &rhs) {
		_deallocate(end_);

		end_ = new Node<T>(T(), true);
		size_ = 0;

		if (rhs.root_) {
			create_root_(rhs.root_->value);
			copy(root_, rhs.root_);
		}
	}
	return *this;
}

template <typename T>
void SplayTree<T>::copy(Node<T> *h1, const Node<T> *h2)
{
	if (h2->left) {
		h1->left = new Node<T>(h2->left->value);
		h1->left->parent = h1;
		++size_;
		copy(h1->left, h2->left);
	}

	if (h2->right) {
		h1->right = new Node<T>(h2->right->value);
		h1->right->parent = h1;
		++size_;
		copy(h1->right, h2->right);
	}
}

template <typename T>
void SplayTree<T>::remove(const T& value)
{
	Node<T> *elt_ptr = _find(root_, value);

	if (!elt_ptr) {
		return;
	}

	splay(elt_ptr);

	assert(root_ == elt_ptr);

	SplayTree<T> left_sub(root_->left);
	SplayTree<T> right_sub(root_->right);

	--size_;

	*this = join(left_sub, right_sub);
}

template<typename T>
void SplayTree<T>::insert(const T& value)
{
	if(!root_)
	{
		create_root_(value);
		return;
	}

	Node<T> *trav = root_;
	Node<T> *prev = nullptr;

	while(trav != nullptr)
	{
		prev = trav;
		if(trav->value > value)
		{
			trav = trav->left;
		}
		else
		{
			trav = trav->right;
		}
	}

	if (prev->value != value)
	{
		Node<T> *temp = new Node<T>(value);
		if(prev->value > value)
		{
			prev->left = temp;
		}
		else
		{
			prev->right = temp;
		}

		temp->parent = prev;
		++size_;

		splay(temp);
	} else {
		splay(prev);
	}
}

template<typename T>
void SplayTree<T>::_inorder(Node<T>* head)
{
	if(!head) return;

	_inorder(head->left);
	std::cout << head->value << ' ';
	_inorder(head->right);
}

template <typename T>
void SplayTree<T>::inorder()
{
	_inorder(root_);
	std::cout << '\n';
}

template <typename T>
void SplayTree<T>::zig(Node<T> *ptr)
{
	Node<T> *parent = ptr->parent;

	assert(parent != end_);

	if (parent->left == ptr) {
		Node<T> *rptr = ptr->right;
		ptr->right = parent;
		ptr->parent = parent->parent;
		parent->parent = ptr;
		parent->left = rptr;
		if (rptr) rptr->parent = parent;
	} else {
		Node<T> *lptr = ptr->left;
		ptr->left = parent;
		ptr->parent = parent->parent;
		parent->right = lptr;
		parent->parent = ptr;
		if (lptr) lptr->parent = parent;
	}

	root_ = ptr;
	end_->left = root_;
}

template <typename T>
void SplayTree<T>::zig_zag(Node<T> *child)
{
	Node<T> *gp = child->parent->parent;
	Node<T>* parent = child->parent;

	assert(gp != end_ && parent != end_);

	Node<T> *rchild = child->right;
	Node<T> *lchild = child->left;

	child->parent = gp->parent;

	parent->right = lchild;
	if (lchild) lchild->parent = parent;
	child->left = parent;
	parent->parent = child;

	gp->left = rchild;
	if (rchild) rchild->parent = gp;
	child->right = gp;
	gp->parent = child;

	root_ = child;
	end_->left = root_;
}

template <typename T>
void SplayTree<T>::zag_zig(Node<T> *child)
{
	Node<T> *gp = child->parent->parent;
	Node<T>* parent = child->parent;

	assert(gp != end_ && parent != end_);

	Node<T> *rchild = child->right;
	Node<T> *lchild = child->left;

	child->parent = gp->parent;

	parent->left = rchild;
	if (rchild) rchild->parent = parent;
	child->right = parent;
	parent->parent = child;

	gp->right = lchild;
	if (lchild) lchild->parent = gp;
	child->left = gp;
	gp->parent = child;

	root_ = child;
	end_->left = root_;
}

template <typename T>
void SplayTree<T>::splay(Node<T> *ptr)
{
	if (ptr == root_) return;

	Node<T> *parent = root_;
	Node<T> *child = nullptr;

	if (parent->value > ptr->value) {
		child = parent->left;
		if (child == ptr) {
			zig(child);
		} else {
			if (child->value > ptr->value) {
				zig(child);
			} else {
				zig_zag(child->right);
			}
		}
	} else {
		child = parent->right;
		if (child == ptr) {
			zig(child);
		} else {
			if (child->value > ptr->value) {
				zag_zig(child->left);
			} else {
				zig(child);
			}
		}
	}
	splay(ptr);
}

template <typename T>
inline Node<T>* SplayTree<T>::_find(Node<T>* ptr, const T& elt) const
{
	while (ptr && ptr->value != elt) {
		if (ptr->value > elt) {
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}

	return ptr;
}

template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::find(const T& elt)
{
	Node<T> *h = _find(root_, elt);

	// return iterator instead of the below code
	if (h) {
		splay(h);
		assert(h == root_ && h == end_->left);
		return iterator(h);
	}
	return iterator(end_);
}

template <typename T>
void SplayTree<T>::_deallocate(Node<T> *node)
{
	if (!node) return;

	_deallocate(node->left);
	_deallocate(node->right);

	delete node;
}

template <typename T>
SplayTree<T>::~SplayTree()
{
	_deallocate(end_);
}

/* -------------- SplayTree member function end ---------------- */
