%{
#include <iostream>
#include <cmath>    
#include <map>
#include <math.h>
#include <ostream>
#include "ast.h"   
extern std::fstream output;
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
%token <num>NUMBER
%token <dub>FLOAT
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

start   : start funcdef { 
                           try
                    	   {
                    	        eval(new AstStart('a',$2));

                  
                              makeGraph(new AstStart('a', $2),output);
                              //treeFree($1);
                              
                              
                    	   }
                    	   catch (const std::string& msg) 
                    	   {
                    	       std::cout << msg << std::endl; 
                    	   } 
                               
                         }
        | { ; } 
        ;
     

funcdef : DEF IDENT LPAREN parm_list RPAREN COLON stmt END {$$ = new AstFuncdef('b', $2,$4,$7); yyerrok;}
        | CR {$$ = 0;}
        ;           

parm_list 
        : expr COMMA parm_list {$$ = new AstNode('c',$1,$3);}
        | expr {$$ = new AstNode('d',$1, NULL);}
        | {$$ = 0;}
        ;

stmt    : line stmt {$$ = new AstNode('s',$$ = new AstNode('i',$1,NULL),$2);}
        | selection stmt {$$ = new AstNode('f',$$ = new AstNode('t',$1,NULL),$2);}
        | CR stmt{ $$ = new AstNode('s',$2,NULL); } 
        | {$$=0;}
        ;

selection 
        : IF expr COLON stmt %prec less_than_else END {$$ = new AstIf('j',$2,$4);}
        | IF expr COLON stmt ELSE COLON stmt END {$$ = new AstElse('n',$2,$4,$7);}
        ;

line    : IDENT ASSIGN expr {$$ = new AstAssign('=',$1,$3);
                              std::cout<< "the Ident is:" << $1 << " the num is :"<< eval($3)<<std::endl;
                            }
        | IDENT LPAREN parm_list RPAREN { $$ = 0; }
        | PRINT expr { $$ = new AstNode('p',$2,NULL);
                        //std::cout << "PRINTING: " << eval($2) << std::endl;
                     } 
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
        | NUMBER {$$ = new AstNumber('K', $1); 
                      std::cout << "NUMBER IS: " << $1 << std::endl;
                   }
        | FLOAT {$$ = new AstNumber('F', $1); 
                      std::cout << "NUMBER FLOAT IS: " << $1 << std::endl;
                   }
        | IDENT { $$ = new AstIdent('I', $1);
                  //std::cout << "IDENT IS: " << $1 << std::endl;
                }
        | LPAREN expr RPAREN {$$ = $2;}
        ;

%%
