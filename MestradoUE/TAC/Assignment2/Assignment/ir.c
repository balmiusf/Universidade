#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ir.h"
#include "lists.h"

list frames;			// linked list of all frames
frame fr;				// current function frame being used
int func_i; 			// index of current function being used

/*
	frame->vars[N] structure:
		- arg1, arg2, ..., argN, local1, local2, ..., localN
*/
	
frame new_frame(char *name_function , formal_args args, locals lcs)
{
    frame ob = (frame) malloc(sizeof(*ob));
    
    int n_fa = -1; // last position of formals args
    int n_lc = -1; // last position of locals

    if(args != NULL)
    {
      	n_fa++;
        ob->vars[n_fa] = args->arg2;	//add it to the array
        more_formal_args mfa = args->arg3; 	

        while(mfa != NULL)	// are there more args? repeat the process if true
        {
            n_fa++;
            ob->vars[n_fa] = mfa->arg2;
            mfa = mfa->arg3;
        }
    }
    n_lc = n_fa;	// start where formal args ended
    if(lcs != NULL)	// are there any locals?
    {
        n_lc++;	// increment the position
        ob->vars[n_lc] = lcs->arg2; 	// same step as before
        more_locals ml = lcs->arg3;

        while(ml != NULL)	// same step as before
        {
            n_lc++;
            ob->vars[n_lc] = ml->arg2;
            ml = ml->arg3;
        }        
    }

    ob->n_fa = n_fa;
    ob->n_lc = n_lc;

    return ob;
}

// add the function frame to the list
void mips_global_fun(symbol_fun sf)
{
	frame f = (frame) new_frame(sf->arg1, sf->arg3, sf->arg4);		// create
	list_insert(frames,f);											// add
}


void emitGlobalVar(symbol_var sv)
{
	printf("%s: ",sv->arg1);	// name
	if(sv->kind == value)		
	{
		if(sv->u.v.arg2->kind == INT_)		
			printf(" .word %d\n", sv->u.v.arg3->u.v1);	
		else
			printf(" .word %d\n", sv->u.v.arg3->u.v2);	
	}
	else
		printf(".space 4\n");	// no value, but has its space allocated
}

void emitGlobalSymbols(global_symbols gs)
{
	global_symbols temp = gs;

	if(temp->arg1->kind == var_) // if there is any global var
		printf("\t.data\n");

	while(temp != NULL)
	{
		if(temp->arg1->kind == var_)
			emitGlobalVar(temp->arg1->u.arg1);
		else
			mips_global_fun(temp->arg1->u.arg2);
		temp = temp->arg2;
	}
}

// saves actual args from last to first
void emitMoreAA(more_actual_args maa)
{
	if (maa != NULL)
	{
		emitMoreAA(maa->arg2);
		printf("\taddiu $sp, $sp, -4\n");
		printf("\tsw %s, 0($sp)\n", maa->arg1);	
	}
}


// same as the function above, last to first is the order the args are saved
void emitActualArgs(actual_args aa)
{
	more_actual_args maa = aa->arg2;
	if(maa != NULL)	
		emitMoreAA(maa);	

	printf("\taddiu $sp, $sp, -4\n");
	printf("\tsw %s, 0($sp)\n", aa->arg1);	// first actual arg (last one to be saved)
}

void emitCall(call_inst ri)
{
	if(ri->kind == call_r_)	// call with return
	{
		if(ri->u.call_r.arg4 != NULL)
			emitActualArgs(ri->u.call_r.arg4);

		printf("\tjal %s\n", ri->u.call_r.arg3);	
		printf("\tor %s, $0, $v0\n",ri->u.call_r.arg1); // save the result
	}
	else	// procedure call
	{
		if(ri->u.call.arg3!= NULL)
			emitActualArgs(ri->u.call.arg3);
		printf("\tjal %s\n", ri->u.call.arg2);
	}
}

