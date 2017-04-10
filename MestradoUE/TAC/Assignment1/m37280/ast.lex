%{
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include "ast.tab.h"
%}

/* avoid `input' and `yyunput' not used warnings */

%option noinput
%option nounput
%option yylineno

%%

"var"   return VAR;
"arg"   return ARG;
"local" return LOCAL;
"id"	return ID;
"assign" return ASSIGN;

"body" 	return BODY;
"fun"   return FUN;
"call" 	return CALL;
"print" return PRINT;

"if" 	return IF;
"while" return WHILE;

"or" 	return OR;
"and" 	return AND;
"eq" 	return EQ;
"ne" 	return NE;
"lt" 	return LT;
"le" 	return LE;
"gt" 	return GT;
"ge" 	return GE;

"plus" 	return PLUS;
"minus" return MINUS;
"times" return TIMES;
"div" 	return DIV;
"mod" 	return MOD;
"not" 	return NOT;
"inv" 	return INV;

"int"			return INT;
"int_literal" 	return INT_LITERAL;

"real" 			return REAL;
"real_literal" 	return REAL_LITERAL;

"bool" 		return BOOL;
"toreal" 	return TOREAL;

"nil" 		return NIL;

"("			return OPPAR;
")"			return CLPAR;
"["			return OPRPAR;
"]"			return CLRPAR;
":"     	return COLON;

"true" {
	yylval.integer = 1;
	return BOOL_LITERAL;
}

"false" {
	yylval.integer = 0;
	return BOOL_LITERAL;
}

\"[_a-zA-Z][_a-zA-Z0-9]*\"	{
	yylval.string = strdup(yytext);
	return IDENTIFIER;
}


[0-9]*\.[0-9]+ {
	yylval.real = atof(yytext);
	return REAL_LITERAL_VALUE;
}

[0-9]+		{
	yylval.integer = atoi(yytext);
	return INT_LITERAL_VALUE;
}



#.*		; /* ignore comments */

[ \t\n]+	; /* and whitespace */

.		{
		  fprintf(stderr, "unrecognised character: `%c'\n", *yytext);

		  return ERROR;
		}
