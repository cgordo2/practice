%{
#include <iostream>
#include <cstring>
#include <string>
#include "ast.h"
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
		yylval.id = new char[strlen(yytext)+1];
  		strcpy(yylval.id, yytext);
  		return IDENT; }

{float}    { 
             return FLOAT; 
           }
{digits}   { 
			yylval.dub = atoi(yytext);
             return NUMBER; 
           }
"#"[^\n]*  { ; }
"\n"	   { yylineno++; return CR; }
.          { ; }

%%
int yywrap() {
   yylex_destroy();
  return 1;}