void emitMemoryInst(instruction inst)
{
	if(inst->kind == load_)
	{
		if(inst->u.load.arg2->kind == I_GLOAD_)	
			printf("\tla %s, %s\n\tlw %s, 0(%s)\n",inst->u.load.arg1,
				inst->u.load.arg3, inst->u.load.arg1,inst->u.load.arg1 );	
		else if(inst->u.load.arg2->kind == I_ALOAD_)
		{
			int i;
			for(i = 0; i <= fr->n_fa; i++)
 				if(strcmp(inst->u.load.arg3,fr->vars[i])==0)
				{
					printf("\tlw %s, %d($fp)\n",inst->u.load.arg1,(i+1)*4);
					break;
				}
		}
		else
		{		
			int i;
			int j = 2;	
			// for local vars it starts from last Actual Arg position + 1		
			for(i = fr->n_fa+1; i <= fr->n_lc; i++)
			{
				if(strcmp(inst->u.load.arg3,fr->vars[i])==0)
				{
					printf("\tlw %s, %d($fp)\n",inst->u.load.arg1,j*(-4));
					break;
				}
				j++;			
			}
		}
	}
	else
	{
		if(inst->u.store.arg2->kind == I_GSTORE_)
			printf("\tla $at, %s\n \tsw %s, 0($at)\n", inst->u.store.arg1, 
				inst->u.store.arg3);
		else
		{
			int i;
			if(inst->u.store.arg2->kind == I_ASTORE_)
			{
				for(i = 0; i <= fr->n_fa; i++)
					if(strcmp(inst->u.store.arg1,fr->vars[i])==0)
					{
						printf("\tsw %s, %d($fp)\n",inst->u.store.arg3,(i+1)*4);
						break;
					}
			}
			else
			{
				int j = 2;
				for(i = fr->n_fa+1; i <= fr->n_lc; i++)
				{
					if(strcmp(inst->u.store.arg1,fr->vars[i])==0)
					{
						printf("\tsw %s, %d($fp)\n",inst->u.store.arg3,j*(-4));
						break;
					}
					j++;
				}
			}
		}
	}
}

void emitPrint(print inst)
{
	if(inst->kind == I_PRINT_)
		printf("\ti_print$ %s\n", inst->arg2);
	else
		printf("\tb_print$ %s\n", inst->arg2);
}

// if its a procedure return does nothing because it returns void
void emitReturn(return_inst ri)
{
	if(ri->kind == I_RETURN_)
		printf("\tor $v0, $0, %s\n", ri->arg2);
}

// just a substring function
char *substring(char *str, int i, int f)
{
	int n = 0;
	char *name = malloc(strlen(str)-2); 

	while (n < f) 
	{
		name[n] = str[i+n-1];
		n++;
	}

	name[n] = '\0';
	return name;
}

