%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tacl_ir.h"
    
    int yylex(void);
    void yyerror(const char *);	// see below
    
%}

%union 
{
    char   *string;
    int    integer;
    double real;

    struct global_declaration *global_declaration;
    struct global_declarations *global_declarations;
    struct atomic_expression *atomic_expression;
    struct expression *expression;
    struct conditional *conditional;
    struct more_vardecls *more_vardecls;
    struct vardecls *vardecls;
    struct stmt *stmt;
    struct stmts *stmts;
    struct body *body_fun;
    struct id *id_;
    struct type *type;
    struct kind *kind;
    struct operator *operator;
    struct fundef *fundef;
    struct function_call *function_call;
    struct actual_args *actual_args;
    struct more_actual_args *more_actual_args;
    struct literal *literal;
    struct formal_args *formal_args;
    struct more_formal_args *more_formal_args;
    struct ast *ast;
    
};

%token FUN VAR ARG LOCAL
%token BODY
%token OPPAR CLPAR OPRPAR CLRPAR COLON

%token <integer> INT_LITERAL_VALUE
%token <real> REAL_LITERAL_VALUE
%token <integer> BOOL_LITERAL
%token INT REAL BOOL TOREAL
%token <string> IDENTIFIER

%token ID
%token INT_LITERAL REAL_LITERAL
%token TYPE 
%token ASSIGN
%token WHILE PRINT CALL
%token IF ELSE
%token NIL



%left OR
%left AND
%left EQ NE LT LE GT GE
%left PLUS MINUS 
%left TIMES DIV MOD

%nonassoc NOT INV

%token ERROR        // for signalling lexical errors

%type <ast> ast
%type <global_declarations> global_declarations
%type <global_declaration> global_declaration
%type <vardecls> vardecls
%type <more_vardecls> more_vardecls
%type <expression> expression
%type <conditional> conditional
%type <stmt> statement
%type <stmts> statements
%type <body_fun> body_fun
%type <id_> id_
%type <type> type
%type <kind> kind
%type <operator> operator
%type <fundef> fundef
%type <function_call> function_call
%type <actual_args> actual_args
%type <more_actual_args> more_actual_args
%type <formal_args> formal_args
%type <more_formal_args> more_formal_args
%type <literal> literal
%type <atomic_expression> atomic_expression

%%

ast: 
        global_declarations                                     {the_root($1);}    
    ;

global_declarations : 
        global_declaration global_declarations                  {$$ = new_global_declarations($1,$2);}      
    |   global_declaration                                      {$$ = new_global_declarations($1, NULL);}
    ;

global_declaration:
        vardecls                                                {$$ = new_global_declaration_decl($1);}
    |   fundef                                                  {$$ = new_global_declaration_fun($1);}   
    ;

vardecls:
     OPPAR VAR OPPAR id_ CLPAR expression CLPAR                 {$$ = new_vardecls($4,$6);}
    ;

kind:   
        VAR                 {$$ = new_kind(VAR_);}
    |   LOCAL               {$$ = new_kind(LOCAL_);}
    |   ARG                 {$$ = new_kind(ARG_);}
    ;

type:
        BOOL                {$$ = new_type(BOOL_);}
    |   INT                 {$$ = new_type(INT_);}
    |   REAL                {$$ = new_type(REAL_);} 
    ;   

fundef: 
        OPPAR FUN IDENTIFIER OPRPAR formal_args CLRPAR OPPAR BODY body_fun CLPAR CLPAR  {$$ = new_fundef($3,$5,$9);}
    ;

formal_args:
        OPPAR ARG IDENTIFIER type CLPAR more_formal_args                                {$$ = new_formal_args($3,$4,$6);}
    |   /* empty */  {$$ = NULL;}
    ;

more_formal_args:
        OPPAR ARG IDENTIFIER type CLPAR more_formal_args                                {$$ = new_more_formal_args($3,$4,$6);}
    |   /* empty */  {$$ = NULL;}
    ;

body_fun:
        OPRPAR more_vardecls CLRPAR statement expression                                    {$$ = new_body($2,$4,$5);}
    |   OPRPAR CLRPAR statement expression                                                  {$$ = new_body(NULL,$3,$4);}
    |   OPRPAR CLRPAR NIL expression                                                        {$$ = new_body(NULL,NULL,$4);}
    |   /* empty */  {$$ = NULL;}
    ;

