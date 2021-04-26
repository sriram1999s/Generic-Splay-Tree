#include<iostream>
using namespace std;

// template<typename T>
// struct Node
// {
//   T value;
//   T* left;
//   T* right;
// };

struct Node
{
  int value;
  Node* left;
  Node* right;

  Node(int n);
  ~Node();
};


class SplayTree
{

  private:
    // Node *head_ = nullptr;

  public:
    SplayTree();
    ~SplayTree();
    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;
    void insert(int x);
    Node *head_;

};


/* -------------- Node member functions ------------------- */

Node::Node(int n)
:value(n), left(nullptr), right(nullptr)
{
  cout << "Node being created : " << n << '\n';
}

Node::~Node()
{
  cout << "Node being deleted : "<< value << '\n';
}
/* -------------- Node member functions end --------------- */

/* -------------- SplayTree member function --------------- */

SplayTree::SplayTree()
:head_(nullptr)
{

}

SplayTree::~SplayTree()
{
  Node *trav;
  Node *prev;
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

void SplayTree::insert(int x)
{
  Node* temp = new Node(x);
  if(head_ == nullptr)
  {
    head_ = temp;
    return;
  }
  Node *trav = head_;
  Node *prev = nullptr;
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


void inorder(Node* head)
{
  if(head == nullptr)
  return;

  inorder(head->left);
  cout << head->value << '\n';
  inorder(head->right);
}


int main()
{
  SplayTree st;
  st.insert(5);
  st.insert(8);
  st.insert(1);
  st.insert(4);
  st.insert(7);
  st.insert(24);

  inorder(st.head_);
}
