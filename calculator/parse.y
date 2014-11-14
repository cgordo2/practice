%{
#include <iostream>
#include "ast.h" 
//#include <fstream>


extern int yylex();
  void yyerror(const char *s) { std::cout << s << std::endl; }
  void yyerror(const char *s, const char ch) {
    std::cout << s << ch << std::endl;
  }	
%}

%union {
  Ast* ast;
  double d;
}
%type <ast> Expression
%token <d> NUMBER
%token <ast> PLUS MINUS TIMES DIVIDE POWER
%token LEFT RIGHT
%token END

%left PLUS MINUS
%left TIMES DIVIDE
%left <ast> NEG
%right POWER

%start Input
%%

Input:
    
     | Input Line
;

Line:
     END
     | Expression END  {
           std::cout << "= " << eval($1) << std::endl;
           //treeFree($1);
           std::cout << "> ";
          
           //makeGraph(); 
           std::fstream output;
           output.open("graph.gv", std::ios::out);
           output << "digraph G {" << std::endl;
           makeGraph($1, output);
           treeFree($1);
           output << "}" << std::endl;
           output.close();
               
         }
;

Expression:
     NUMBER {$$ = new AstNumber('K', $1);  }
| Expression PLUS Expression { $$ = new AstNode('+', $1,$3); }
| Expression MINUS Expression { $$ = new AstNode('-', $1,$3);}
| Expression TIMES Expression {  $$ = new AstNode('*', $1,$3); }
| Expression DIVIDE Expression { $$ = new AstNode('/', $1,$3);  }
| MINUS Expression %prec NEG { $$ = new AstNode('M', $2, NULL); }
| Expression POWER Expression {  $$ = new AstNode('P', $1,$3);}
| LEFT Expression RIGHT { $$=$2; }
;

%%



