#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "ast.h"
std::map<char*, int> table;
//will need another map for fucnctions

int power(int lhs, int rhs) { return pow(lhs, rhs); }

BinaryNode::~BinaryNode() {
  delete left;
  delete right;
}

double AddBinaryNode::eval() const { 
  return left->eval()+right->eval(); 
}

double SubBinaryNode::eval() const { 
  return left->eval()-right->eval(); 
}

double MulBinaryNode::eval() const { 
  return left->eval()*right->eval(); 
}

double DivBinaryNode::eval() const { 
  double result = right->eval();
  if ( result == 0 ) throw std::string("Can't divide by zero!");
  return left->eval()/right->eval(); 
}

double ModBinaryNode::eval() const { 
  return ::fmod(left->eval(), right->eval()); 
}

double ExpBinaryNode::eval() const { 
  return power(left->eval(), right->eval()); 
}

// .... code here ...

double LessBinaryNode::eval() const { 
  if (left->eval() < right->eval())
      return 1;
    else 
      return 0;
  //return left->eval() < right->eval(); // return 1 if true and zero if false 
}

double LessEQBinaryNode::eval() const { 
  if (left->eval() <= right->eval())
      return 1;
    else 
      return 0;
  //return left->eval() <= right->eval(); 
}

double GreatBinaryNode::eval() const { 
  if (left->eval() > right->eval())
      return 1;
    else 
      return 0;
  //return left->eval() > right->eval(); 
}

double GreatEQBinaryNode::eval() const { 
  if (left->eval() >= right->eval())
      return 1;
    else 
      return 0;
  //return left->eval() >= right->eval(); 
}

double NotEQBinaryNode::eval() const { 
  if (left->eval() != right->eval())
      return 1;
    else 
      return 0;
  //return left->eval() != right->eval(); 
}

double EQBinaryNode::eval() const { 
  if (left->eval() == right->eval())
      return 1;
    else 
      return 0;
  //return left->eval() == right->eval(); 
}

// Insertd code  ////
double SelectionNode::eval() const{
// return eval
std::cout << "In SelectionNode eval "  << std::endl; 
         if( right ->eval()){std::cout << "here is it: "  << std::endl;}
  return  left ->eval() ; std::cout << "here is it: "  << std::endl;
}

double SelectNode::eval() const{
// return eval
std::cout << "In SelectNode eval "  << std::endl; 
          right ->eval();
  return  left ->eval();
}

double StmtNode::eval() const{
  std::cout << "In StmtNode eval "  << std::endl;
  if (!left) std::cout << "LEFT IS NULL" << std::endl;
     return left->eval();
}

double IfNode::eval() const{ 
// call the branch that is true and return it.
  std::cout << "In IfNode eval "  << std::endl;
 if ( right ->eval()){
  return left ->eval();}
  else 
    return 0;

}

double ElseNode::eval() const{
 // got to choose the correct branch 
  std::cout << "In ElseNode eval "  << std::endl;
  if (if_1 ->eval()){then->eval();}
    else 
    return  else_1->eval();
  

}

double FuncNode::eval() const{
// function call with paramaters
  //Ident->eval(); 
  std::cout << "In FuncNode eval "  << std::endl;
  //return right->eval(); 

}

double ExpressNode::eval() const{
//evalueate expression
  std::cout << "In ExpressNode eval "  << std::endl;
  return left ->eval();

}

double ParmNode::eval() const{
//evaluate paramatars not needed yet
  std::cout << "In ParmNode eval "  << std::endl;
  //right ->eval();
  //return left->eval();
}

double FuncdefNode::eval() const{
//def of a function 
  std::cout << "In funcdef eval "  << std::endl;
  return stmt->eval();

}

double StartNode::eval() const{
// just start node
   std::cout << "In start eval "  << std::endl;
  return left->eval();

}

double AssignNode::eval() const{
        std::cout << "The Ident string is: " << left->getIdent() << std::endl;
        table [left->getIdent()] = right->eval(); 

}

double PrintNode::eval() const{
          std::cout << "In print eval "  << std::endl;

        std::cout << "The Ident string is: " << left->getIdent() << std::endl;
        std::cout<< left->eval(); 

}

double IdentNode::eval() const {
  std::cout<<"ident in eval: " << Ident<<std::endl;
std::map<char*, int>::const_iterator ptr = table.find(Ident);
  if ( ptr == table.end() ) {
    std::cout<<"Didn't FInd Ident";
   return 0;
  }
  else {
    std::cout<<"foudn ident"<<std::endl;;
    std::cout<<ptr->second;
    return ptr->second;
  }//table find stuff here;
} 
