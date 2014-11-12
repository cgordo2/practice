%{
#define YYSTYPE double
#include "parse.tab.h"
#include <stdlib.h>
#include <string>
extern std::string textvalues;
%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

%%

{white} { }
{real} { yylval=atof(yytext); textvalues=textvalues+yytext;
 return NUMBER;
}

"+" {textvalues=textvalues+"+"; return PLUS;}
"-" { textvalues=textvalues+"-";return MINUS;}
"**" {textvalues=textvalues+"**";return POWER;}
"*" {textvalues=textvalues+"*";return TIMES;}
"/" {textvalues=textvalues+"/";return DIVIDE;}
"(" {textvalues=textvalues+"(";return LEFT;}
")" {textvalues=textvalues+")";return RIGHT;}
"\n" {textvalues=textvalues+"\t";return END;}
%%
int yywrap() {
  yylex_destroy();
  return 1;
}
