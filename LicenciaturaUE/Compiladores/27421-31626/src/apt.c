#include <stdio.h>
#include "apt.h"
#include <string.h>
#include <stdlib.h>

struct calc_exp *calc_exp_new_par(calc_t_exp exp){
	calc_t_exp ret = (calc_t_exp) malloc(sizeof(*ret));

	ret->kind= EXP_PAR;
	ret->u.par.exp = exp;

	return ret;
}

struct calc_exp *calc_exp_new_binop(char *op, calc_t_exp arg1, calc_t_exp arg2)
{
  calc_t_exp ret = (calc_t_exp) malloc (sizeof (*ret));

  ret->kind = EXP_BINOP;
  ret->u.binop.op =strdup(op);
  ret->u.binop.arg1 = arg1;
  ret->u.binop.arg2 = arg2;

  return ret;
}

struct calc_exp *calc_exp_new_literal(literalExp lit){
	calc_t_exp ret = (calc_t_exp) malloc (sizeof (*ret));

	ret->u.literals.lit = lit;
	ret->kind = LITERAL;
	return ret;
}

struct literalExp *new_literal_int(int n){
	literalExp ret = (literalExp) malloc (sizeof (*ret));

	ret->kind = INT_LITERAL;
	ret->u.INT.val = n;

	return ret;
}

struct literalExp *new_literal_float(float n){
	literalExp ret = (literalExp) malloc (sizeof (*ret));
	ret->kind = FLOAT_LITERAL;
	ret->u.FLOAT.valfloat = n;
	return ret;
}

struct literalExp *new_literal_string(char *id){
	literalExp ret = (literalExp) malloc (sizeof (*ret));
	ret->kind = STRING_LITERAL;
	ret->u.STRING.str = strdup(id);

	return ret;
}

struct literalExp *new_literal_bool(int n){
	literalExp ret = (literalExp) malloc (sizeof (*ret));
	ret->kind = BOOL_LITERAL;
	ret->u.INT.val = n;

	return ret;
}

struct decls *new_decls(decl args1, decls args2){
	decls ret = (decls) malloc (sizeof (*ret));	

	ret->kind = DECLS;
	ret->declarations.args1 = args1;
	ret->declarations.args2 = args2;

	return ret;
}

struct decl *new_decl_normal(decl1 args1){
	decl ret = (decl) malloc (sizeof (*ret));
	ret->kind = NORMAL;
	ret->u.normal.args1 = args1;

	return ret;
}

struct decl *new_decl_func(decl2 args1){
	decl ret = (decl) malloc (sizeof (*ret));

	ret->kind = FUNC;
	ret->u.func.args1 = args1;

	return ret;
}


struct decl1 *new_decl1_wo_type(belos_ids ids, type type){
	decl1 ret = (decl1) malloc (sizeof (*ret));
	

	ret->kind = IDS;
	ret->u.many_ids.args1 = ids;
	ret->u.many_ids.args2 = type;

	return ret;
	
}

struct decl1 *new_decl1_type(belos_ids ids, type type, calc_t_exp exp){
	decl1 ret = (decl1) malloc (sizeof (*ret));
	
	ret->kind = ASSIGN_;
	ret->u.assign.args1 = ids;
	ret->u.assign.args2 = type;
	ret->u.assign.args3 = exp;

}

struct decl1 *new_decl1_define(char *id, type type){
	decl1 ret = (decl1) malloc (sizeof (*ret));
	
	ret->kind = DEFINE_ID;
	ret->u.define.id = strdup(id);

	return ret;
}

struct decl1 *new_decl1_array(char *id,calc_t_exp args1,type type){
	decl1 ret = (decl1) malloc (sizeof (*ret));
	
	if(args1 == NULL)
	{
		ret->u.array2.id = strdup(id);	
		ret->u.array2.type = type;
	}
	else
	{
		ret->u.array1.id = strdup(id);
		ret->u.array1.args1 = args1;
		ret->u.array1.type = type;
	}

	return ret;

}

struct ifs *new_ifs(expBools args1, corpo args2, corpo args3){
	ifs ret = (ifs) malloc (sizeof (*ret));

	if(args3 == NULL)
	{
		ret->kind = IF_ELSE;
		ret->u.if_else.args1 = args1;
		ret->u.if_else.args2 = args2;
		
	}
	else
	{
		ret->kind = IF_ELSE_THEN;
		ret->u.if_else_then.args1 = args1;
		ret->u.if_else_then.args2 = args2;
		ret->u.if_else_then.args3 = args3;
	}
	return ret;	
}

