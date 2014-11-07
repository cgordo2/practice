%{
#include <iostream>
#include <cstring>

#include "parse.tab.h"

%}

letter      [a-zA-Z]
ident       {letter}({letter}|{digit})*
digit       [0-9]
digits      [0-9]+
float       {digits}"."{digits}

%%

"**"       { return EXPON; }
"="        { return ASSIGN; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"*"        { return MULT; }
"/"        { return DIV; }
"%"        { return MOD; }
"("        { return LPAREN; }
")"        { return RPAREN; }
":"        { return COLON; }
","        { return COMMA; }
"<"        { return LESS; }
">"        { return GREAT; }
"<="       { return LESSEQ; }
">="       { return GREATEQ; }
"=="       { return EQ; }
"!="       { return NOTEQ; }
"if"       { return IF; }
"else"     { return ELSE; }
"def"      { return DEF; }
"print"    { return PRINT; }
"end"      { return END; }
"return"   { return RETURN; }

{ident}    { 
	     return IDENT; }

{float}    { 
             return FLOAT; 
           }
{digits}   { 
             return NUMBER; 
           }
"#"[^\n]*  { 
	     ; }
"\n"	   {//LCOV_EXCL_LINE
		++yylloc.first_line; 
		return CR; }
.          { ; }

%%//LCOV_EXCL_LINE
int yywrap() {//LCOV_EXCL_LINE
  yylex_destroy();
  return 1;
}
