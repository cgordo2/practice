//  Source code for "flex & bison", by John Levine
//  Declarations for an AST calculator fb3-1
//  Adapted by Brian Malloy
%{
#include <iostream>
#include "ast.h"
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

%token <d> NUMBER
%token EOL
%type <ast> exp factor term

%%

calclist 
       : calclist exp EOL {
           std::cout << "= " << eval($2) << std::endl;
           treeFree($2);
           std::cout << "> ";
         }
       | calclist EOL // blank line or a comment
       | // empty
       ;

exp    : factor
       | exp '+' factor { $$ = new AstNode('+', $1,$3); }
       | exp '-' factor { $$ = new AstNode('-', $1,$3);}
       ;

factor : term
       | factor '*' term { $$ = new AstNode('*', $1,$3); }
       | factor '/' term { $$ = new AstNode('/', $1,$3); }
       ;

term   : NUMBER   { $$ = new AstNumber('K', $1); }
       | '(' exp ')' { $$ = $2; }
       | '-' term    { $$ = new AstNode('M', $2, NULL); }
       ;
%%
