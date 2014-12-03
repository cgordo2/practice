// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <fstream>
#  include <stdlib.h>
#  include "ast.h"
# include <math.h>
# include <map>

std::map <std::string, int>table;
std::map <std::string, int>functable;

double eval(Ast *a) {
  double v = 0;
  std::map<std::string, int>::const_iterator ptr;
  std::map<std::string, int>::const_iterator pointer;
  if(a != NULL)
  switch( a->getNodetype() ) {
  case 'K': v = a->getNumber(); std::cout<<" K\n";break;
  case '+': v = eval(a->getLeft()) + eval(a->getRight()); std::cout<<" +\n"; break;
  case '-': v = eval(a->getLeft()) - eval(a->getRight()); std::cout<<" -\n";break;
  case '*': v = eval(a->getLeft()) * eval(a->getRight());std::cout<<" *\n"; break;
  case '/': v = eval(a->getLeft()) / eval(a->getRight()); std::cout<<" /\n"; break;
  case 'l': if (eval(a->getLeft()) < eval(a->getRight())){v=1;}else{v=0;}; std::cout<<" l\n";break;
  case 'L': if (eval(a->getLeft()) <= eval(a->getRight())){v=1;}else{v=0;}; std::cout<<" L\n";break;
  case 'g': if (eval(a->getLeft()) > eval(a->getRight())){v=1;}else{v=0;}; std::cout<<" g\n";break;
  case 'G': if (eval(a->getLeft()) >= eval(a->getRight())){v=1;}else{v=0;}; std::cout<<" G\n";break;
  case 'e': if (eval(a->getLeft()) != eval(a->getRight())){v=1;}else{v=0;}; std::cout<<" e\n";break;
  case 'E': if (eval(a->getLeft()) == eval(a->getRight())){v=1;}else{v=0;}; std::cout<<" E\n";break;
  case 'M': v = -eval(a->getLeft()); break; std::cout<<" M\n";
  case 'P': v = pow(eval(a->getLeft()),eval(a->getRight())); std::cout<<" P\n";break;
  case 'I': ptr = table.find(a->getIdent());
                 if(ptr != table.end()){
                      v=ptr->second;
                  } 
                  std::cout<<" I\n";
                  break;
  case 'p': v =  eval(a->getLeft()); std::cout<< "PrintingResult: "<< v <<std::endl; std::cout<<" p\n";break;
  case 's': std::cout<<" s\n";if(a->getLeft()){v=eval(a->getLeft());} if(a->getRight()){v=eval(a->getRight());}break;
  // added 
  case 'a': eval(a->getLeft()); std::cout<<" a\n";break;
  case 'b': std::cout<<eval(a->getstmt());std::cout<<" b\n"; break;
  //case 'm': std::cout<<eval(a->getstmt());std::cout<<" b\n"; break;
  case 'c': ;
  case 'i':  std::cout<<" i\n";if(a->getLeft()){v=eval(a->getLeft());} if(a->getRight()){v=eval(a->getRight());}break;
  case 't':  std::cout<<" t\n";if(a->getLeft()){v=eval(a->getLeft());} if(a->getRight()){v=eval(a->getRight());}break;
  case 'd': std::cout<<" d\n";if(a->getLeft()){v=eval(a->getLeft());} if(a->getRight()){v=eval(a->getRight());}break;//std::cout<<eval(a->getLeft()); std::cout<<" c/d\n"; break;
  case 'f': std::cout<<" f\n";if(a->getLeft()){v=eval(a->getLeft());} if(a->getRight()){v=eval(a->getRight());}break;//std::cout<<eval(a->getLeft()); std::cout<<" f\n";break;
  case 'j': std::cout<<" j\n";if (eval(a->getLeft())){ return eval(a->getRight());} else return 0;
  case 'n': if (eval(a->getiff())){eval(a->getthen());} 
             else   
              return (eval(a->getelse1())); std::cout<<" n\n";break;
  // end added
  case '%': v = int(eval(a->getLeft())) % int(eval(a->getRight()));  std::cout<<" %\n";break;
  case '=': table[a->getIdent()] = eval(a->getLeft()); std::cout<<" =\n";break;
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
    case 'p':
  case 'M':
    treeFree(a->getLeft());
    break;
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
    if ( node->getLeft() && node->getLeft() != NULL) {
      output << "   " << node->getid() << "->";
      output << node->getLeft()->getid() << std::endl;
      makeGraph( node->getLeft(), output );
    }
    if ( node->getRight() && node->getRight() != NULL) {
      output << "   " << node->getid() << "->";
      output << node->getRight()->getid() << std::endl;;
      makeGraph( node->getRight(), output );
    }
    if(node->getstmt()){
      output << "   " << node->getid() << "->";
      output << node->getstmt()->getid() << std::endl;;
      makeGraph( node->getstmt(), output );
    }
    output << node -> getid()<<"[label =\"";
    if(node != NULL){
      switch(node->getNodetype()){
        case 'K': output << node->getNumber() <<"\""<<" color=blue fontcolor=black "; 
            break;
        case 'M': output << node->getNodetype()<<"\""<<" color=red fontcolor=black"; 
            break;
        case 'P': output <<node->getNodetype()<<"\""<<" color=green fontcolor=black "; 
          break;
      case '+':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case '-':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case '*':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case '/': output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case '%': output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case 'l': output<<"<"<<"\""<<" color=green fontcolor=black "; break;
      case 'L': output<<"<="<<"\""<<" color=green fontcolor=black "; break;
      case 'g': output<<">"<<"\""<<" color=green fontcolor=black "; break;
      case 'G': output<<">="<<"\""<<" color=green fontcolor=black "; break;
      case 'e': output<<"!="<<"\""<<" color=green fontcolor=black "; break;
      case 'E':output<<"=="<<"\""<<" color=green fontcolor=black "; break;
      case 'a':output<<"Start"<<"\""<<" color=green fontcolor=black "; break;
      case 'b':output<<"Funcdef"<<"\""<<" color=green fontcolor=black "; break;
      case 'd':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case 'j':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case 'n':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case 'i':output<<"Lines"<<"\""<<" color=green fontcolor=black "; break;
      case 't':output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
      case 'I':output<<"Ident"<<"\""<<" color=green fontcolor=black "; break;
      case 'p':output<<"Print"<<"\""<<" color=green fontcolor=black "; break;
      case '=':output<<"Assign"<<"\""<<" color=green fontcolor=black "; break;
      case 's': output<<"Statement"<<"\""<<" color=green fontcolor=black "; break;
      default:std::cout<<"error with node: " << node->getNodetype()<<std::endl;//output<<node->getNodetype()<<"\""<<" color=green fontcolor=black "; break;
    }
   output << " style=filled fontsize=12 ]\n";
  }
  }
}