void emitInst(instruction inst)
{
	if(inst->kind == UNOP_LIT_ )
	{
		int n;
		if(inst->u.unop_lit.arg3->kind == _INT)
		 	n = inst->u.unop_lit.arg3->u.v1;
		else
			n = inst->u.unop_lit.arg3->u.v2;
		if(n < 65536)
			printf("\tori %s, $0, %d\n", inst->u.unop.arg1, n);
		else
		{
			printf("\tlui %s, %d\n", inst->u.unop.arg1, n / 65536);
			printf("\tori %s, %s, %d\n", inst->u.unop.arg1, inst->u.unop.arg1, n % 65536);
		}
	}
	else if(inst->kind == binop_)
	{
		op oper = inst->u.binop.arg2;
		
		if(oper->kind == I_ADD_) 
			printf("\taddu %s, %s, %s\n", 
				inst->u.binop.arg1, inst->u.binop.arg3, inst->u.binop.arg4);
		else if(oper->kind == I_SUB_) 
			printf("\tsubu %s, %s, %s\n", 
				inst->u.binop.arg1, inst->u.binop.arg3, inst->u.binop.arg4);
		else if(oper->kind == I_MUL_)
			printf("\tmult %s, %s\n\tmflo %s\n", 
				inst->u.binop.arg3, inst->u.binop.arg4,inst->u.binop.arg1);
		else if(oper->kind == I_DIV_)
			printf("\tdiv %s, %s\n\tmflo %s\n",
				inst->u.binop.arg3, inst->u.binop.arg4, inst->u.binop.arg1);
		else if(oper->kind == MOD_)
			printf("\tdiv %s, %s\n\tmfhi %s\n", 
				inst->u.binop.arg3,inst->u.binop.arg4, inst->u.binop.arg1);
		else if(oper->kind == I_LT_)
			printf("\tslt %s,%s,%s\n", 
				inst->u.binop.arg1, inst->u.binop.arg3, inst->u.binop.arg4);
		else if(oper->kind == I_EQ_)
		{
			printf("\tsubu  %s,%s,%s\n",
				inst->u.binop.arg1, inst->u.binop.arg3, inst->u.binop.arg4);
			printf("\tsltiu %s,%s,1\n",inst->u.binop.arg1,inst->u.binop.arg1);
		}
		else if(oper->kind == I_NE_)
		{
			printf("\tsubu  %s,%s,%s\n",
				inst->u.binop.arg1, inst->u.binop.arg3, inst->u.binop.arg4);
			printf("\tsltu %s,$0,%s\n",inst->u.binop.arg1,inst->u.binop.arg1);
		}
		else if(oper->kind == I_LE_)
		{
			printf("\tslt %s,%s,%s\n", 
				inst->u.binop.arg1, inst->u.binop.arg4, inst->u.binop.arg3);
			printf("\txori %s, %s, 1\n", inst->u.binop.arg1, inst->u.binop.arg1);
		}
	}
	else if(inst->kind == unop_)
	{
		op oper = inst->u.unop.arg2;
		if(oper->kind == I_INV_)
			printf("\tsubu %s, $0, %s\n",inst->u.unop.arg1, inst->u.unop.arg3);
		else if(oper->kind == NOT_)
			printf("\txori %s, %s, 1\n", inst->u.unop.arg1, inst->u.unop.arg3);
		else if(oper->kind == I_COPY_)
			printf("\tadd %s, %s, $0\n", inst->u.unop.arg1, inst->u.unop.arg3);
	}
	else if(inst->kind == jumps_)
	{
		jumps jp = inst->u.jmp;
		if(jp->kind == cjump_)
		{
			char *new_true_lb = substring(jp->u.cjump.true_lb,2,
				strlen(jp->u.cjump.true_lb)-1);
			char *new_false_lb = substring(jp->u.cjump.false_lb,2,
				strlen(jp->u.cjump.false_lb)-1);
			printf("\tbeq %s, $0, l$%s\n", jp->u.cjump.arg1, new_false_lb);
			printf("\tj l$%s\n",new_true_lb);
		}
		else
		{
			char *new_lb = substring(jp->u.jump.arg1,2,strlen(jp->u.jump.arg1));
			printf("\tj l$%s\n", new_lb);
		}
	}
	else if(inst->kind == call__)
		emitCall(inst->u.ci);
	else if(inst->kind == label_)
	{
		char *old_lb = inst->u.label_inst.arg1;
		char *new_lb = substring(old_lb,2,strlen(old_lb)-1);
		printf("l$%s: \n",new_lb);
		emitInst(inst->u.label_inst.arg2);
	}
	else if(inst->kind == store_ || inst->kind == load_)
		emitMemoryInst(inst);
	else if(inst->kind == print_)
		emitPrint(inst->u.prt);
	else if(inst->kind == return_)
		emitReturn(inst->u.ri);
}

void emitInsts(instructions inst)
{
	while(inst != NULL)
	{	
		emitInst(inst->arg1);
		inst = inst->arg2;
	}
}

// sp will be - (return addres (4) + n locals * 4) 
void emitPrologue()
{
	printf("\tsw $fp, -4($sp)\n\taddiu $fp, $sp, -4\n\tsw $ra, -4($fp)\n");
	printf("\taddiu $sp, $fp, -%d\n",((fr->n_lc+1)-(fr->n_fa+1))*4+4);
}

// sp will be n args * 4 + control link (4)
void emitEpilogue()
{	
	printf("\tlw $ra, -4($fp)\n\taddiu $sp, $fp, %d\n\tlw $fp, 0($fp)\n",
		(fr->n_fa+1)*4+4);
	printf("\tjr $ra\n");
}

void emitFunc(fundef arg1)
{
	printf("\n\t.text\n%s:\n",arg1->name);
	fr = getFrame(frames,func_i); // get the correct frame for the following function
	emitPrologue();
	emitInsts(arg1->arg2);
	emitEpilogue();
	func_i--;
}

void start(global_symbols arg1, global_declarations arg2)
{
	frames = list_new();	// initialize the list

	if(arg1 != NULL)
		emitGlobalSymbols(arg1);

	func_i = (frames->size)-1; // list is backwards, so first function is the last one on the list
	global_declarations temp = arg2;
	
	while(temp != NULL)	// while there are functions
	{
		emitFunc(temp->arg1);
		temp = temp->arg2;
	}

	free(frames);	// free the list
}

global_symbols new_global_symbols(global_symbol arg1, global_symbols arg2)
{
	global_symbols ob = (global_symbols) malloc(sizeof(*ob));

	ob->arg1 = arg1;
	ob->arg2 = arg2;

	return ob;
}

