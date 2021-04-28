#include<iostream>
#include <cassert>
using namespace std;

template <typename T>
class SplayTree;

template<typename T>
class Node
{
	private:
		Node(T n);
		T value;
		Node<T>* left;
		Node<T>* right;
		~Node();
		friend class SplayTree<T>;
		template <typename U>
		friend SplayTree<U> join(const SplayTree<U> &st1, const SplayTree<U> &st2);
};

template<typename T>
class SplayTree
{

	private:
		Node<T> *head_;
		void _inorder(Node<T> *head);
		void splay(Node<T> *ptr);
		void zig(Node<T> *parent, Node<T> *ptr);
		void zig_zag(Node<T> *gp, Node<T> *parent, Node<T> *ptr);
		void zag_zig(Node<T> *gp, Node<T> *parent, Node<T> *ptr);
		void copy(Node<T> *h1, const Node<T> *h2);
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
		T get_root()
		{
			if (!head_) return T();
			return head_->value;
		}
		template <typename U>
		friend SplayTree<U> join(const SplayTree<U> &st1, const SplayTree<U> &st2);
};

/* -------------- SplayTree friend functions ------------------- */

template <typename T>
SplayTree<T> join(const SplayTree<T> &st1, const SplayTree<T> &st2)
{
	Node<T> *rightmost_st1 = st1.head_;
	while (rightmost_st1->right) {
		rightmost_st1 = rightmost_st1->right;
	}

	Node<T> *leftmost_st2 = st2.head_;
	while (leftmost_st2->left) {
		leftmost_st2 = leftmost_st2->left;
	}

	if (rightmost_st1 >= leftmost_st2) {
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
	combined.head_->right = temp.head_;

	return combined;
}

/* -------------- SplayTree friend functions end --------------- */


/* -------------- Node member functions ------------------- */

template<typename T>
Node<T>::Node(T n) : value(n), left(nullptr), right(nullptr) {}

template<typename T>
Node<T>::~Node() {}

/* -------------- Node member functions end --------------- */

/* -------------- SplayTree member function --------------- */

template<typename T>
SplayTree<T>::SplayTree() : head_(nullptr) {}

template <typename T>
SplayTree<T>::SplayTree(const SplayTree& rhs)
{
	head_ = new Node<T>(rhs.head_->value);
	copy(head_, rhs.head_);
}

template <typename T>
SplayTree<T>::SplayTree(const Node<T> *head)
{
	head_ = new Node<T>(head->value);
	copy(head_, head);
}

template <typename T>
SplayTree<T>& SplayTree<T>::operator=(const SplayTree& rhs)
{
	head_ = new Node<T>(rhs.head_->value);
	copy(head_, rhs.head_);

	return *this;
}

template <typename T>
void SplayTree<T>::copy(Node<T> *h1, const Node<T> *h2)
{
	if (h2->left) {
		h1->left = new Node<T>(h2->left->value);
		copy(h1->left, h2->left);
	}
	if (h2->right) {
		h1->right = new Node<T>(h2->right->value);
		copy(h1->right, h2->right);
	}
}

template <typename T>
void SplayTree<T>::remove(const T& value)
{
	Node<T> *elt_ptr = head_;

	while(elt_ptr && elt_ptr->value != value) {
		if (elt_ptr->value > value) {
			elt_ptr = elt_ptr->left;
		} else {
			elt_ptr = elt_ptr->right;
		}
	}

	if (!elt_ptr) {
		return;
	}

	splay(elt_ptr);
	SplayTree<T> left_sub(head_->left);
	SplayTree<T> right_sub(head_->right);
	*this = join(left_sub, right_sub);
}

template<typename T>
void SplayTree<T>::insert(const T& value)
{
	// cout << "Node " << value << " being inserted" << '\n';
	Node<T> *temp = new Node<T>(value);
	if(head_ == nullptr)
	{
		head_ = temp;
		return;
	}

	Node<T> *trav = head_;
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
	_inorder(this->head_);
}

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

	head_ = ptr;
}

template <typename T>
void SplayTree<T>::zig_zag(Node<T> *gp, Node<T> *parent, Node<T> *child)
{
	Node<T> *rchild = child->right;
	Node<T> *lchild = child->left;

	parent->right = lchild;
	child->left = parent;
	gp->left = rchild;
	child->right = gp;

	head_ = child;
}

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

template <typename T>
void SplayTree<T>::splay(Node<T> *ptr)
{
	if (ptr == head_) return;

	Node<T> *parent = head_;
	Node<T> *child = nullptr;

	if (parent->value > ptr->value) {
		child = parent->left;
		if (child == ptr) {
			zig(parent, child);
		} else {
			if (child->value > ptr->value) {
				zig(parent, child);
			} else {
				// cout << "zig zag" << endl;
				zig_zag(parent, child, child->right);
			}
		}
	} else {
		child = parent->right;
		if (child == ptr) {
			zig(parent, child);
		} else {
			if (child->value > ptr->value) {
				// cout << "zag zig" << endl;
				zag_zig(parent, child, child->left);
			} else {
				zig(parent, child);
			}
		}
	}
	splay(ptr);
}

template<typename T>
SplayTree<T>::~SplayTree()
{
	Node<T> *trav;
	Node<T> *prev;
	while(head_ != nullptr)
	{
		prev = nullptr;
		trav = head_;
		while(trav->left || trav->right)
		{
			prev = trav;
			if(trav->left == nullptr)
			{
				trav = trav->right;
			}
			else
			{
				trav = trav->left;
			}
		}

		if(head_ == trav)
		{
			head_ = nullptr;
		}
		else if(prev->left == trav)
		{
			prev->left = nullptr;
		}
		else
		{
			prev->right = nullptr;
		}
		delete trav;
	}
}

/* -------------- SplayTree member function end ----------- */

int main()
{
	SplayTree<int> st;
	st.insert(2);
	st.insert(3);
	st.insert(4);
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
	cout << '\n';
	st2.inorder();
	cout << '\n';
	cout << "root: " << st.get_root() << '\n';
	cout << "root2: " << st2.get_root() << '\n';

	st2.remove(12);
	st2.inorder();
	cout << '\n';
	cout << "root2 new: " << st2.get_root() << '\n';

	// SplayTree<int> comb;
	// SplayTree<int> comb(join(st, st2));
	// comb = join(st, st2);
	// comb.inorder();
	// cout << '\n';
	// cout << "root comb: " << comb.get_root() << '\n';
}
