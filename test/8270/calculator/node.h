#include <cstdio>  // for NULL

class Node {
public:
  Node(int k) : key(k), left(NULL), right(NULL) {}
  Node(int k, Node* l, Node* r) : key(k), left(l), right(r) {}
  int getKey() const { return key; }
  const Node* getLeft() const { return left; }
  const Node* getRight() const { return right; }
  void setLeft(Node* l) { left = l; }
  void setRight(Node* r) { right = r; }
private:
  int key;
  Node* left;
  Node* right;
};