struct whiles *new_whiles(expBools args1, corpo_cycle args2){
	whiles ret = (whiles) malloc (sizeof (*ret));

	ret->kind = WHILE_;
	ret->u.cycle.args1 = args1;
	ret->u.cycle.args2 = args2;

	return ret;
}

struct decl2 *new_decl2(funcdeclar args1, type args2, corpo args3){
	decl2 ret = (decl2) malloc (sizeof (*ret));

	ret->kind = FUNC_DECL;
	ret->u.func.args1 = args1;
	ret->u.func.args2 = args2;
	ret->u.func.args3 = args3;

	return ret;
}

struct corpo *new_corpo(stmts args1, corpo args2){
	corpo ret = (corpo) malloc (sizeof (*ret));

	ret->kind = BODY_STMTS;
	ret->BODY_STMTS.arg1 = args1;
	ret->BODY_STMTS.arg2 = args2;

	return ret;
}

struct corpo_cycle *new_corpo_cycle(stmts args1){
	corpo_cycle ret = (corpo_cycle) malloc (sizeof (*ret));
		ret->kind = CYCLE_STMTS;
		ret->u.stmt.arg1 = args1;

		return ret;
}

struct corpo_cycle *new_corpo_cycle_break(enum cycle_kind_2 kind){
	corpo_cycle ret = (corpo_cycle) malloc (sizeof (*ret));

	ret->kind = BREAK_2;
	ret->u.stop.args1 = kind;

	return ret;
}

struct corpo_cycle *new_corpo_cycle_next(enum cycle_kind_2 kind){
	corpo_cycle ret = (corpo_cycle) malloc (sizeof (*ret));
	ret->kind = NEXT_2;
	ret->u.next.args1 = kind;

	return ret;
}

struct stmts *new_stmts_decl(decl1 args1){
	stmts ret = (stmts) malloc (sizeof (*ret));

	ret->kind = stmts_DECL;
	ret->u.decl.arg1 = args1;
	return ret;
}

struct stmts *new_stmts_cond(ifs args1){
	stmts ret = (stmts) malloc (sizeof (*ret));
	
	ret->kind = stmts_IF;
	ret->u.ifs.arg1 = args1;	

	return ret;
}

struct stmts *new_stmts_cycle(whiles args1){
	stmts ret = (stmts) malloc (sizeof (*ret));
	
	ret->kind = stmts_CYCLE;
	ret->u.cycle.arg1 = args1;	

	return ret;
}

struct stmts *new_stmts_return(calc_t_exp args1){
	stmts ret = (stmts) malloc (sizeof (*ret));
	
	ret->kind = stmts_RETURN;
	ret->u.returns.arg1 = args1;

	return ret;	
}

struct stmts *new_stmts_afect(afect args1){
	stmts ret = (stmts) malloc (sizeof (*ret));

	ret->kind = stmts_AFECT;
	ret->u.afects.arg1 = args1;

	return ret;
}

struct funcdeclar *new_func_args(char *id, char *arg1, type args3, more_args  args4){
	funcdeclar ret = (funcdeclar) malloc (sizeof (*ret));

	ret->kind = WITH_ARGS;
	ret->u.has_args.id = strdup(id);
	ret->u.has_args.first_arg = strdup(arg1);
	ret->u.has_args.type = args3;
	ret->u.has_args.args = args4;

	return ret;
}

struct funcdeclar *new_func_no_args(char *id){
	funcdeclar ret = (funcdeclar) malloc (sizeof (*ret));
	ret->kind = NO_ARGS;
	ret->u.id = strdup(id);

	return ret; 
}

// ou more_args? Yup
struct funcdeclar2 *new_func_args_2(char *id, type args2, more_args args3){
	more_args ret = (more_args) malloc (sizeof (*ret));
	
	ret->kind = MORE_ARGS;
	ret->u.mais_args.id = strdup(id);
	ret->u.mais_args.type = args2;
	ret->u.mais_args.args3 = args3;

	return ret; 

}

struct afect *new_afect(char *id, afects args1){
	afect ret = (afect) malloc (sizeof (*ret));
	
	ret->kind = AFECT;
	ret->u.afect.id = strdup(id);
	ret->u.afect.afect = args1;

	return ret; 

}

struct afects *new_afects(char *id, afects args2){
	
	afects ret = (afects) malloc (sizeof (*ret));
	ret->kind = AFECT_1;
	ret->u.afects.id = strdup(id);
	ret->u.afects.afects = args2;

	return ret;

}

struct afects *new_afects_end(calc_t_exp args1){
	afects ret = (afects) malloc (sizeof (*ret));
	ret->kind = AFECT_2;
	ret->u.end_afect.arg1 = args1;

