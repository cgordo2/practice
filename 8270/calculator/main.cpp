#include <iostream>
#include <fstream>
#include <string>
extern int yyparse();
std::fstream output1;
std::string textvalues;
int main() {
  output1.open("graph.gv", std::ios::out);
  output1 << "digraph G {" << std::endl;

  try {
    std::cout << "> "; 
    int returnCode = yyparse();
    std::cout << std::endl;
    std::cout<<textvalues<<std::endl;
     output1 << "\n labelloc=\"t\"\n label=\"Clayton's Graphs \\n"<< textvalues <<"\""<<"\n";
     output1 << "}" << std::endl;
  output1.close();
    return returnCode;
  }
  catch (const std::string& msg) {
    std::cout << msg << std::endl; 
  }
  catch (...) {
    std::cout << "Oops, need someone behind the plate" << std::endl; 
  }
 
  return 0;
}
