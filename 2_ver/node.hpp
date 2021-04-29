template <typename T>
class SplayTree;

template<typename T>
class Node
{
	private:
		Node(T n, bool end = false);
		T value;
		bool end;
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
Node<T>::Node(T n, bool end) : value(n), end(end), left(nullptr), right(nullptr), parent(nullptr) {}

template<typename T>
Node<T>::~Node() {}

/* -------------- Node member functions end --------------- */
