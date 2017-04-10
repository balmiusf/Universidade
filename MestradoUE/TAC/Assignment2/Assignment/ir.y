%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
 
int yylex(void);
void yyerror(const char *); // see below

%}

%error-verbose

%union {
  char   	*string;
  int    	integer;
  char 		*registers;
  char 		*label;

 struct global_declarations *global_declarations;
 struct global_symbol *global_symbol;
 struct global_symbols *global_symbols;
 struct symbol_var *symbol_var;
 struct symbol_fun *symbol_fun;
 struct formal_args *formal_args;
 struct more_formal_args *more_formal_args;
 struct locals *locals;
 struct more_locals *more_locals;
 struct fundef *fundef;
 struct instructions *instructions;
 struct instruction *instruction;
 struct op *op;
 struct call_inst *call_inst;
 struct op_call *op_call;
 struct print *print;
 struct kind_load *kind_load;
 struct kind_store *kind_store;
 struct return_inst *return_inst;
 struct jumps *jumps;
 struct actual_args *actual_args;
 struct more_actual_args *more_actual_args;
 struct literal *literal;
 struct type *type;

};

%token FUN FUNCTION
%token OPPAR CLPAR OPRPAR CLRPAR ASSIGN AT

%token <integer> INT_LITERAL
%token <integer> BOOL_LITERAL
%token INT BOOL VOID
%token <string> IDENTIFIER
%token <registers> REGISTER
%token <label> LABEL
%token I_CALL  PROC_CALL
%token ID VAR 
%token I_PRINT  B_PRINT
%token I_LSTORE  I_ASTORE   I_GSTORE
%token I_ALOAD  I_LLOAD  I_GLOAD 
%token COLON SEMICOLON DQ
%token I_COPY
%token CJUMP JUMP
%token I_VALUE I_RETURN PROC_RETURN 

%left I_EQ I_LT I_NE I_LE I_GT I_GE
%left I_ADD I_SUB   
%left I_MUL  I_DIV  MOD
%nonassoc NOT I_INV


%token ERROR        // for signalling lexical errors

%type <global_symbols> global_symbols
%type <global_symbol> global_symbol
%type <global_declarations> global_declarations
%type <symbol_fun> symbol_fun
%type <symbol_var> symbol_var
%type <actual_args> actual_args
%type <more_actual_args> more_actual_args
%type <formal_args> formal_args
%type <more_formal_args> more_formal_args
%type <locals> locals
%type <print> print
%type <more_locals> more_locals
%type <fundef> fundef
%type <instructions> instructions
%type <instruction> instruction
%type <return_inst> return_inst
%type <op> op
%type <op_call> op_call
%type <call_inst> call_inst
%type <kind_store> kind_store
%type <kind_load> kind_load
%type <jumps> jumps
%type <literal> literal
%type <type> type


%%

ir_start:  global_symbols global_declarations		{start($1,$2); }
	; 		


global_declarations: 
        fundef global_declarations	{$$ = new_global_declarations($1,$2);}
    |   fundef 						{$$ = new_global_declarations($1,NULL);}
    ;

global_symbols:
        global_symbol global_symbols 			{$$ = new_global_symbols($1,$2);}
    |   global_symbol 							{$$ = new_global_symbols($1,NULL);}
    ;

global_symbol:
        symbol_var 								{$$ = new_global_symbol($1,NULL);}
    |   symbol_fun 								{$$ = new_global_symbol(NULL,$1);}
    ;

symbol_fun: 
        OPPAR ID AT IDENTIFIER FUN type OPRPAR formal_args CLRPAR OPRPAR locals CLRPAR CLPAR {$$ = new_symbol_fun($4,$6,$8,$11);}
    ;

formal_args : 
        OPPAR type AT IDENTIFIER CLPAR more_formal_args {$$ = new_formal_args($2,$4,$6);}
    |   /* empty */	{$$ = NULL;}
    ;

more_formal_args : 
        OPPAR type AT IDENTIFIER CLPAR more_formal_args {$$ = new_more_formal_args($2,$4,$6);}
    |   /* empty */	{$$ = NULL;}
    ;

locals:
        OPPAR type AT IDENTIFIER CLPAR more_locals 	{$$ = new_locals($2,$4,$6);}
    |   /* empty */ {$$ = NULL;}
    ;

more_locals : 
        OPPAR type AT IDENTIFIER CLPAR more_locals {$$ = new_more_locals($2,$4,$6);}
    |   /* empty */ {$$ = NULL;}
    ;

symbol_var: 
    OPPAR ID AT IDENTIFIER VAR type CLPAR 				{$$ = new_symbol_var($4,$6,NULL);}
  | OPPAR ID AT IDENTIFIER VAR type literal CLPAR 		{$$ = new_symbol_var($4,$6,$7);}
  ;

fundef:
   		FUNCTION AT IDENTIFIER instructions	{$$ = new_fundef($3,$4);}
    ;

