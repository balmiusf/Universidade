%{
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>
	#include "parser.h"

	void count();
%}


ID [a-zA-Z][a-zA-Z0-9_]*
INT [0-9]*
INT_FLOAT [0-9]*\.[0-9]+([eE][\+\-]?[0-9]+)? 
BOOL "true"|"false"
STRING \"[a-zA-Z0-9_].*\"

%%



"int"		{count();return INT;}
"float"		{count();return FLOAT;}
"bool"		{count();return BOOL;}
"string"	{count();return STRING;}
"void"		{count();return VOID;}

";" 	{count();return END_OF_STMT;}
"("		{count();return LPAR;}
")"		{count();return RPAR;}
"["		{count();return LRECTPAR;}
"]"		{count();return RRECTPAR;}
"{"		{count();return LCURLYPAR;}
"}"		{count();return RCURLYPAR;}
"."		{count();return POINT;}
","		{count();return COMMA;}
":"		{count();return DOUBLEPOINT;}
"="		{count();return ASSIGN;}

"+"		{count();return SUM;}
"-"		{count();return SUB;}
"*"		{count();return MUL;}
"/"		{count();return DIV;}
"mod"	{count();return MOD;}
"^"		{count();return POT;}

"==" 		{count();return EQUALS;}
"!="		{count();return DIFFERENTTHAN;}
"<"		{count();return LESSTHAN;}
">"		{count();return MORETHAN;}
"<="		{count();return EQUALLESSTHAN;}
">="		{count();return EQUALMORETHAN;}

"and"		{count();return AND;}
"or"		{count();return OR;}		
"not" 		{count();return NOT;}

"return" 	{count();return RETURN;}
"break"		{count();return BREAK;}
"next"		{count();return NEXT;}
"define"	{count();return DEFINE;}
"if"		{count();return IF;}
"then"		{count();return THEN;}
"else"		{count();return ELSE;}
"while"		{count();return WHILE;}
"do"		{count();return DO;}
[ \v\f]		{ count(); }

{BOOL}		{yylval.booleano = strdup(yytext); return BOOL_LIT;}

{ID}		{yylval.id = strdup(yytext); return ID;		}
{INT_FLOAT} 	{yylval.valfloat = atof(yytext); return NUM_FLOAT_LIT;		}
{INT}    	{yylval.val = atof(yytext); return NUM_LIT; 	}
{STRING}	{yylval.str  = strdup(yytext)	; return STRING_LIT;	}

[\n\t]			{ /* ignore bad characters */ }

%%

int yywrap()
{
	return(1);
}

// remove later
void count()
{
	int a = 1;
}