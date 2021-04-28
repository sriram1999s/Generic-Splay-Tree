template <typename T>
class SplayTree;

template<typename T>
class Node
{
	private:
		Node(T n);
		T value;
		Node<T> *left;
		Node<T> *right;
		Node<T> *parent;
		~Node();
		friend class SplayTree<T>;
		template <typename U>
		friend SplayTree<U> join(const SplayTree<U> &st1, const SplayTree<U> &st2);
};

/* -------------- Node member functions ------------------- */

template<typename T>
Node<T>::Node(T n) : value(n), left(nullptr), right(nullptr), parent(nullptr) {}

template<typename T>
Node<T>::~Node() {}

/* -------------- Node member functions end --------------- */
