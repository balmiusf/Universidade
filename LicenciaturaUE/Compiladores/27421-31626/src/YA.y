%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "apt.h"

int yylex (void);
void yyerror (char const *);

enum type_kind lookup_type(char *id);
void table_insert_1(char *id, type type);
void table_insert_2(belos_ids ids, type type);
void insertFunc(funcdeclar funcdeclar, type type);

%}

%union {
	int val;
    char *id;
    float valfloat;
    char *str;
    bool booleano;
    struct nl *nl;
    struct Id *id_2;
    struct ids *ids;
	struct calc_exp *CExp;
	struct op *op;
	struct type *type;
	struct stmts *stmts;
	struct corpo *corpo;
	struct corpo_cycle *corpo_cycle;
	struct Corpo_cond *corpo_cond;
	struct decl *decl;
	struct decl1 *decl1;
	struct decl2 *decl2;
	struct ifs *ifs;
	struct afect *afect;
	struct afects *afects;
	struct funcdeclar *funcdeclar;
	struct funcdeclar2 *funcdeclar2;
	struct whiles *whiles;
	struct expBools *expBools;
	struct decls *decls;
	struct literalExp *literalExp;
	struct funcCall *funcCall;
}

/* Bison declarations.  */
%token	<id>		ID
%token	<val>		NUM_LIT
%token 	<valfloat>  NUM_FLOAT_LIT
%token  <str>		STRING_LIT
%token <booleano>	BOOL_LIT


%token NL /* newline */
%token INT FLOAT BOOL STRING VOID


%token DEFINE
%left EQUALS LESSOREQUAL LESSTHAN DIFFERENTTHAN EQUALLESSTHAN EQUALMORETHAN MORETHAN
%token POINT COMMA DOUBLEPOINT END_OF_STMT

%token DO WHILE

%token BREAK NEXT RETURN

%token AND OR NOT		// check with prof (ordenacao)

%right			ASSIGN
%left			SUB SUM 
%left			MUL DIV MOD
%right			POT
%left			NEG     /* negation--unary minus */

%token  LCURLYPAR RCURLYPAR LPAR RPAR LRECTPAR RRECTPAR
%token IF ELSE THEN

%type 	<funcCall>		funcCall
%type	<CExp>			exp
%type 	<decls>			decls
%type 	<decl>			decl
%type 	<ifs>			ifs
%type 	<whiles>		whiles
%type   <decl1>			decl1
%type  	<decl2>			decl2
%type 	<corpo>			corpo
%type 	<corpo_cycle>	corpo_cycle
%type 	<stmts>			stmts
%type 	<funcdeclar>	funcdeclar
%type   <funcdeclar2>	funcdeclar2
%type 	<afect>			afect
%type 	<afects>		afects
%type 	<ids>			ids
%type 	<type>			type
%type 	<expBools>		expBools
%type 	<op>			op
%type 	<literalExp>	literalExp
%%

input: 	/* empty */
		 decls 				{printf("END\n");}
;

decls:  
													
		  decls decl								{$$ = new_decls($2,$1); printf("DECL DECLS\n");}
		|  decl 									{$$ = new_decls($1,NULL);printf("DECL ;\n");}
;

decl: 	 
		 decl2 								{$$ = new_decl_func($1);printf("DECL2\n");}
		| decl1									{$$ = new_decl_normal($1);printf("DECL1\n");}
;

ifs:	 IF expBools THEN LCURLYPAR corpo RCURLYPAR ELSE LCURLYPAR corpo RCURLYPAR		{$$ = new_ifs($2,$5,$9);printf("IF_ELSE_THEN\n");}

		| IF expBools THEN LCURLYPAR corpo RCURLYPAR									{$$ = new_ifs($2,$5,NULL);printf("IF_ELSE\n");}
;

whiles:	 WHILE expBools DO LCURLYPAR corpo_cycle RCURLYPAR							{$$ = new_whiles($2,$5);printf("WHILE\n");}
;

decl1:	 ids DOUBLEPOINT type END_OF_STMT												{$$ = new_decl1_wo_type($1,$3); table_insert_2($1,$3); printf("IDS : TYPE\n");}
		| ids DOUBLEPOINT type ASSIGN exp END_OF_STMT									{$$ = new_decl1_type($1,$3,$5); table_insert_2($1,$3);printf("IDS : TYPE = EXP\n");}
		| DEFINE ID type END_OF_STMT													{$$ = new_decl1_define($2,$3);table_insert_1($2,$3);printf("DEFINE ID TYPE\n");}
		| ID LRECTPAR exp RRECTPAR type	END_OF_STMT											{$$ = new_decl1_array($1,$3,$5);printf("ID[EXP]\n");}
		| ID LRECTPAR RRECTPAR type		END_OF_STMT											{$$ = new_decl1_array($1,NULL,$4);printf("ID[]\n");}
