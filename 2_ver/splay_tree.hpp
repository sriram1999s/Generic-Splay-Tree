#include<iostream>
#include <cassert>
#include "node.hpp"

using namespace std;

template<typename T>
class SplayTree
{
	public:
		class iterator;
	private:
		Node<T> *end_;
		Node<T> *root_;
		int size_;
		inline void set_root_(const T& val);
		void _inorder(Node<T> *head);
		void splay(Node<T> *ptr);
		void zig(Node<T> *parent, Node<T> *ptr);
		void zig(Node<T> *ptr);
		void zig_zag(Node<T> *gp, Node<T> *parent, Node<T> *ptr);
		void zig_zag(Node<T> *ptr);
		void zag_zig(Node<T> *gp, Node<T> *parent, Node<T> *ptr);
		void zag_zig(Node<T> *ptr);
		void copy(Node<T> *h1, const Node<T> *h2);
		void _deallocate(Node<T> *node);
		inline Node<T>* _find(Node<T>*, const T&);
		SplayTree(const Node<T> *head);
	public:
		SplayTree();
		~SplayTree();
		SplayTree(const SplayTree&);
		SplayTree& operator=(const SplayTree&);
		// provide operator functions
		void inorder();
		void insert(const T& value);
		void remove(const T& value);
		iterator find(const T& elt); // return iterator instead
		SplayTree split(const T& elt);
		T get_root()
		{
			if (!root_) return T();
			return root_->value;
		}
		template <typename U>
		friend SplayTree<U> join(const SplayTree<U> &st1, const SplayTree<U> &st2);

		class iterator
		{
			private:
				Node<T>* p_;
			public:
				int front = -1;
				int back = -1;
				iterator(Node<T> *p = nullptr) : p_(p) { }
				~iterator() {}
				iterator(const iterator& rhs)
				{
					p_ = rhs.p_;
				}

				bool operator==(const iterator& rhs)
				{
					return p_ == rhs.p_;
				}
				bool operator!=(const iterator& rhs)
				{
					return !(*this==rhs);
				}
				iterator& operator=(const iterator& rhs)
				{
					p_ = rhs.p_;
					return *this;
				}

				T operator*()
				{
					return p_->value;
				}

				iterator& operator++()
				{
					if (front == -1) {
						if (p_->parent == nullptr) front = 0;
					}
					if (front >= 0) {
						++front;
					}
					else if (back >= 0) {
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
					// if (back == -1) {
					// 	if (p_->left == nullptr && p_->right == nullptr) {
					// 		cout << "here: " << p_->value << endl;
					// 		back = 0;
					// 	}
					// }
					if(front >= 0)
					{
						--front;
					}
					else if (back >= 0) {
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
							while(p_->parent && (p_->parent->value > p_->value)) p_ = p_->parent;
							p_ = p_->parent;
						}
					}
					cout << "back before returning from --: " << back << endl;

					return *this;
				}
		};
		iterator begin();
		iterator end();
};

/* -------------- SplayTree iterator functions ----------------- */

template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::begin()
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
typename SplayTree<T>::iterator SplayTree<T>::end()
{
	return iterator(end_);
}
/* -------------- SplayTree iterator functions ends ------------ */

/* -------------- SplayTree friend functions ------------------- */

template <typename T>
SplayTree<T> join(const SplayTree<T> &st1, const SplayTree<T> &st2)
{
	if (!st1.root_ || !st2.root_) {
		return SplayTree<T>();
	}

	Node<T> *rightmost_st1 = st1.root_;
	while (rightmost_st1->right) {
		rightmost_st1 = rightmost_st1->right;
	}

	Node<T> *leftmost_st2 = st2.root_;
	while (leftmost_st2->left) {
		leftmost_st2 = leftmost_st2->left;
	}

	if (rightmost_st1->value >= leftmost_st2->value) {
		return SplayTree<T>();
	}

	SplayTree<T> combined(st1);
	SplayTree<T> temp(st2);

	Node<T> *rightmost_combined = combined.root_;
	while (rightmost_combined->right) {
		rightmost_combined = rightmost_combined->right;
	}

	combined.splay(rightmost_combined);

	assert (combined.root_->right == nullptr &&
			combined.end_->left == combined.root_);

	combined.root_->right = new Node<T>(temp.root_->value);
	combined.copy(combined.root_->right, temp.root_);

	return combined;
}

