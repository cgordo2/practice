#include <iostream>
extern int yyparse();


int main() {
  if ( yyparse() ) {
    return 1;
  }
  else {
    std::cout << "accepted" << std::endl;
  }
  return 0;
}