global_symbol new_global_symbol(symbol_var arg1, symbol_fun arg2)
{
	global_symbol ob = (global_symbol) malloc(sizeof(*ob));
	
	if(arg1 != NULL)
	{
		ob->kind = var_;
		ob->u.arg1 = arg1;
	}
	else
	{
		ob->kind = fun_;
		ob->u.arg2 = arg2;
	}

	return ob;
}

global_declarations new_global_declarations(fundef arg1, global_declarations arg2)
{
	global_declarations ob = (global_declarations) malloc(sizeof(*ob));
	ob->arg1 = arg1;
	ob->arg2 = arg2;

	return ob;
}

symbol_var new_symbol_var(char *arg0, type arg1, literal arg2)
{
	symbol_var ob = (symbol_var) malloc(sizeof(*ob));
	ob->arg1 = strdup(arg0);
	if(arg2 == NULL)
	{
		ob->kind = no_value;
		ob->u.no_v.arg2 = arg1;
	}
	else
	{
		ob->kind = value;
		ob->u.v.arg2 = arg1;
		ob->u.v.arg3 = arg2;
	}
	return ob;	
}

symbol_fun new_symbol_fun(char *arg1, type arg2, formal_args arg3, locals arg4)
{
	symbol_fun ob = (symbol_fun) malloc(sizeof(*ob));
	
	ob->arg1 = strdup(arg1);
	ob->arg2 = arg2;
	ob->arg3 = arg3;
	ob->arg4 = arg4;

	return ob;	
}

fundef new_fundef(char *arg1, instructions arg2)
{
	fundef ob = (fundef) malloc(sizeof(*ob));

	ob->name = strdup(arg1);
	ob->arg2 = arg2;

	return ob;
}

instructions new_instructions(instruction arg1, instructions arg2)
{
	instructions ob = (instructions) malloc(sizeof(*ob));
	ob->arg1 = arg1;
	ob->arg2 = arg2;

	return ob;
}

instruction new_instruction_binop(char *arg1, op arg2, char *arg3, char *arg4)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = binop_;
	ob->u.binop.arg1 = strdup(arg1);
	ob->u.binop.arg2 = arg2;
	ob->u.binop.arg3 = strdup(arg3);
	ob->u.binop.arg4 = strdup(arg4);

	return ob;
}

instruction new_instruction_unop(char *arg1, op arg2, char *arg3)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = unop_;
	ob->u.unop.arg1 = strdup(arg1);
	ob->u.unop.arg2 = arg2;
	ob->u.unop.arg3 = strdup(arg3);

	return ob;
}

instruction new_instruction_unop_lit(char *arg1, op arg2, literal arg3)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = UNOP_LIT_;
	ob->u.unop_lit.arg1 = strdup(arg1);
	ob->u.unop_lit.arg2 = arg2;
	ob->u.unop_lit.arg3 = arg3;

	return ob;
}

instruction new_instruction_load(char *arg1, kind_load arg2, char *arg3)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = load_;
	ob->u.load.arg1 = strdup(arg1);
	ob->u.load.arg2 = arg2;
	ob->u.load.arg3 = strdup(arg3);

	return ob;
}

instruction new_instruction_return(return_inst arg1)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = return_;
	ob->u.ri = arg1;

	return ob;
}

instruction new_instruction_store(char *arg1, kind_store arg2, char *arg3)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = store_;
	ob->u.store.arg1 = strdup(arg1);
	ob->u.store.arg2 = arg2;
	ob->u.store.arg3 = strdup(arg3);

	return ob;
}

instruction new_instruction_jump(jumps arg1)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = jumps_;
	ob->u.jmp = arg1;

	return ob;
}

instruction new_instruction_call(call_inst arg1)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = call__;
	ob->u.ci = arg1;

	return ob;
}

instruction new_instruction_print(print arg1)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = print_;
	ob->u.prt = arg1;

	return ob;
}

instruction new_instruction_label(char *arg1, instruction arg2)
{
	instruction ob = (instruction) malloc(sizeof(*ob));

	ob->kind = label_;
	ob->u.label_inst.arg1 = strdup(arg1);
	ob->u.label_inst.arg2 = arg2;

	return ob;
}

op new_op(enum kind_op_ arg1)
{
	op ob = (op) malloc(sizeof(*ob));
	ob->kind = arg1;

	return ob;
}

call_inst new_call_inst_fun(char *arg1, op_call arg2, char *arg3, actual_args arg4)
{
	call_inst ob = (call_inst) malloc(sizeof(*ob));

	ob->kind = call_r_;
	ob->u.call_r.arg1 = strdup(arg1);
	ob->u.call_r.arg2 = arg2;
	ob->u.call_r.arg3 = strdup(arg3);
	ob->u.call_r.arg4 = arg4;

	return ob;
}

