#include <cstdio>  // for NULL
#include <cstdlib> // for rand
#include <fstream>

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

class Tree {
public:
  Tree() : root(NULL) {}
  void insertAt(Node*&, int);
  void buildRandomTree();
  void printTree() const;
  void evalTree() const;
  void makeGraph() const;
  void freeTree();
private:
  Node* root;
  void printTree(const Node*) const;
  void addLeaves(Node*, int, int);
  void evalTree(const Node*, int&) const;
  void makeGraph(const Node*, std::fstream&) const;
  void freeTree(Node*);
};