instructions:
        instruction instructions 		{$$ = new_instructions($1,$2);}
    |  	/* instruction (was here before) */ {$$ = NULL;}
    ;

instruction:
        REGISTER ASSIGN op REGISTER COLON REGISTER {$$ = new_instruction_binop($1,$3,$4,$6);}
    |	REGISTER ASSIGN op literal {$$ = new_instruction_unop_lit($1,$3,$4);}
    |   REGISTER ASSIGN op REGISTER {$$ = new_instruction_unop($1,$3,$4);}

    |   REGISTER ASSIGN kind_load AT IDENTIFIER  {$$ = new_instruction_load($1,$3,$5);}
    |   AT IDENTIFIER ASSIGN kind_store REGISTER {$$ = new_instruction_store($2,$4,$5);}
    
    |   jumps {$$ = new_instruction_jump($1);}
    |   call_inst {$$ = new_instruction_call($1);}
    |   print {$$ = new_instruction_print($1);}
    | 	return_inst {$$ = new_instruction_return($1);}
    |   LABEL DQ instruction {$$ = new_instruction_label($1,$3);}
    ;	

op:
        I_ADD 	{$$ = new_op(I_ADD_);}
    |   I_SUB   {$$ = new_op(I_SUB_);}
    |   I_DIV	{$$ = new_op(I_DIV_);}
    |   I_MUL	{$$ = new_op(I_MUL_);}
    |   I_INV	{$$ = new_op(I_INV_);}
    |   MOD		{$$ = new_op(MOD_);}
    |   I_LT 	{$$ = new_op(I_LT_);}
    |   I_EQ 	{$$ = new_op(I_EQ_);}
    | 	I_NE 	{$$ = new_op(I_NE_);}
    |	I_LE 	{$$ = new_op(I_LE_);}
    |   NOT 	{$$ = new_op(NOT_);}
    |   I_COPY 	{$$ = new_op(I_COPY_);}
    |	I_VALUE	{$$ = new_op(I_VALUE_);}
    ;

call_inst:
        REGISTER ASSIGN op_call AT IDENTIFIER COLON OPRPAR actual_args CLRPAR {$$ = new_call_inst_fun($1,$3,$5,$8);}
    |	REGISTER ASSIGN op_call AT IDENTIFIER COLON OPRPAR CLRPAR {$$ = new_call_inst_fun($1,$3,$5,NULL);}
    |   op_call AT IDENTIFIER COLON OPRPAR actual_args CLRPAR {$$ = new_call_inst_proc($1,$3,$6);}
    |   op_call AT IDENTIFIER COLON OPRPAR CLRPAR {$$ = new_call_inst_proc($1,$3,NULL);}
    ;

op_call:
        I_CALL 		{$$ = new_op_call(I_CALL_);}
    |   PROC_CALL   {$$ = new_op_call(PROC_CALL_);}
    ;

print:
        I_PRINT REGISTER 		{$$ = new_print(I_PRINT_,$2);}
    |   B_PRINT REGISTER 		{$$ = new_print(B_PRINT_,$2);}
    ;

kind_load:
        I_ALOAD 	{$$ = new_kind_load(I_ALOAD_);}		
    |   I_LLOAD 	{$$ = new_kind_load(I_LLOAD_);}	
    |   I_GLOAD		{$$ = new_kind_load(I_GLOAD_);}	
    ;

kind_store:
        I_ASTORE 			{$$ = new_kind_store(I_ASTORE_);}
    |   I_LSTORE			{$$ = new_kind_store(I_LSTORE_);}
    |   I_GSTORE			{$$ = new_kind_store(I_GSTORE_);}
    ;

return_inst:
        I_RETURN REGISTER 	{$$ = new_return_inst(I_RETURN_,$2);}
    |   PROC_RETURN 		{$$ = new_return_inst(PROC_RETURN_,NULL);}
    ;
    
jumps:
        CJUMP REGISTER COLON LABEL COLON LABEL 		{$$ = new_cjump($2,$4,$6);}
    |   JUMP LABEL 		{$$ = new_jump($2);}
    ;

actual_args : REGISTER more_actual_args 			{$$ = new_actual_args($1,$2);}
      ;

more_actual_args : COLON REGISTER more_actual_args 	{$$ = new_more_actual_args($2,$3);}
     | /* empty */ 	{$$ = NULL;}
     ;

literal:
   	INT_LITERAL 		{$$ = new_literal_int($1);}		
  | BOOL_LITERAL 		{$$ = new_literal_bool($1);}
  ;

type:
      INT 				{$$ = new_type(INT_);}
    | BOOL 				{$$ = new_type(BOOL_);}
    | VOID 				{$$ = new_type(VOID_);}
    ;

%%

/* called when there is a syntax error */
void yyerror(const char *msg)
{
    extern int yylineno;     
    fprintf(stderr, "error: %s\n " , msg);
    fprintf(stderr, "Syntax error at line %d\n",yylineno); // TELL ME EXACTLY WHERE THE ERROS ARE
}

int main()
{
  return yyparse();
}