more_vardecls:
        vardecls                                                                        {$$ = new_more_vardecls($1,NULL);}
    |   vardecls more_vardecls                                                          {$$ = new_more_vardecls($1,$2);}
    ;

statement:
        OPRPAR statements CLRPAR    /* compound statement */                            {$$ = new_stmt($2);}
    |   OPPAR WHILE expression statement CLPAR      /* loop */                          {$$ = new_stmt_loop($3,$4);}                             
    |   conditional                                                                     {$$ = new_stmt_cond($1);}
    |   OPPAR ASSIGN OPPAR id_ CLPAR expression CLPAR   /* assign                   */  {$$ = new_stmt_assign($4,$6);}
    |   OPPAR function_call CLPAR                                                       {$$ = new_stmt_call($2);}
    |   OPPAR PRINT expression CLPAR                                                    {$$ = new_stmt_print($3);}
    ;

statements:
        statement statements                                                            {$$ = new_stmts($1,$2);}
    |   /* empty */   {$$ = NULL;}
    ;

id_:
        ID IDENTIFIER kind type                                         {$$ = new_id($2,$3,$4);}
    ;

conditional:

        OPPAR IF expression statement statement CLPAR                   {$$ = new_conditional($3,$4,$5);}
    |   OPPAR IF expression statement NIL CLPAR                         {$$ = new_conditional($3,$4,NULL);}
    ;

function_call:
    CALL IDENTIFIER OPRPAR actual_args CLRPAR                           {$$ = new_function_call($2,$4);}
    ;

actual_args:
        expression more_actual_args                                     {$$ = new_actual_args($1,$2);}
    |   /* empty */                                                     {$$ = new_actual_args(NULL,NULL);}
    ;

more_actual_args:
        expression more_actual_args                                     {$$ = new_more_actual_args($1,$2);}
    |   /* empty */                                                     {$$ = new_more_actual_args(NULL,NULL);}
    ;

expression:
        OPPAR operator expression expression CLPAR COLON type           {$$ = new_expression_op($2,$3,$4,$7);}
    |   OPPAR atomic_expression CLPAR COLON type                        {$$ = new_expression_atom($2,$5);}
    |   NIL                                                             {$$ = no_exp(NIL_);}
    |   OPPAR operator expression CLPAR COLON type                      {$$ = new_expression_unop($2,$3,$6);}
    |   BOOL_LITERAL COLON BOOL                                         {$$ = new_expression_lit($1);}
    ;   

operator:
        TIMES   {$$ = new_operator(TIMES_);}
    |   PLUS    {$$ = new_operator(PLUS_);}
    |   MOD     {$$ = new_operator(MOD_);}
    |   DIV     {$$ = new_operator(DIV_);}
    |   OR      {$$ = new_operator(OR_);}
    |   AND     {$$ = new_operator(AND_);}
    |   MINUS   {$$ = new_operator(MINUS_);}
    |   EQ      {$$ = new_operator(EQ_);}
    |   NE      {$$ = new_operator(NE_);}
    |   LT      {$$ = new_operator(LT_);}
    |   GT      {$$ = new_operator(GT_);}
    |   GE      {$$ = new_operator(GE_);}
    |   LE      {$$ = new_operator(LE_);}
    |   NOT     {$$ = new_operator(NOT_);}
    |   INV     {$$ = new_operator(INV_);}
    |   TOREAL  {$$ = new_operator(TOREAL_);}
    ;   

atomic_expression:
        id_                             {$$ = new_atomic_expression_id($1);}
    |   function_call                   {$$ = new_atomic_expression_call($1);}
    |   literal                         {$$ = new_atomic_expression_lit($1);}
    |   /* empty */  {$$ = NULL;}
    ;
    
literal:
        INT_LITERAL  INT_LITERAL_VALUE              {$$ = new_literal_int($2);}        
    |   REAL_LITERAL REAL_LITERAL_VALUE              {$$ = new_literal_real($2);}  
    |   BOOL_LITERAL                                {$$ = new_literal_bool($1);}
    ;




%%

// called when there is a syntax error
void yyerror(const char *msg)
{
    extern int yylineno;     
    fprintf(stderr, "error: %s\n " , msg);
    fprintf(stderr, "Syntax error at line %d\n",yylineno); // TELL ME EXACTLY WHERE THE ERRORS ARE
}

int main()
{
  return yyparse();
}