/* -------------- SplayTree friend functions end --------------- */


/* -------------- SplayTree member function -------------------- */

template <typename T>
inline void SplayTree<T>::set_root_(const T& val)
{
	root_ = new Node<T>(val);
	end_->left = root_;
	root_->parent = end_;
}

template<typename T>
SplayTree<T>::SplayTree() : end_(new Node<T>(T(), true)), root_(nullptr), size_(0) {}

template <typename T>
SplayTree<T>::SplayTree(const SplayTree& rhs) : end_(new Node<T>(T(), true)), root_(nullptr), size_(0)
{
	if (rhs.root_) {
		set_root_(rhs.end_->value);
		copy(root_, rhs.end_);
	}
}

template <typename T>
SplayTree<T>::SplayTree(const Node<T> *head) : end_(new Node<T>(T(), true)), root_(nullptr), size_(0)
{

	if (head) {
		set_root_(head->value);
		copy(root_, head);
	}
}

template <typename T>
SplayTree<T>& SplayTree<T>::operator=(const SplayTree& rhs)
{
	_deallocate(end_);

	end_ = new Node<T>(T(), true);
	size_ = 0;

	if (rhs.root_) {
		set_root_(rhs.end_->value);
		copy(end_, rhs.end_);
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
	*this = join(left_sub, right_sub);
	--size_;
}

template<typename T>
void SplayTree<T>::insert(const T& value)
{
	// cout << "Node " << value << " being inserted" << '\n';
	if(!root_)
	{
		set_root_(value);
		++size_;
		return;
	}

	Node<T> *temp = new Node<T>(value);

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
}

template<typename T>
void SplayTree<T>::_inorder(Node<T>* head)
{
	if(!head) return;

	_inorder(head->left);
	cout << head->value << ' ';
	_inorder(head->right);
}

template <typename T>
void SplayTree<T>::inorder()
{
	_inorder(root_);
	cout << '\n';
}
/*
template <typename T>
void SplayTree<T>::zig(Node<T> *parent, Node<T> *ptr)
{
	if (parent->left == ptr) {
		Node<T> *rptr = ptr->right;
		ptr->right = parent;
		parent->left = rptr;
	} else {
		Node<T> *lptr = ptr->left;
		ptr->left = parent;
		parent->right = lptr;
	}

	end_->left = ptr;
}
*/
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
/*
template <typename T>
void SplayTree<T>::zig_zag(Node<T> *gp, Node<T> *parent, Node<T> *child)
{
	Node<T> *rchild = child->right;
	Node<T> *lchild = child->left;

	parent->right = lchild;
	child->left = parent;
	gp->left = rchild;
	child->right = gp;

	end_->left = child;
}
*/
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
/*
template <typename T>
void SplayTree<T>::zag_zig(Node<T> *gp, Node<T> *parent, Node<T> *child)
{
	Node<T> *rchild = child->right;
	Node<T> *lchild = child->left;

	parent->left = rchild;
	child->right = parent;
	gp->right = lchild;
	child->left = gp;

	end_ = child;
}
*/
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
			// zig(parent, child);
			zig(child);
		} else {
			if (child->value > ptr->value) {
				zig(child);
			} else {
				// cout << "zig zag" << endl;
				zig_zag(child->right);
			}
		}
	} else {
		child = parent->right;
		if (child == ptr) {
			zig(child);
		} else {
			if (child->value > ptr->value) {
				// cout << "zag zig" << endl;
				zag_zig(child->left);
			} else {
				zig(child);
			}
		}
	}
	splay(ptr);
}

template <typename T>
inline Node<T>* SplayTree<T>::_find(Node<T>* ptr, const T& elt)
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
	else
	{
		return iterator(end_);
	}
}

/*
template <typename T>
SplayTree<T> SplayTree<T>::split(const T& elt)
{
	Node<T> *ptr = _find(end_, elt);

	//iterator pending
}
*/

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
