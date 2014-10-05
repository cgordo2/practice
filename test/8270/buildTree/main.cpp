#include "tree.h"

int main() {
  Tree tree;
  tree.buildRandomTree();
  tree.printTree();
  tree.evalTree();
  tree.makeGraph();
  tree.freeTree();
  tree.buildRandomTree();
  tree.printTree();
  tree.evalTree();
  tree.freeTree();
  return 0;
}
