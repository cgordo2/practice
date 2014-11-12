#include <iostream>
#include <string>
#include "ast.h"
extern int yyparse();
int Node::idCount = 0;

int main() {
  if ( !yyparse() ) {
     std::cout << "accepted" << std::endl;
  }
  else {
    std::cout << "Syntax error" << std::endl;
  }
  return 0;
}