;

decl2: funcdeclar DOUBLEPOINT type LCURLYPAR corpo RCURLYPAR END_OF_STMT						{$$ = new_decl2($1,$3,$5);insertFunc($1,$3);printf("FUNCAO\n");}
;

corpo: 	  stmts																		{$$ =  new_corpo($1,NULL);printf("STMTS\n");}		
		| stmts corpo																{$$ = new_corpo($1,$2); printf("STMTS CORPO\n");}													
;

corpo_cycle:  stmts 						{$$ = new_corpo_cycle($1);}
			| BREAK	END_OF_STMT				{$$ = new_corpo_cycle_break(BREAK_);printf("BREAK\n");}
			| NEXT	END_OF_STMT				{$$ = new_corpo_cycle_next(NEXT_);printf("NEXT\n");}
;

stmts:    decl1 											{$$ = new_stmts_decl($1);		printf("STMTS -> DECL1\n");}
		| ifs END_OF_STMT									{$$ = new_stmts_cond($1);		printf("STMTS -> IFS\n");}
		| whiles END_OF_STMT								{$$ = new_stmts_cycle($1);		printf("STMTS -> WHILE\n");}
		| RETURN exp END_OF_STMT 							{$$ = new_stmts_return($2);		printf("STMTS -> RETURN\n");}
		| afect 											{$$ = new_stmts_afect($1);		printf("STMTS -> AFECT\n");}
		| funcCall	END_OF_STMT								{$$ = new_stmts_funcCalls($1);	printf("STMTS -> FUNC CALL\n");}
;

funcCall: ID LPAR RPAR 						{$$ = new_function_calls_no_args($1);printf("FUNC_CALL_NO_ARGS\n");}
		| ID LPAR ids RPAR 					{$$ = new_function_calls_args($1,$3);printf("FUNC_CALL_ARGS\n");}
		| ID LPAR exp RPAR 					{$$ = new_function_calls_exp($1,$3);printf("FUNC_CALL_EXPS\n");}
		| ID LPAR funcCall RPAR 			{$$ = new_function_calls_func($1,$3);printf("FUNC_CALL_FUNC\n");}
;

funcdeclar:	ID LPAR ID DOUBLEPOINT type funcdeclar2  		{$$ = new_func_args($1,$3,$5,$6);printf("FUNCTION_WITH_ARGS\n");}
			| ID LPAR RPAR 										{$$ = new_func_no_args($1);printf("FUNCTION_NO_ARGS\n");}
;
	
funcdeclar2:  RPAR											{$$ = NULL;}				
			| COMMA ID DOUBLEPOINT type funcdeclar2				{$$ = new_func_args_2($2,$4,$5);printf("FUNC DECLAR 2\n");}
;

afect: 	 ID EQUALS afects END_OF_STMT							{$$ = new_afect($1,$3);printf("1 - ID = AFECTS\n");}
;

afects:	 ID EQUALS afects										{$$ = new_afects($1,$3);printf("2 - ID = AFECTS\n");}
		| exp 													{$$ = new_afects_end($1);printf("AFECTS - EXP\n");}
;

ids:	 ID 											{$$ = new_ids_solo($1);printf("ID\n");}
		| ID COMMA ids									{$$ = new_ids_more($1,$3);printf("MULTIPLE IDS\n");}
;

type:	 INT 											{$$ = new_type(INTEGER_);printf("INT\n");}															
		| BOOL											{$$ = new_type(BOOLEAN_);printf("BOOL\n");}							
		| STRING										{$$ = new_type(STRING_);printf("STRING\n");}							
		| VOID											{$$ = new_type(VOID_);printf("VOID\n");}							
		| FLOAT											{$$ = new_type(FLOATING_);printf("FLOAT\n");}
;

expBools:	exp op exp 							{$$ = new_exp_bools_1($1,$2,$3);printf("EXP OP EXP\n");}
		|	ID 									{$$ = new_exp_bools_id($1);printf("EXPBOOLS ID\n");}
		|   ID op exp 							{$$ = new_exp_bools_id_exp($1,$2,$3);printf("ID op EXP\n");}
		| 	ID op ID 							{$$ = new_exp_bools_id_exp_2($1,$2,$3);printf("ID op ID\n");}
		|	exp op expBools						{$$ = new_exp_bools_2($1,$2,$3);printf("EXP OP BOOLS EXP\n");}
		|	NOT expBools 						{$$ = new_exp_bools_not($2);printf("NOT EXP BOOLS\n");}
		|	LPAR expBools RPAR 					{$$ = new_exp_bools_par($2);printf("( EXP BOOLS )\n");}
