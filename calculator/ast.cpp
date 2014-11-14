// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <fstream>
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
  case 'P': v = pow(eval(a->getLeft()),eval(a->getRight())); break;
  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
  return v;
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

void makeGraph(const Ast* node, std::fstream& output) {
  if ( node ) {
    if ( node->getLeft() ) {
      output << "   " << node->getid() << "->";
      output << node->getLeft()->getid() << std::endl;
      makeGraph( node->getLeft(), output );
    }
    if ( node->getRight() ) {
      output << "   " << node->getid() << "->";
      output << node->getRight()->getid() << std::endl;;
      makeGraph( node->getRight(), output );
    }
    output << node -> getid()<<"[label =\"";
         switch(node->getNodetype()){
    case 'K': output << node->getNumber() <<"\""<<" color=blue fontcolor=black "; 
    break;
    case 'M': output << node->getNodetype()<<"\""<<" color=red fontcolor=black"; 
    break;
    case 'P': output <<node->getNodetype()<<"\""<<" color=green fontcolor=black "; 
    break;
    case '+':
    case '-':
    case '*':
    case '/': output <<node->getNodetype()<<"\""<<" color=green fontcolor=black ";
    break;
    }
   output << " style=fill fontsize=12 ]\n";

  }
}

