%{
#include <iostream>
#include <cmath>    
#include <map>
#include <math.h>

#include "ast.h"   

extern int yylex();

  void yyerror(const char * msg){ std::cout << msg << std::endl; }
  void yyerror(const char *msg, const char ch) {
    std::cout << msg << ch << std::endl;
  }
  std::map<char*, int>table;
%}


%union {
  Node* ast;
  double dub;
  int num;
  char * id;
}

%token CR
%token ASSIGN
%token PRINT
%token <id>IDENT 
%token <dub>NUMBER
%token FLOAT
%token LPAREN
%token RPAREN
%token DEF
%token COLON
%token COMMA
%token IF
%token END
%token ELSE
%token RETURN
%token EXPON

%left  LESS LESSEQ GREAT GREATEQ EQ NOTEQ
%left  PLUS MINUS
%left  MULT DIV MOD
%right EXPON

%nonassoc less_than_else
%nonassoc ELSE
%type<ast> expr start funcdef parm_list stmt selection line 
%%

start   : start funcdef {$$ = 0;}
        | { ; } 
        ;

funcdef : DEF IDENT LPAREN parm_list RPAREN COLON stmt END {yyerrok;}
        | CR {$$ = 0;}
        ;           

parm_list 
        : expr COMMA parm_list {$$ = 0;}
        | expr {$$ = 0;}
        |{$$ = 0;}
        ;

stmt    : line stmt {$$ = 0;}
        | selection stmt {$$ = 0;}
        | CR stmt{$$ = 0;}
        |{$$ = 0;}
        ;

selection 
        : IF expr COLON stmt %prec less_than_else END {$$ = 0;}
        | IF expr COLON stmt ELSE COLON stmt END{$$ = 0;}
        ;

line    : IDENT ASSIGN expr {table[$1] = $3->eval();}
        | IDENT LPAREN parm_list RPAREN {$$ = 0;}
        | PRINT expr {std::cout<< $2->eval();}
        | RETURN expr{$$ = 0;}
        ;

expr    : expr PLUS expr { $$ = new AddBinaryNode($1, $3); }
        | expr MINUS expr{ $$ = new SubBinaryNode($1, $3); }
        | expr MULT expr { $$ = new MulBinaryNode($1, $3); }
        | expr EXPON expr { $$ = new ExpBinaryNode($1, $3); }
        | expr DIV expr  { $$ = new DivBinaryNode($1, $3);}
        | expr MOD expr { $$ = new ModBinaryNode($1, $3); }
        | expr LESS expr {$$=0;}
        | expr LESSEQ expr {$$=0;}
        | expr GREAT expr {$$=0;}
        | expr GREATEQ expr{$$=0;}
        | expr NOTEQ expr {$$=0;}
        | expr EQ expr {$$=0;}
        | MINUS expr { $$ = new UnaryMinusNode($2);}
        | NUMBER { $$ = new NumberNode($1);        }
        | IDENT { $$ = new IdentNode($1);}
        | LPAREN expr RPAREN {$$ = $2;}
        ;

%%
