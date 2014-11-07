%{
#include <iostream>
#include <map>
#include <math.h>

extern int yylex();
  void yyerror(const char * msg);
%}

%token CR
%token ASSIGN
%token PRINT
%token IDENT 
%token NUMBER
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
%left  NEG
%right EXPON

%nonassoc less_than_else
%nonassoc ELSE
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

line    : IDENT ASSIGN expr{$$ = 0;}
        | IDENT LPAREN parm_list RPAREN {$$ = 0;}
        | PRINT expr {$$ = 0;}
        | RETURN expr{$$ = 0;}
        ;

expr    : expr PLUS expr{$$ = $1 + $3;}
        | expr MINUS expr{$$ = $1 - $3;}
        | expr MULT expr {$$ = $1 * $3;}
        | expr EXPON expr {$$ = pow($1,$3);}
        | expr DIV expr 
	 { 
            if ($3) $$ = $1 / $3; 
            else {
              $$ = 1;
              std::cout << "Division by zero at line: "
                        << @3.first_line
                        << std::endl;}
            }
        | expr MOD expr {$$ = $1 % $3;}
        | expr LESS expr {$$ = $1 < $3;}
        | expr LESSEQ expr {$$ = $1 <= $3;}
        | expr GREAT expr {$$ = $1 > $3;}
        | expr GREATEQ expr {$$ = $1 >= $3;}
        | expr NOTEQ expr {$$ = $1 != $3;}
        | expr EQ expr {$$ = $1 = $3;}
        | MINUS expr %prec NEG {$$ = -$2;}
        | NUMBER { $$ = $1; }
        | FLOAT {$$ = 1;}
        | IDENT{$$ = 1;}
        | LPAREN expr RPAREN {$$ = $2;}
        ;

%%
void yyerror(const char * msg) { 
  std::cout << msg << " at line " << yylloc.first_line << std::endl; 
}
