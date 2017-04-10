#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct ir_start *ir_start;
typedef struct global_declaration *global_declaration;
typedef struct global_declarations *global_declarations;
typedef struct global_symbol *global_symbol;
typedef struct global_symbols *global_symbols;
typedef struct symbol_var *symbol_var;
typedef struct symbol_fun *symbol_fun;
typedef struct formal_args *formal_args;
typedef struct more_formal_args *more_formal_args;
typedef struct locals *locals;
typedef struct more_locals *more_locals;
typedef struct fundef *fundef;
typedef struct instructions *instructions;
typedef struct instruction *instruction;
typedef struct op *op;
typedef struct call_inst *call_inst;
typedef struct op_call *op_call;
typedef struct print *print;
typedef struct kind_load *kind_load;
typedef struct kind_store *kind_store;
typedef struct return_inst *return_inst;
typedef struct jumps *jumps;
typedef struct actual_args *actual_args;
typedef struct more_actual_args *more_actual_args;
typedef struct literal *literal;
typedef struct type *type;

enum kind_op_{
    I_ADD_,
   	I_SUB_,
   	I_DIV_,
   	I_MUL_,
   	I_INV_,
   	MOD_,
  	I_LT_,
   	I_EQ_,
	I_NE_,
	I_LE_,

   	NOT_,
   	I_COPY_,
	I_VALUE_,
};

enum kind_op_call{
	I_CALL_,
    PROC_CALL_
};

enum kind_print_{
	I_PRINT_,
	B_PRINT_
};

// maybe memory_kind with load + store?
enum kind_load_{
 	I_ALOAD_,
   	I_LLOAD_,
  	I_GLOAD_,
};

enum kind_store_{
	I_ASTORE_,
    I_LSTORE_,
   	I_GSTORE_,
};

enum kind_return_{
	I_RETURN_,
	PROC_RETURN_
};

enum kind_lit_{
	INT_LITERAL_,
	BOOL_LITERAL_
};

enum kind_type_{
	INT_,
	BOOL_,
	VOID_
};

enum kind_jump_{
	CJUMP_,
	JUMP_
};

struct literal{
	enum {_INT, _BOOL} kind;

	union{
		int v1;
		bool v2;
	}u;
};

struct global_symbols{
	global_symbol arg1;
	global_symbols arg2;
};

struct symbol_var{
	enum {value, no_value} kind;
	char *arg1;
	union{
		struct{
			type arg2;
		}no_v;
		struct{

			type arg2;
			literal arg3;
		}v;
	}u;
};

struct symbol_fun{
	char *arg1;
	type arg2;
	formal_args arg3;
	locals arg4;
};

struct global_symbol
{
	enum {var_, fun_} kind;
	union
	{
		symbol_var arg1;
		symbol_fun arg2;
	}u;
};

struct global_declarations
{
	fundef arg1;
	global_declarations arg2;
};

struct formal_args{
	type arg1;
    char *arg2;
    more_formal_args arg3;
};

struct more_formal_args{
    char *arg2;
    type arg1;
    more_formal_args arg3;
};

struct locals{
    type arg1;
    char *arg2;
    more_locals arg3;
};

struct more_locals{
    type arg1;
    char *arg2;
    more_locals arg3;
};

struct fundef
{
	char *name;
	instructions arg2;
};

struct instructions
{	
	instruction arg1;
	instructions arg2;
};

struct instruction{
	enum {binop_,unop_,UNOP_LIT_,load_,store_,jumps_, return_,call__ ,print_,label_} kind; 
	union{
		struct{
			char *arg1;
			op arg2;
			char *arg3;
			char *arg4;
		}binop;
		struct{
			char *arg1;
			op arg2;
			char *arg3;
		}unop;
		struct{
			char *arg1;
			op arg2;
			literal arg3;
		}unop_lit;
		struct{
			char *arg1;
			kind_load arg2;
			char *arg3;
		}load;
		struct{
			char *arg1;
			kind_store arg2;
			char *arg3;
		}store;
		return_inst ri;
		jumps jmp;
		call_inst ci;
		print prt;
		struct{
			char *arg1;
			instruction arg2;
		}label_inst;
	}u;
};

