// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#include <fstream>
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
void AstNode (Ast *astNode){
  switch(astNode -> getNodetype()){
  case 'K': 
  case '+': 
  case '-': 
  case '*': 
  case '/': 
  case 'M': 
  case 'P':;
  }
}

  void makeGraph(const Ast* node, std::fstream& output)  {
  if ( node ) {
    if ( node->getLeft() ) {
      output << "   " << node->getid() << "->";
      output << "\""<<node->getLeft()->getid() <<"\":f2"<< std::endl;
      makeGraph( node->getLeft(), output );
    }
    if ( node->getRight() ) {
      output << "   " << node->getid() << "->";
      output << "\""<< node->getRight()->getid()<<"\":f2" << std::endl;;
      makeGraph( node->getRight(), output );
    }
     output << node -> getid()<<"[label =\"";
     switch(node->getNodetype()){
      case 'K': output << "<f1>Left|<f2>"<< node->getNumber() <<"|<f3>Right\""<<" color=blue fontcolor=black shape=record "; //needs own color
                break;

      case 'M': output <<"<f1>Left|<f2>-|<f3>Right"<<"\""<<" color=red fontcolor=black shape=record "; //needs own color
                break;
      case 'P': output <<"<f1>Left|<f2>**|<f3>Right"<<"\""<<" color=green fontcolor=black shape=record "; //This and below same color
                break;
      case '+':
      case '-':
      case '*':
      case '/': output << "<f1>Left|<f2>"<<node->getNodetype()<<"|<f3>Right\""<<" color=green fontcolor=black shape=record ";
                break;
     }
     output << "  fontsize=12 ]\n";
  }
}




