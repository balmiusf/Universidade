#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct ast *ast;
typedef struct global_declaration *global_declaration;
typedef struct global_declarations *global_declarations;
typedef struct atomic_expression *atomic_expression;
typedef struct expression *expression;
typedef struct conditional *conditional;
typedef struct more_vardecls *more_vardecls;
typedef struct vardecls *vardecls;
typedef struct stmt *stmt;
typedef struct stmts *stmts;
typedef struct body *body;
typedef struct print *print;
typedef struct id *id;
typedef struct fundef *fundef;
typedef struct function_call *function_call;
typedef struct actual_args *actual_args;
typedef struct more_actual_args *more_actual_args;
typedef struct literal *literal;
typedef struct formal_args *formal_args;
typedef struct more_formal_args *more_formal_args;
typedef struct operator *operator;
typedef struct type *type;
typedef struct kind *kind;

enum kind_ {ARG_ , VAR_, LOCAL_} ;  
enum type_ {BOOL_, INT_, REAL_, VOID_} ;
enum nil{NIL_ };

enum  op_ {
        TIMES_, PLUS_, MOD_, OR_, AND_, MINUS_, 
        EQ_, NE_, LT_, GT_, GE_, LE_, NOT_, 
        TOREAL_, INV_, DIV_
    }; 

struct ast{
    global_declarations root;
};

struct type{
    enum type_ type;
};

struct kind{
  enum kind_ kind;  
};

struct operator{
   enum op_ op; 
};

struct global_declaration{
    enum{var_decls, fun_def} kind;

    union{
        struct{
            vardecls arg1;
        }vars;
        struct{
            fundef arg1;
        }fun;
    }un;
};
    
struct global_declarations
{
    enum{single, multiple} kind;

    union{
        struct{
            global_declaration arg1;
        }single_global;
        struct{
            global_declaration arg1;
            global_declarations arg2;
        }multiple_global;
    }un;
};

struct vardecls{
    id arg1;
    expression arg2;
};

struct formal_args{
    char *arg1;
    type arg2;
    more_formal_args arg3;
};

struct more_formal_args{
    char *arg1;
    type arg2;
    more_formal_args arg3;
};

struct fundef{
    char *id;
    formal_args arg1;
    body arg2;
};

struct id{
    char *arg1;
    kind arg2;
    type arg3;
};

struct function_call{
    char *arg1;
    actual_args arg2;
};

struct actual_args{
    expression arg1;
    more_actual_args arg2;
};

struct more_actual_args{
    expression arg1;
    more_actual_args arg2;
};

struct literal{
    enum {INT_LIT, REAL_LIT, BOOL_LIT} kind;

    union{
        int int_lit_v;
        double real_lit_v;
        bool bool_lit_v;
    }u;
};

struct atomic_expression{
    enum {ID_, function_call_, literals_} kind;

    union{
        struct{
            id arg1;
        }id_;
        struct{
            function_call arg1;

        }func_call;
        struct{
            literal arg1;
        }literal_;
    }u;
};

struct expression
{
    enum {no_ret,binop, nil_op,bool_lit, atom_exp,unop} kind;    
    union
    {
        struct
        {
            operator op_;
            expression arg1;
            expression arg2;
            type arg3;
        }bin_op;        
        struct
        {
            operator op_;
            expression arg1;
            type arg2;
        }un_op;
        struct
        {
            atomic_expression arg1; 
            type arg2;
        }atomic_exp_;  
        struct
        {
            literal l;
        }boollit;

        struct{
            enum nil arg1;
        }no_return;
    }u;
};

struct conditional{
        expression arg1;
        stmt arg2;              // label true   
        stmt arg3;              // label false
};

struct more_vardecls{
    vardecls arg1;
    more_vardecls arg2;
};

struct stmt{
    enum {compound_stmts, loop_, conditional_, assign, func_call, print_} kind;

    union{
        struct{
            stmts arg1;
        }compound_stmts_;
        struct{
            expression arg1;
            stmt arg2;
        }_loop;

        struct{
            conditional arg1;
        }_conditional;

        struct 
        {
            id arg1;
            expression arg2;

        }assigns_;
        struct{
            function_call arg1;

        }_func_call;
        struct{
            expression arg1;
        }_prints;
    }u;
};

struct stmts{
    stmt arg1;
    stmts arg2;
};

struct body{
        more_vardecls arg1;
        stmt arg2;
        expression arg3;
};


void the_root(global_declarations root);

global_declarations new_global_declarations(global_declaration arg1, global_declarations arg2);
global_declaration new_global_declaration_decl(vardecls arg1);
global_declaration new_global_declaration_fun(fundef arg1);

 vardecls new_vardecls(id arg1, expression arg2);

fundef new_fundef(char *arg1, formal_args arg2, body arg3);

formal_args new_formal_args(char *arg1, type arg2, more_formal_args arg3);
more_formal_args new_more_formal_args(char *arg1, type arg2, more_formal_args arg3);

body new_body(more_vardecls arg1, stmt arg2, expression arg3);
more_vardecls new_more_vardecls(vardecls arg1, more_vardecls arg2);

stmt new_stmt(stmts arg1);
stmt new_stmt_loop(expression arg1, stmt arg2);
stmt new_stmt_cond(conditional arg1);
stmt new_stmt_assign(id arg1, expression arg2);
stmt new_stmt_call(function_call arg1);
stmt new_stmt_print(expression arg1);
stmts new_stmts(stmt arg1, stmts arg2);
stmt no_stmt(enum nil arg1);

conditional new_conditional(expression arg1, stmt arg2, stmt arg3);
function_call new_function_call(char *arg1, actual_args arg2);

actual_args new_actual_args(expression arg1, more_actual_args arg2);
more_actual_args new_more_actual_args(expression arg1, more_actual_args arg2);

expression new_expression_op(operator arg1, expression arg2, expression arg3, type arg4);
expression new_expression_atom(atomic_expression arg1, type arg2);

expression new_expression_lit(bool arg1);
expression new_expression_unop(operator arg1, expression arg2, type arg3);

expression no_exp(enum nil arg1);

atomic_expression new_atomic_expression_id(id arg1);
atomic_expression new_atomic_expression_call(function_call arg1);
 atomic_expression new_atomic_expression_lit(literal arg1);

 literal new_literal_int(int value);
 literal new_literal_real(double value);
 literal new_literal_bool(bool value);

 kind new_kind(enum kind_ arg1);
 type new_type(enum type_ arg1);
 operator new_operator(enum op_ arg1);

 id new_id(char *arg1, kind arg2, type arg3);

