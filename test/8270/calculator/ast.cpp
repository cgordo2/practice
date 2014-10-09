// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <stdlib.h>
#  include "ast.h"
# include <math.h>

double eval(Ast *a) {
  double v = 0;
  switch( a->getNodetype() ) {
  case 'K': v = a->getNumber(); break;
  case '+': v = eval(a->getLeft()) + eval(a->getRight()); break;
  case '-': v = eval(a->getLeft()) - eval(a->getRight()); break;
  case '*': v = eval(a->getLeft()) * eval(a->getRight()); break;
  case '/': v = eval(a->getLeft()) / eval(a->getRight()); break;
  case 'M': v = -eval(a->getLeft()); break;
  case  'P': v = pow(eval(a->getLeft()),eval(a->getRight())); break;
  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
  return v;
}

double eval(Ast *astNode){
  switch(astNode->getNodetype()){

  case'K':
  case'+':
  case'-':
  case'*':
  case'/':
  case'M':
  case'P':

  }

}

void treeFree(Ast *a) {
  switch(a->getNodetype()) {
   // two subtrees
  case '+':
  case '-':
  case '*':
  case '/':
  case 'P':
    treeFree(a->getRight());

   // one subtrees
  case 'M':
    treeFree(a->getLeft());

   //no subtree
  case 'K':
    delete a;
    break;

  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
}
void makeGraph(Ast* Node, std::fstream& output) const {
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

