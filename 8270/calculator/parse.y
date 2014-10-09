%{
#include <iostream>
#include "ast.h"

extern int yylex();
void yyerror(const char *s) { std::cout << s << std::endl; }
void yyerror(const char *s, const char ch) {
  std::cout << s << ch << std::endl; }
extern std::fstream output1;
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
          std::cout << "> ";
          makeGraph($1, output1);
          treeFree($1);
          };

Expression:
  NUMBER {$$ = new AstNumber('K', $1); }
| Expression PLUS Expression { $$ = new AstNode('+', $1,$3); }
| Expression MINUS Expression { $$ = new AstNode('-', $1,$3);}
| Expression TIMES Expression {  $$ = new AstNode('*', $1,$3); }
| Expression DIVIDE Expression { $$ = new AstNode('/', $1,$3);  }
| MINUS Expression %prec NEG { $$ = new AstNode('M', $2, NULL); }
| Expression POWER Expression {  $$ = new AstNode('P', $1,$3);}
| LEFT Expression RIGHT { $$=$2; }
;

%%



