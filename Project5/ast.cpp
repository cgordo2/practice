#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "ast.h"

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

