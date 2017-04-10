%{
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "ir.tab.h"
%}

/* avoid `input' and `yyunput' not used warnings */

%option noinput
%option nounput
%option yylineno

%%

"var"   return VAR;
"id"	return ID;
"@"		return AT;


"fun"   		return FUN;
"function"		return FUNCTION;

"i_call"		return I_CALL;
"call" 			return PROC_CALL;

"i_return"		return I_RETURN;
"return"		return PROC_RETURN;

"i_print" 		return I_PRINT;
"b_print"		return B_PRINT;

"i_value" 		return I_VALUE;

"i_lstore" 		return I_LSTORE;
"i_astore"		return I_ASTORE;
"i_gstore"		return I_GSTORE;


"i_lload"		return I_LLOAD;
"i_aload"		return I_ALOAD;
"i_gload"		return I_GLOAD;



"i_add"			return I_ADD;
"i_sub"			return I_SUB;
"i_div"			return I_DIV;
"i_mul"			return I_MUL;
"i_inv"			return I_INV;
"mod"			return MOD;


"i_eq"			return I_EQ;
"i_lt"			return I_LT;
"i_ne"			return I_NE;
"i_le"			return I_LE;
"i_ge"			return I_GE;
"i_gt"			return I_GT;
"not"			return NOT;


"i_copy"		return I_COPY;

"cjump" 		return CJUMP;
"jump"			return JUMP;

"int"			return INT;
"bool" 			return BOOL;
"void"			return VOID;

"("			return OPPAR;
")"			return CLPAR;
"["			return OPRPAR;
"]"			return CLRPAR;
":"     	return DQ;
";"			return SEMICOLON;
","			return COLON;

"<-"		return ASSIGN;

"true" {
	yylval.integer = 1;
	return BOOL_LITERAL;
}

"false" {
	yylval.integer = 0;
	return BOOL_LITERAL;
}

(t|fp)[0-9]+ {
	yylval.registers = strdup(yytext);
	return REGISTER;
}

l[0-9]+ {
	yylval.label = strdup(yytext);
	return LABEL;
}

[_a-zA-Z][_a-zA-Z0-9]*	{
	yylval.string = strdup(yytext);
	return IDENTIFIER;
}

[0-9]+		{
	yylval.integer = atoi(yytext);
	return INT_LITERAL;
}



#.*		; /* ignore comments */

[ \t\n]+	; /* and whitespace */

.		{
		  fprintf(stderr, "unrecognised character: `%c'\n", *yytext);

		  return ERROR;
		}
