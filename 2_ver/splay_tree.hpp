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
		int size_;
		Node<T> *head_;
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
			if (!head_) return T();
			return head_->value;
		}
		template <typename U>
		friend SplayTree<U> join(const SplayTree<U> &st1, const SplayTree<U> &st2);

		class iterator
		{
			private:
				Node<T>* p_;
			public:
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
					return !operator==(rhs);
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
					if(p_){
						if(p_->right)
						{
							p_ = p_->right;
							while(p_->left) p_ = p_->left;
						}
						else
						{
							while(p_->parent && !(p_->parent->value > p_->value)) p_ = p_->parent;
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
					if(!p_) /* to be completed */
					{

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
							while(p_->parent && (p_->parent->value < p_->value)) p_ = p_->parent;
							p_ = p_->parent;
						}
					}
					return *this;
				}

				iterator operator+(int x)
				{
					iterator temp(*this);
					while(x--)
					{
						++temp;
					}
					return temp;
				}


		};
		iterator begin();
		iterator end();
};

/* -------------- SplayTree iterator functions ----------------- */

template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::begin()
{
	if(!head_)
	{
		return iterator();
	}
	Node<T> *trav = head_;
	while(trav->left)
	{
		trav = trav->left;
	}
	return iterator(trav);
}

template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::end()
{
	return iterator();
}
/* -------------- SplayTree iterator functions ends ------------ */

/* -------------- SplayTree friend functions ------------------- */

template <typename T>
SplayTree<T> join(const SplayTree<T> &st1, const SplayTree<T> &st2)
{
	if (!st1.head_ || !st2.head_) {
		return SplayTree<T>();
	}

	Node<T> *rightmost_st1 = st1.head_;
	while (rightmost_st1->right) {
		rightmost_st1 = rightmost_st1->right;
	}

	Node<T> *leftmost_st2 = st2.head_;
	while (leftmost_st2->left) {
		leftmost_st2 = leftmost_st2->left;
	}

	if (rightmost_st1->value >= leftmost_st2->value) {
		return SplayTree<T>();
	}

	SplayTree<T> combined(st1);
	SplayTree<T> temp(st2);

	Node<T> *rightmost_combined = combined.head_;
	while (rightmost_combined->right) {
		rightmost_combined = rightmost_combined->right;
	}

	combined.splay(rightmost_combined);

	assert (combined.head_->right == nullptr);

	combined.head_->right = new Node<T>(temp.head_->value);
	combined.copy(combined.head_->right, temp.head_);

	return combined;
}

/* -------------- SplayTree friend functions end --------------- */


/* -------------- SplayTree member function -------------------- */

template<typename T>
SplayTree<T>::SplayTree() : head_(new Node<T>(T())), size_(0)
{}

template <typename T>
SplayTree<T>::SplayTree(const SplayTree& rhs) : head_(new Node<T>(T())), size_(0)
{
	if (rhs.size_) {
		// head_ = new Node<T>(rhs.head_->value);
		copy(head_, rhs.head_);
	}
}

template <typename T>
SplayTree<T>::SplayTree(const Node<T> *head) : head_(new Node<T>(T())), size_(0)
{
	if (head) {
		// head_ = new Node<T>(head->value);
		copy(head_, head);
	}
}

template <typename T>
SplayTree<T>& SplayTree<T>::operator=(const SplayTree& rhs)
{
	_deallocate(head_);

	head_ = new Node<T>(T());
	size_ = 0;
	if (rhs.size_) {
		// head_ = new Node<T>(rhs.head_->value);
		copy(head_, rhs.head_);
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
	Node<T> *elt_ptr = _find(head_, value);

	if (!elt_ptr) {
		return;
	}

	splay(elt_ptr);
	SplayTree<T> left_sub(head_->left);
	SplayTree<T> right_sub(head_->right);
	*this = join(left_sub, right_sub);
	--size_;
}

template<typename T>
void SplayTree<T>::insert(const T& value)
{
	// cout << "Node " << value << " being inserted" << '\n';
	Node<T> *temp = new Node<T>(value);
	if(size_ == 0)
	{
		head_->left = temp;
		temp->parent = head_;
		++size_;
		return;
	}

	Node<T> *trav = head_->left;
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
	_inorder(this->head_->left);
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

	head_->left = ptr;
}
*/
template <typename T>
void SplayTree<T>::zig(Node<T> *ptr)
{
	Node<T> *parent = ptr->parent;
	assert(parent != head_);
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

	head_->left = ptr;
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

	head_->left = child;
}
*/
template <typename T>
void SplayTree<T>::zig_zag(Node<T> *child)
{
	Node<T> *gp = child->parent->parent;
	Node<T>* parent = child->parent;
	assert(gp != head_ && parent != head_);

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

	head_->left = child;
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

	head_ = child;
}
*/
template <typename T>
void SplayTree<T>::zag_zig(Node<T> *child)
{
	Node<T> *gp = child->parent->parent;
	Node<T>* parent = child->parent;
	assert(gp != head_ && parent != head_);

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

	head_->left = child;
}

template <typename T>
void SplayTree<T>::splay(Node<T> *ptr)
{
	if (ptr == head_->left) return;

	Node<T> *parent = head_->left;
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
	Node<T> *h = _find(head_->left, elt);

	// return iterator instead of the below code
	if (h) {
		splay(h);
		assert(h == head_->left);
		return iterator(h);
	}
	else
	{
		return iterator();
	}
}

/*
template <typename T>
SplayTree<T> SplayTree<T>::split(const T& elt)
{
	Node<T> *ptr = _find(head_, elt);

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
	_deallocate(head_);
}

/* -------------- SplayTree member function end ---------------- */
