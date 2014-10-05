#include <iostream>
#include "tree.h"

void Tree::insertAt(Node*& temp, int val) {
  temp = new Node(val);
}

void Tree::addLeaves(Node* temp, int lval, int rval) {
  temp->setLeft( new Node(lval, NULL, NULL) );
  temp->setRight( new Node(rval, NULL, NULL) );
}

void Tree::buildRandomTree() {
  insertAt(root, 1);
  addLeaves(root, 2, 3);
  Node* temp = root;
  temp = const_cast<Node*>(temp->getLeft());
  addLeaves(temp, 4, 5);
  temp = const_cast<Node*>(temp->getRight());
  addLeaves(temp, 6, 7);
}

void Tree::printTree() const {
  printTree(root);
}

void Tree::printTree(const Node* node) const {
  if ( node ) {
    std::cout << node->getKey() << std::endl;
    printTree( node->getLeft() );
    printTree( node->getRight() );
  }
}

void Tree::evalTree(const Node* node, int& sum) const {
  if ( node ) {
    sum += node->getKey();
    evalTree( node->getLeft(), sum );
    evalTree( node->getRight(), sum );
  }
}

void Tree::makeGraph(const Node* node, std::fstream& output) const {
  if ( node ) {
    if ( node->getLeft() ) {
      output << "   " << node->getKey() << "->";
      output << node->getLeft()->getKey() << std::endl;
      makeGraph( node->getLeft(), output );
    }
    if ( node->getRight() ) {
      output << "   " << node->getKey() << "->";
      output << node->getRight()->getKey() << std::endl;;
      makeGraph( node->getRight(), output );
    }
  }
}

void Tree::makeGraph() const {
  std::fstream output;
  output.open("graph.gv", std::ios::out);
  output << "digraph G {" << std::endl;
  makeGraph(root, output);
  output << "}" << std::endl;
  output.close();
}

void Tree::evalTree() const {
  int sum = 0; 
  evalTree(root, sum);
  std::cout << "sum is " << sum << std::endl;
}

void Tree::freeTree(Node* temp) {
  if ( temp ) {
    Node* left = const_cast<Node*>(temp->getLeft());
    Node* right = const_cast<Node*>(temp->getRight());
    delete temp;
    freeTree(left);
    freeTree(right);
  }
  root = NULL;
}

void Tree::freeTree() {
  freeTree(root);
}
