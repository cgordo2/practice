// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <fstream>
#  include <stdlib.h>
#  include "ast.h"
# include <math.h>
# include <map>
std::map <char*, int>table;

double eval(Ast *a) {
  double v = 0;
  std::map<char*, int>::const_iterator ptr;
  switch( a->getNodetype() ) {
  case 'K': v = a->getNumber(); break;
  case '+': v = eval(a->getLeft()) + eval(a->getRight()); break;
  case '-': v = eval(a->getLeft()) - eval(a->getRight()); break;
  case '*': v = eval(a->getLeft()) * eval(a->getRight()); break;
  case '/': v = eval(a->getLeft()) / eval(a->getRight()); break;
  case 'l': if (eval(a->getLeft()) < eval(a->getRight())){v=1;}else{v=0;}; break;
  case 'L': if (eval(a->getLeft()) <= eval(a->getRight())){v=1;}else{v=0;}; break;
  case 'g': if (eval(a->getLeft()) > eval(a->getRight())){v=1;}else{v=0;}; break;
  case 'G': if (eval(a->getLeft()) >= eval(a->getRight())){v=1;}else{v=0;}; break;
  case 'e': if (eval(a->getLeft()) != eval(a->getRight())){v=1;}else{v=0;}; break;
  case 'E': if (eval(a->getLeft()) == eval(a->getRight())){v=1;}else{v=0;}; break;
  case 'M': v = -eval(a->getLeft()); break;
  case 'P': v = pow(eval(a->getLeft()),eval(a->getRight())); break;
  case 'I': ptr = table.find(a->getIdent());
                 if(ptr != table.end()){
                      v=ptr->second;
                  } 
                  break;
  case 'p': std::cout<<eval(a->getLeft());
  case 's': std::cout<<eval(a->getLeft());
  // added 
  case 'a': std::cout<<eval(a->getLeft()); break;
  case 'b': std::cout<<eval(a->getstmt()); break;
  case 'c': ;
  case 'd': std::cout<<eval(a->getLeft()); break;
  case 'f': std::cout<<eval(a->getLeft()); break;
  case 'j': if (eval(a->getRight())){ return eval(a->getLeft());} else return 0;
  case 'n': if (iff->eval()){then->eval();} else   return {else1->eval()}; break;
  // end added
  case '%': v = int(eval(a->getLeft())) % int(eval(a->getRight()));  break;
  case '=': table[a->getIdent()] = eval(a->getLeft());break;
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
  case '%':
    treeFree(a->getRight());

   // one subtrees
  case 'M':
    treeFree(a->getLeft());

   //no subtree
    case 'I':
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

