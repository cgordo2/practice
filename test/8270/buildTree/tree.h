#include <cstdlib> // for rand
#include <fstream>
#include "node.h"

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
