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

start   : start funcdef {$$ = new StartNode($2); $$->eval();}
        | { ; } 
        ;

funcdef : DEF IDENT LPAREN parm_list RPAREN COLON stmt END {$$ = new FuncdefNode($2,$4,$7); yyerrok;}
        | CR {$$ = 0;}
        ;           

parm_list 
        : expr COMMA parm_list {$$ = new ParmNode($1,$3);}
        | expr {$$ = new ExpressNode($1);}
        |{$$ = 0;}
        ;

stmt    : line stmt {
            if ( $1 ) {
              std::cout << "LINE STMT $1 is eval to: " << $1->eval() << std::endl;
              $$ = new StmtNode($1);
            }
            else std::cout << "Darn $1 is NULL" << std::endl;
          }
        | selection stmt {$$ = new SelectNode($1,$2);}
        | CR stmt{
            if ($2 == NULL) {
              std::cout << "$2 is NULL in CR stmt" << std::endl;
              $$ = $2;
            }
            else $$ = new StmtNode($2); 
          }
        |   {$$=0;}
        ;

selection 
        : IF expr COLON stmt %prec less_than_else END {$$ = new IfNode($2,$4);}
        | IF expr COLON stmt ELSE COLON stmt END{$$ = new ElseNode($2,$4,$7);}
        ;

line    : IDENT ASSIGN expr {$$ = new AssignNode (new IdentNode($1), $3);} //{table[$1] = $3->eval();}
        | IDENT LPAREN parm_list RPAREN {$$ = new FuncNode($1,$3);}//{$$ = 0;} //function node
        | PRINT expr {
            std::cout << "PRINTING: " << $2->eval() << std::endl;
            $$ = new PrintNode($2); 
          } //printing  out 
        | RETURN expr{$$ = 0;}
        | CR expr { 
            std::cout << "Tracking, $2 is: " << $2->eval() << std::endl;
            //$$ = $2;
            $$ = new ExpressNode($2);
          }
        ;

expr    : expr PLUS expr { $$ = new AddBinaryNode($1, $3); }
        | expr MINUS expr{ $$ = new SubBinaryNode($1, $3); }
        | expr MULT expr { $$ = new MulBinaryNode($1, $3); }
        | expr EXPON expr { $$ = new ExpBinaryNode($1, $3); }
        | expr DIV expr  { $$ = new DivBinaryNode($1, $3);}
        | expr MOD expr { $$ = new ModBinaryNode($1, $3); }
        | expr LESS expr {$$ = new LessBinaryNode($1, $3);}//{$$=0;}
        | expr LESSEQ expr {$$ = new LessEQBinaryNode($1, $3);}//{$$=0;}
        | expr GREAT expr {$$ = new GreatBinaryNode($1, $3);}//{$$=0;}
        | expr GREATEQ expr{$$ = new GreatEQBinaryNode($1, $3);}//{$$=0;}
        | expr NOTEQ expr {$$ = new NotEQBinaryNode($1, $3);}//{$$=0;}
        | expr EQ expr {$$ = new EQBinaryNode($1, $3);}//{$$=0;}
        | MINUS expr { $$ = new UnaryMinusNode($2);}
        | NUMBER { 
            $$ = new NumberNode($1);        
            std::cout << "NUMBER IS: " << $1 << std::endl;
          }
        | IDENT { $$ = new IdentNode($1);}
        | LPAREN expr RPAREN {$$ = $2;}
        ;

%%
