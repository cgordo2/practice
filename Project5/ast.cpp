#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "ast.h"
extern std::map <char*, int>table;
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

// CODE FOR THE ASSIGN NODE 
double AssignNode::eval() const{

        table [IdentNode(left)->getIdent()] = right->eval();
 //return (left->eval(), right->eval()); 
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