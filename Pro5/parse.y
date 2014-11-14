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
  //std::map<char*, int>table;
%}


%union {
  Ast* ast;
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
%left NEG
%right EXPON

%nonassoc less_than_else
%nonassoc ELSE
%type<ast> expr start funcdef parm_list stmt selection line 
%%

start   : start funcdef {$$ = 0;}
        | { ; } 
        ;

funcdef : DEF IDENT LPAREN parm_list RPAREN COLON stmt END {; yyerrok;}
        | CR {$$ = 0;}
        ;           

parm_list 
        : expr COMMA parm_list {$$ = 0;}
        | expr {$$ = 0;}
        |{$$ = 0;}
        ;

stmt    : line stmt {$$ = new AstStmt('s',$1);}//{$$ = 0;}
        | selection stmt {$$ = 0;}
        | CR stmt{$$ = 0;}
        |   {$$=0;}//{$$ = new AssignNode ($1, $3);} // list of statement. 
        ;

selection 
        : IF expr COLON stmt %prec less_than_else END {$$ = 0;}
        | IF expr COLON stmt ELSE COLON stmt END{$$ = 0;}
        ;

line    : IDENT ASSIGN expr {$$ = new AstAssign('=',$1,$3);}
        | IDENT LPAREN parm_list RPAREN {$$ = 0;}
        | PRINT expr {$$ = new AstPrint('p',$2);} // printing  out std::cout<< eval($2)
        | RETURN expr{$$ = 0;}
        ;

expr    : expr PLUS expr { $$ = new AstNode('+', $1,$3); }
        | expr MINUS expr{ $$ = new AstNode('-', $1,$3); }
        | expr MULT expr { $$ = new AstNode('*', $1,$3); }
        | expr EXPON expr { $$ = new AstNode('P', $1,$3); }
        | expr DIV expr  { $$ = new AstNode('/', $1,$3); }
        | expr MOD expr { $$ = new AstNode('%', $1,$3); }
        | expr LESS expr {$$ = new AstNode('l',$1,$3);}
        | expr LESSEQ expr {$$ = new AstNode('L',$1,$3);}
        | expr GREAT expr {$$ = new AstNode('g',$1,$3);}
        | expr GREATEQ expr{$$ = new AstNode('G',$1,$3);}
        | expr NOTEQ expr {$$ = new AstNode('e',$1,$3);}
        | expr EQ expr {$$ = new AstNode('E',$1,$3);}
        | MINUS expr %prec NEG { $$ = new AstNode('M', $2, NULL); }
        | NUMBER {$$ = new AstNumber('K', $1);  }
        | IDENT { $$ = new AstIdent('I', $1);}
        | LPAREN expr RPAREN {$$ = $2;}
        ;

%%