struct op{
	enum  kind_op_ kind;
};

struct call_inst{
	enum {call_r_, _call} kind;
	union{
		struct{
			char *arg1;
			op_call arg2;
			char *arg3;
			actual_args arg4;
		}call_r;
		struct{
			op_call arg1;
			char *arg2;
			actual_args arg3;
		}call;
	}u;
};

struct op_call{
	enum  kind_op_call kind;
};

struct print{
	enum  kind_print_ kind;
	char *arg2;
};

struct kind_load{
	enum  kind_load_ kind;
};

struct kind_store{
	enum  kind_store_ kind;
};

struct return_inst{
	enum  kind_return_ kind;
	char *arg2;
};

struct jumps{
	enum {cjump_, jump_} kind;
	union{
		struct{
			char *arg1;
			char *true_lb;
			char *false_lb;
		}cjump;
		struct{
			char *arg1;
		}jump;
	}u;
};

struct actual_args{
	char *arg1;
	more_actual_args arg2;
};

struct more_actual_args{
	char *arg1;
	more_actual_args arg2;
};

struct type{
	enum  kind_type_ kind;
};

void start(global_symbols arg1, global_declarations arg2);

ir_start the_root(global_symbols arg1, global_declarations arg2);
void create_list();
void mips_global_fun(symbol_fun sf);
global_symbols new_global_symbols(global_symbol arg1, global_symbols arg2);
global_symbol new_global_symbol(symbol_var arg1, symbol_fun arg2);

global_declarations new_global_declarations(fundef arg1, global_declarations arg2);

symbol_var new_symbol_var(char *arg0, type arg1, literal arg2);
symbol_fun new_symbol_fun(char *arg1, type arg2, formal_args arg3, locals arg4);

actual_args new_actual_args(char *arg1, more_actual_args arg2);
more_actual_args new_more_actual_args(char *arg1, more_actual_args arg2);

locals new_locals(type arg0, char *arg1, more_locals arg2);
more_locals new_more_locals( type arg0, char *arg1, more_locals arg2);

formal_args new_formal_args(type arg0, char *arg1, more_formal_args arg2);
more_formal_args new_more_formal_args( type arg0, char *arg1, more_formal_args arg2);

fundef new_fundef(char *arg1, instructions arg2);
instructions new_instructions(instruction arg1, instructions arg2);

instruction new_instruction_binop(char *arg1, op arg2, char *arg3, char *arg4);
instruction new_instruction_unop(char *arg1, op arg2, char *arg3);
instruction new_instruction_unop_lit(char *arg1, op arg2, literal arg3);
instruction new_instruction_load(char *arg1, kind_load arg2, char *arg3);
instruction new_instruction_store(char *arg1, kind_store arg2, char *arg3);
instruction new_instruction_jump(jumps arg1);
instruction new_instruction_call(call_inst arg1);
instruction new_instruction_print(print arg1);
instruction new_instruction_return(return_inst arg1);
instruction new_instruction_label(char *arg1, instruction arg2);

return_inst new_return_inst(enum kind_return_ arg1, char *arg2);

op new_op(enum kind_op_ arg1);

print new_print(enum kind_print_ arg1, char *arg2);

call_inst new_call_inst_fun(char *arg1, op_call arg2, char *arg3, actual_args arg4);
call_inst new_call_inst_proc(op_call arg1, char *arg2,  actual_args arg3);

op_call new_op_call(enum kind_op_call arg1);
print new_print(enum kind_print_ arg1, char *arg2);

kind_load new_kind_load( enum kind_load_ arg1);
kind_store new_kind_store(enum kind_store_ arg1);

jumps new_cjump(char *arg1, char *true_lb, char *false_lb);
jumps new_jump(char *arg1);

literal new_literal_int(int v);
literal new_literal_bool(bool v);

type new_type(enum kind_type_ kind);


// 