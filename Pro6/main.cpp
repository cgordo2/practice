#include <iostream>
#include <string>
#include "ast.h"
#include <ostream>
extern int yyparse();
//int Node::idCount = 0;
	std::fstream output;
int main() {

                              output.open("graph.gv", std::ios::out);
                              output << "digraph G {" << std::endl;
  if ( !yyparse() ) {
     std::cout << "accepted" << std::endl;
  }
  else {
    std::cout << "Syntax error" << std::endl;
  }
  output << "}" << std::endl;
                              output.close();
  return 0;
}