;

op:		EQUALS 							{$$ = new_op(EQUALS_);printf("equals\n");}											
	|	DIFFERENTTHAN 					{$$ = new_op(DIFFERENTTHAN_);printf("!=\n");}												
	|	LESSTHAN 						{$$ = new_op(LESSTHAN_);printf("<\n ");}											
	|	MORETHAN 						{$$ = new_op(MORETHAN_);printf(">\n");}									
	|	EQUALLESSTHAN 					{$$ = new_op(EQUALESSTHAN_);printf("<=\n");}												
	|	EQUALMORETHAN 					{$$ = new_op(EQUALMORETHAN_);printf(">=\n");}												
	|	AND 							{$$ = new_op(AND_);printf("and\n");}													
	|	OR 								{$$ = new_op(OR_);printf("or\n");}									
;

literalExp: 		NUM_LIT 			{$$ = new_literal_int($1);printf("INT_LIT\n");}
				|	NUM_FLOAT_LIT 		{$$ = new_literal_float($1);printf("FLOAT_LIT\n");}
				|	STRING_LIT			{$$ = new_literal_string($1);printf("STRING_LIT\n");}
				|	BOOL_LIT			{$$ = new_literal_bool($1);printf("BOOL_LIT\n");}
;

exp:   
		 	exp SUM exp        		{ $$ = calc_exp_new_binop("+",$1,$3);printf("exp + exp\n");} 	
        | 	exp SUB exp        		{ $$ = calc_exp_new_binop("-",$1,$3);printf("exp - exp\n");} 	
        | 	exp MUL exp        		{ $$ = calc_exp_new_binop("*",$1,$3);printf("exp * exp\n");} 	
        | 	exp DIV exp        		{ $$ = calc_exp_new_binop("/",$1, $3);printf("exp / exp\n");}	
		|	exp POT exp	   			{ $$ = calc_exp_new_binop("^",$1,$3);printf("exp ^ exp\n");} 	
        | 	SUB exp  %prec NEG 		{ $$ = calc_exp_new_binop("-",0,$2);printf(" - exp \n");} 	
        | 	LPAR exp RPAR      		{ $$ = calc_exp_new_par($2);printf( "( exp ) \n");} 			
        |   literalExp 				{ $$ = calc_exp_new_literal($1);printf("FOUND LITERAL\n");}		
;	

%%

	/*
	*
	*
	*			SYMBOL TABLE
	*
	*
	*/

struct node{
	char *id;
	enum type_kind kind;
	int ocupado;
};


struct node table[267];	// hashtable
int size = 0;

int hash(char word[], int size)
{

  	int h = 0;
 	int i = 0;

  	while (word[i] != '\0')
  	{
      	h += word[i];
      	i++;
  	}
  	int c;
  	if(size == 0)
  		c = 0;
  	else
  		c = h % size;
 // 	printf("%d\n", h % size);
  return c;
}


enum type_kind lookup_type(char *id)
{
	int h = hash(id,size);


	while(true)
	{
		if(table[h].ocupado  == 1 &&
			strcmp(id,table[h].id) == 0)
		{
			return table[h].kind;
		}
		else
		{
			h = 0;
			while(table[h].ocupado != 1)
			{
				h++;
				h%= 267;
			}
		}
	}

	return 0;	// no symbol was found
}

void table_insert_1(char *id, type type){
	int h = hash(id,size);

	while(true)
	{
		if(table[h].ocupado  == 0)
		{
			table[h].id = strdup(id);
			table[h].kind = type->kind;
			table[h].ocupado = 1;
			break;
		}

		else{
			h = 0;
			while(table[h].ocupado != 1)
			{
				h++;
				h%= 267;
			}
		}
	}

	size++;
}


// declaracoes do genero, a,b,c,d,e : int;
void table_insert_2( belos_ids ids,type type)
{
	belos_ids root = ids;

	while(root != NULL)
	{
		table_insert_1(root->u.many_ids.id,type);
		root = root->u.many_ids.more_ids;
	}
}

void insertFunc(funcdeclar funcdeclar, type type){
	table_insert_1(funcdeclar->u.id,type);

}

void table_remove(char *id, type type){
	int h = hash(id,size);

	while(true){
		if(table[h].ocupado  == 1 && strcmp(table[h].id,id)==0 
			&& type->kind == table[h].kind)
		{
			table[size].ocupado = 0;
			break;
		}
		else if(table[h].ocupado == 1 && strcmp(table[h].id,id)!=0)
		{
			h = 0;
			while(table[h].ocupado != 1)
			{
				h++;
				h%= 267;
			}
		}
		else
			break; // no symbol was found
	}
	size--;
}


void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}


int main (void)
{
  return yyparse();
}