call_inst new_call_inst_proc(op_call arg1, char *arg2, actual_args arg3)
{
	call_inst ob = (call_inst) malloc(sizeof(*ob));

	ob->kind = _call;
	ob->u.call.arg1 = arg1;
	ob->u.call.arg2 = strdup(arg2);
	ob->u.call.arg3 = arg3;

	return ob;
}

op_call new_op_call(enum kind_op_call arg1)
{
	op_call ob = (op_call) malloc(sizeof(*ob));

	ob->kind = arg1;

	return ob;
}

print new_print(enum kind_print_ arg1, char *arg2)
{
	print ob = (print) malloc(sizeof(*ob));
	ob->kind = arg1;

	ob->arg2 = strdup(arg2);
	return ob;
}

kind_load new_kind_load( enum kind_load_ arg1)
{
	kind_load ob = (kind_load) malloc(sizeof(*ob));
	ob->kind = arg1;

	return ob;
}


kind_store new_kind_store( enum kind_store_ arg1)
{
	kind_store ob = (kind_store) malloc(sizeof(*ob));
	ob->kind = arg1;

	return ob;
}

return_inst new_return_inst(enum kind_return_ arg1, char *arg2)
{
	return_inst ob = (return_inst) malloc(sizeof(*ob));
	if(arg1 == I_RETURN_)
	{
		ob->kind = arg1;
		ob->arg2 = strdup(arg2);
	}
	else
		ob->kind = arg1;

	return ob;	
}

jumps new_cjump(char *arg1, char *true_lb, char *false_lb)
{
	jumps ob = (jumps) malloc(sizeof(*ob));
	ob->kind = cjump_;
	ob->u.cjump.arg1 = strdup(arg1);
	ob->u.cjump.true_lb = strdup(true_lb);
	ob->u.cjump.false_lb = strdup(false_lb);

	return ob;
}


jumps new_jump(char *arg1)
{
	jumps ob = (jumps) malloc(sizeof(*ob));
	ob->kind = jump_;
	ob->u.jump.arg1 = strdup(arg1);

	return ob;
}

locals new_locals(type arg0, char *arg1, more_locals arg2)
{
	locals ob = (locals) malloc(sizeof(*ob));
	ob->arg1 = arg0;
	ob->arg2 = strdup(arg1);
	ob->arg3 = arg2;

	return ob;
}

more_locals new_more_locals( type arg0, char *arg1, more_locals arg2)
{
	more_locals ob = (more_locals) malloc(sizeof(*ob));
	ob->arg1 = arg0;
	ob->arg2 = strdup(arg1);
	ob->arg3 = arg2;

	return ob;
}


formal_args new_formal_args(type arg0, char *arg1, more_formal_args arg2)
{
	formal_args ob = (formal_args) malloc(sizeof(*ob));
	ob->arg1 = arg0;
	ob->arg2 = strdup(arg1);
	ob->arg3 = arg2;

	return ob;
}



more_formal_args new_more_formal_args( type arg0, char *arg1, more_formal_args arg2)
{
	more_formal_args ob = (more_formal_args) malloc(sizeof(*ob));
	ob->arg1 = arg0;
	ob->arg2 = strdup(arg1);
	ob->arg3 = arg2;

	return ob;
}



actual_args new_actual_args(char *arg1, more_actual_args arg2)
{
	actual_args ob = (actual_args) malloc(sizeof(*ob));
	ob->arg1 = strdup(arg1);
	ob->arg2 = arg2;

	return ob;
}



more_actual_args new_more_actual_args(char *arg1, more_actual_args arg2)
{
	more_actual_args ob = (more_actual_args) malloc(sizeof(*ob));
	ob->arg1 = strdup(arg1);
	ob->arg2 = arg2;

	return ob;
}


literal new_literal_int(int v)
{
	literal ob = (literal) malloc(sizeof(*ob));
	ob->kind = _INT;
	ob->u.v1 = v;

	return ob;
}

literal new_literal_bool(bool v)
{
	literal ob = (literal) malloc(sizeof(*ob));
	ob->kind = _BOOL;
	ob->u.v2 = v;

	return ob;
}

type new_type(enum kind_type_ kind)
{
	type ob = (type) malloc(sizeof(*ob));
	ob->kind = kind;

	return ob;
}