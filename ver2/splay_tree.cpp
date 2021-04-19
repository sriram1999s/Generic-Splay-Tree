#include<iostream>
using namespace std;

// template<typename T>
// struct Node
// {
//   T value;
//   T* left;
//   T* right;
// };

template<typename T>
struct Node
{
  T value;
  Node<T>* left;
  Node<T>* right;

  Node(T n);
  ~Node();
};


template<typename T>
class SplayTree
{

  private:
    // Node *head_ = nullptr;

  public:
    SplayTree();
    ~SplayTree();
    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;
    void insert(T x);
    Node<T> *head_;

};


/* -------------- Node member functions ------------------- */

template<typename T>
Node<T>::Node(T n)
:value(n), left(nullptr), right(nullptr)
{
  cout << "Node being created : " << n << '\n';
}

template<typename T>
Node<T>::~Node()
{
  cout << "Node being deleted : "<< value << '\n';
}
/* -------------- Node member functions end --------------- */

/* -------------- SplayTree member function --------------- */


template<typename T>
SplayTree<T>::SplayTree()
:head_(nullptr)
{

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

template<typename T>
void SplayTree<T>::insert(T x)
{
  Node<T>* temp = new Node<T>(x);
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
    if(trav->value > x)
    {
      trav = trav->left;
    }
    else
    {
      trav = trav->right;
    }
  }
  if(prev->value > x)
  {
    prev->left = temp;
  }
  else
  {
    prev->right = temp;
  }

}


/* -------------- SplayTree member function end ----------- */

/* -------------- free functions -------------------------- */


template<typename T>
void inorder(Node<T>* head)
{
  if(head == nullptr)
  return;

  inorder(head->left);
  cout << head->value << '\n';
  inorder(head->right);
}


int main()
{
  SplayTree<double> st;
  st.insert(5.1);
  st.insert(8.1);
  st.insert(1.1);
  st.insert(4.1);
  st.insert(7.1);
  st.insert(24.1);

  inorder(st.head_);
}
