%{
#define YYSTYPE double
#include "parse.tab.h"
#include <stdlib.h>
%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

%%

{white} { }
{real} { yylval=atof(yytext); 
 return NUMBER;
}

"+" return PLUS;
"-" return MINUS;
"**" return POWER;
"*" return TIMES;
"/" return DIVIDE;

"(" return LEFT;
")" return RIGHT;
"\n" return END;
%%
int yywrap() {
  yylex_destroy();
  return 1;
}