	return ret;
}

struct ids *new_ids_solo(char *id){
	belos_ids ret = (belos_ids) malloc (sizeof (*ret));
	ret->kind = ID_SOLO;

	ret->u.id = strdup(id);
	return ret;
}

struct ids *new_ids_more(char *id, belos_ids args2){
	belos_ids ret = (belos_ids) malloc (sizeof (*ret));
	ret->kind = MULTIPLE_IDS;

	ret->u.many_ids.id= strdup(id);
	ret->u.many_ids.more_ids = args2;

	return ret;
}

struct expBools *new_exp_bools_1(calc_t_exp args1, op args2, calc_t_exp args3){
	expBools ret = (expBools) malloc(sizeof(*ret));

	ret->kind = EXP_BINOP_1;
	ret->u.binop.arg1 = args1;
	ret->u.binop.op = args2;
	ret->u.binop.arg2 = args3;

	return ret;
}

struct expBools *new_exp_bools_2(calc_t_exp args1, op args2, expBools args3){
	expBools ret = (expBools) malloc(sizeof(*ret));

	ret->kind = EXP_BINOP_2;
	ret->u.binop2.arg1 = args1;
	ret->u.binop2.op = args2;
	ret->u.binop2.arg2 = args3;

	return ret;
}

struct expBools *new_exp_bools_not(expBools args1){
	expBools ret = (expBools) malloc(sizeof(*ret));

	ret->kind = NEGATE_BOOL;
	ret->u.negation.arg1 = args1;

	return ret;
}

struct type *new_type(enum type_kind typel){
	type ret = (type) malloc(sizeof(*ret));
	ret->kind = typel;

	return ret;
}

struct op *new_op(enum op_kind operator){
	op ret = (op) malloc(sizeof(*ret));
	ret->kind = operator;

	return ret;
}
struct expBools *new_exp_bools_par(expBools args1){
	expBools ret = (expBools) malloc(sizeof(*ret));
	ret->u.par.arg1 = args1;

	return ret;
}

struct expBools *new_exp_bools_id(char *arg1){
		expBools ret = (expBools) malloc(sizeof(*ret));
		ret->kind = ID_EXP_BOOL;
		ret->u.id.arg1 = strdup(arg1);

	return ret;
}

struct expBools *new_exp_bools_id_exp_2(char *id, op operador, char *id2){
	expBools ret = (expBools) malloc(sizeof(*ret));
	ret->u.id_op_id.arg1 = strdup(id);
	ret->u.id_op_id.op = operador;
	ret->u.id_op_id.arg2 = strdup(id2);
	ret->kind = ID_OP_ID;
	return ret;
}

struct expBools *new_exp_bools_id_exp(char *id, op operador, calc_t_exp args3){
	expBools ret = (expBools) malloc(sizeof(*ret));
	ret->u.id_op_exp.arg1 = strdup(id);
	ret->u.id_op_exp.op = operador;
	ret->u.id_op_exp.arg3 = args3;

	ret->kind = ID_OP_EXP;

	return ret;
}

struct stmts *new_stmts_funcCalls(funcCall args1){
	stmts ret =  (stmts) malloc(sizeof(*ret));

	ret->kind = FUNCCALL;
	ret->u.call.args1 = args1;

	return ret;
}

struct funcCall *new_function_calls_no_args(char *id){
	funcCall ret = (funcCall) malloc(sizeof(*ret));

	ret->kind = WO_ARGS;
	ret->u.noargs.id =id;

	return ret;
}

struct funcCall *new_function_calls_args(char *id, belos_ids ids){
	funcCall ret = (funcCall) malloc(sizeof(*ret));

	ret->kind = W_ARGS;
	ret->u.wargs.id =id;
	ret->u.wargs.ids = ids;

	return ret;
}

struct funcCall *new_function_calls_exp(char *id, calc_t_exp exp){
	funcCall ret = (funcCall) malloc(sizeof(*ret));

	ret->kind = W_EXP;
	ret->u.w_exp.id = strdup(id);
	ret->u.w_exp.exps = exp;

	return ret;
}

struct funcCall *new_function_calls_func(char *id, funcCall arg2){
	funcCall ret = (funcCall) malloc(sizeof(*ret));

	ret->kind = FUNC_CALL;
	ret->u.funccalls.id = strdup(id);
	ret->u.funccalls.arg2 = arg2;

	return ret;
}

struct nl *new_line(nl args1){
	nl ret = (nl) malloc(sizeof(*ret));

	ret->kind = NL_;

	ret->new_ln.nl = args1;

	return ret;

}



