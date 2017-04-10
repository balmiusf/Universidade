#include "tacl_ir.h"
#include "stack.h"			/* Stack will be used to store temp, fp and label values */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void ir_call(function_call args, type tp, int i);
void ir_exp(expression exp);
void ir_stmt(stmt st);
void ir_stmts(stmts st);
void ir_assign(id id_, expression exp);
void ir_bool(expression exp, int i);
int count_ors(expression exp);	

int temp = 0;	// initialize counter for temporary
int fp = 0;		// initialize counter for floating pointer temporary 
int label = 0;	// initialize counter for labels
int type_r = 0; // useful to know what kind of op needs to be used (r_ or i_) 
				// 1 : real_
				// 0 : int_ or bool_
				// every instruction that generates a new register, affects the value of this global variable


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

/*
	i = 0 for load
	i = 1 for store
*/

void ir_id(id id_, int i)
{ 
	char *name = substring(id_->arg1, 2,strlen(id_->arg1)-2);

	if(i == 0)
	{
		if(id_->arg3->type == INT_ || id_->arg3->type == BOOL_)
		{
			if(id_->arg2->kind == ARG_)
				printf("\tt%d <- i_aload @%s\n",temp,name);
			else if(id_->arg2->kind == LOCAL_)
				printf("\tt%d <- i_lload @%s\n",temp,name);
			else // kind == VAR_
				printf("\tt%d <- i_gload @%s\n",temp,name);
			temp++;
			type_r = 0;
		}
		else if (id_->arg3->type == REAL_)
		{
			if(id_->arg2->kind == ARG_)
				printf("\tfp%d <- r_aload @%s\n",fp,name);
			else if(id_->arg2->kind == LOCAL_)
				printf("\tfp%d <- r_lload @%s\n",fp,name);
			else
				printf("\tfp%d <- r_gload @%s\n",fp,name);
			fp++;
			type_r = 1;
		}
	}
	else		// i == 1
	{
		int t = pop();

		if(id_->arg3->type == INT_ || id_->arg3->type == BOOL_)
		{
			if(type_r == 0)
			{
				if(id_->arg2->kind == ARG_)
					printf("\t@%s <- i_astore t%d\n",name,t);
				else if(id_->arg2->kind == LOCAL_)
					printf("\t@%s <- i_lstore t%d\n",name,t);
				else
					printf("\t@%s <- i_gstore t%d\n",name,t);
			}
			else	// this is valid:  int <- real
			{
				if(id_->arg2->kind == ARG_)
					printf("\t@%s <- i_astore fp%d\n",name,t);
				else if(id_->arg2->kind == LOCAL_)
					printf("\t@%s <- i_lstore fp%d\n",name,t);
				else
					printf("\t@%s <- i_gstore fp%d\n",name,t);
			}	

		}
		else if (id_->arg3->type == REAL_)
		{
			if(id_->arg2->kind == ARG_)
				printf("\t@%s <- r_astore fp%d\n",name,t);
			else if(id_->arg2->kind == LOCAL_)
				printf("\t@%s <- r_lstore fp%d\n",name,t);
			else
				printf("\t@%s <- r_gstore fp%d\n",name,t);
		}
	}
}

void ir_literals(literal lit)
{
	if(lit->kind == INT_LIT || lit->kind == BOOL_LIT)
	{
		printf("\tt%d <- i_value %d\n",temp,lit->u.int_lit_v);
		temp++;
		type_r = 0;
	}
	else if (lit->kind == REAL_LIT)
	{
		printf("\tfp%d <- r_value %f\n",fp,lit->u.real_lit_v);
		fp++;
		type_r = 1;
	}
}

void print_op(operator op,type tp)
{
	int t;
	int t2;
	if(tp->type == INT_) 
	{	
		t = pop();
		if(op->op != INV_)		// if it's not INV_ then there is another pop() to be made
		{
			t2 = pop();
			if(op->op == PLUS_)
				printf("\tt%d <- i_add t%d, t%d\n", temp, t2, t);
			if(op->op == MINUS_)
				printf("\tt%d <- i_sub t%d, t%d\n",temp, t2, t);
			if(op->op == TIMES_)
				printf("\tt%d <- i_mul t%d, t%d\n", temp, t2, t);
			if(op->op == DIV_)
				printf("\tt%d <- i_div t%d, t%d\n", temp, t2, t);
			if(op->op == MOD_)
				printf("\tt%d <- mod t%d, t%d\n", temp, t2, t);
		}
		else
			printf("\tt%d <- i_inv t%d\n", temp, t);

		temp++;	
		type_r = 0;
	}
	else if(tp->type == REAL_)
	{
		t = pop();
		if(op->op != INV_ && op->op != TOREAL_)
		{	
			t2 = pop();
			if(op->op == PLUS_)
				printf("\tfp%d <- r_add fp%d, fp%d\n", fp, t2, t);
			if(op->op == MINUS_)
				printf("\tfp%d <- r_sub fp%d, fp%d\n", fp, t2, t);
			if(op->op == TIMES_)
				printf("\tfp%d <- r_mul fp%d, fp%d\n", fp, t2, t);
			if(op->op == DIV_)
				printf("\tfp%d <- r_div fp%d, fp%d\n", fp, t2, t);
		}
		else
		{
			if ( op->op == INV_)
				printf("\tfp%d <- r_inv fp%d\n", fp, t);
			else if(op->op == TOREAL_)
				printf("\tfp%d <- itor t%d\n",fp,t);
		}

		fp++;
		type_r = 1;
	}
	else // type == BOOL_
	{
		if(type_r == 0)	// if the last register was a "t"
		{
			t = pop();
			if(op->op != NOT_)
			{
				t2 = pop();
				if(op->op == LT_)
					printf("\tt%d <- i_lt t%d, t%d\n", temp, t2, t);
				if(op->op == GT_) 
					printf("\tt%d <- i_lt t%d, t%d\n", temp, t, t2);
				if(op->op == LE_)
					printf("\tt%d <- i_lt t%d, t%d\n", temp, t, t2);
				if(op->op == GE_)
					printf("\tt%d <- i_lt t%d, t%d\n", temp, t2, t);
				if(op->op == NE_)
					printf("\tt%d <- i_eq t%d, t%d\n", temp, t2, t);
				if(op->op == EQ_)
					printf("\tt%d <- i_eq t%d, t%d\n", temp, t2, t);
			}
			else
				if (op->op == NOT_)
					printf("\tt%d <- not t%d\n", temp, t);
			temp++;
		}
		else	// then it's a "fp"
		{
			t = pop();
			t2 = pop();
			if(op->op == LT_)
				printf("\tt%d <- r_lt fp%d, fp%d\n", temp, t2, t);
			if(op->op == GT_) 
				printf("\tt%d <- r_lt fp%d, fp%d\n", temp, t, t2);
			if(op->op == LE_)
				printf("\tt%d <- r_le fp%d, fp%d\n", temp, t, t2);
			if(op->op == GE_)
				printf("\tt%d <- r_lt fp%d, fp%d\n", temp, t2, t);
			if(op->op == NE_)
				printf("\tt%d <- r_eq fp%d, fp%d\n", temp, t2, t);
			if(op->op == EQ_)
				printf("\tt%d <- r_eq fp%d, fp%d\n", temp, t2, t);
			temp++;	
		}
		type_r = 0;
	}
}

void ir_atom_exp(atomic_expression exp, type tp)
{
	if(exp->kind == ID_)
		ir_id(exp->u.id_.arg1,0);
	else if(exp->kind == literals_)
		ir_literals(exp->u.literal_.arg1);
	else
		ir_call(exp->u.func_call.arg1,tp,0);
}

// for every expression the result register gets pushed to the stack
void ir_exp(expression exp)
{
	if (exp->kind == atom_exp)
	{
		ir_atom_exp(exp->u.atomic_exp_.arg1,exp->u.atomic_exp_.arg2);

		if(exp->u.atomic_exp_.arg2->type == REAL_)
			push(fp-1);
		else
			push(temp-1);
	}
	else if (exp->kind == binop)
	{	
		ir_exp(exp->u.bin_op.arg1);
		ir_exp(exp->u.bin_op.arg2);
		print_op(exp->u.bin_op.op_,exp->u.bin_op.arg3);

		if(exp->u.bin_op.arg3->type == REAL_)
			push(fp-1);
		else
			push(temp-1);
	}
	else if(exp->kind == unop)
	{
		ir_exp(exp->u.un_op.arg1);
		print_op(exp->u.un_op.op_,exp->u.un_op.arg2);

		if(exp->u.un_op.arg2->type == REAL_)
			push(fp-1);
		else
			push(temp-1);
	}
	else if(exp->kind == bool_lit)
	{
		if(exp->u.boollit.l)
			printf("\tt%d <- i_value 1\n",temp);
		else
			printf("\tt%d <- i_value 0\n",temp);

		push(temp);
		temp++;
		type_r = 0;
	}
}

void ir_vars(vardecls vd)
{
	if(vd->arg2->kind != nil_op)	
		ir_assign(vd->arg1,vd->arg2);
}

void ir_stmts(stmts st)
{
	while(st != NULL)
	{
		ir_stmt(st->arg1);
		st = st->arg2;
	}
}

void ir_cpy(id dest, id tocpy)
{
	ir_id(tocpy,0);
	if((dest->arg3->type == INT_ && tocpy->arg3->type == INT_) 
		|| dest->arg3->type == BOOL_)
	{
		printf("\tt%d <- i_copy t%d\n",temp, temp-1);
		push(temp);
		temp++;
		type_r = 0;
	}
	else if(dest->arg3->type == REAL_ && tocpy->arg3->type == REAL_)
	{
		printf("\tfp%d <- r_copy fp%d\n",fp, fp-1);
		push(fp);
		fp++;
		type_r = 1;
	}
	else
	{
		printf("\tfp%d <- itor t%d\n",fp,temp-1);
		fp++;
		printf("\tfp%d <- r_copy fp%d\n",fp, fp-1);
		push(fp);
		fp++;
		type_r = 1;
	}
}

/*
	if it's an id assign, then just copy the value
	if it's not a boolean exp, then just call ir_exp()

	else, if its boolean exp, there are 3 special cases:
		AND and OR: call ir_bool(), then create a new label (so that jumps and/or cjumps match with labels)
		NOT: calls ir_assign() first if "NOT exp" contains either AND or OR
*/

void ir_assign(id id_, expression exp)
{
	if(exp->kind == atom_exp && exp->u.atomic_exp_.arg1->kind == ID_)
	{
		id id2 =  exp->u.atomic_exp_.arg1->u.id_.arg1;	
		ir_cpy(id_, id2);
	}
	else if (id_->arg3->type != BOOL_)	// if it's not a bool assign
		ir_exp(exp);
	else		// if its bool assign (these are special cases)
	{
		if(exp->kind == binop && (exp->u.bin_op.op_->op == OR_ 
			|| exp->u.bin_op.op_->op == AND_))
		{
			ir_bool(exp,1);
			int t = pop();						// result of the expression
			int new_label = pop(); 				// correct label to follow  after copy
			int t2 = pop(); 					// previous register that contained the original value of the compare op in the first comparison
			printf("\tt%d <- i_copy t%d\n",t2,t);
			push(t2);			// back in the Stack

			printf("l%d: \n",new_label);		// label to follow (so jumps and cjumps match with labels)
			label++;		
		}
		else if(exp->kind == unop && exp->u.un_op.op_->op == NOT_)
		{
			if(exp->u.un_op.arg1->kind == binop 
				&& (exp->u.un_op.arg1->u.bin_op.op_->op == OR_ 
				|| exp->u.un_op.arg1->u.bin_op.op_->op == AND_))	// check for special case (because of the copy instruction)
				ir_assign(id_,exp->u.un_op.arg1);

			ir_id(id_,0);	// load
			printf("\tt%d <- not t%d\n", temp, temp-1);
			push(temp);
			temp++;
		}
		else if(exp->kind == binop && (exp->u.bin_op.op_->op == GE_ 
				|| exp->u.bin_op.op_->op == NE_ || exp->u.bin_op.op_->op == LE_)) // if the assign is just : var bool x = n >= 0 (for example)
		{
			ir_exp(exp);
			int t = pop();	// result of cmp

			printf("\tt%d <- not t%d\n",temp,t); // negate the result
			push(temp);
			temp++;
		}
		else	// if none of these special cases, then ...
			ir_exp(exp);

		type_r = 0;		// last register was a "t"
	}
		
	ir_id(id_,1);	// store
}	

void ir_print(expression exp)
{
	ir_bool(exp,0);	
	int t = pop();

	if((exp->kind == binop && exp->u.bin_op.arg3->type == INT_) 
			|| (exp->kind == unop && exp->u.un_op.arg2->type == INT_) 
			|| (exp->kind == atom_exp && exp->u.atomic_exp_.arg2->type == INT_))
		printf("\ti_print t%d\n", t);
	else if ((exp->kind == binop && exp->u.bin_op.arg3->type == REAL_) 
			|| (exp->kind == unop && exp->u.un_op.arg2->type == REAL_) 
			|| (exp->kind == atom_exp && exp->u.atomic_exp_.arg2->type == REAL_))
		printf("\tr_print fp%d\n",t);
	else
		printf("\tb_print t%d\n",t);
}

// count the number of consective ors in expressions
int count_ors(expression exp)
{
	if(exp->u.bin_op.op_->op != OR_)
		return 0;
	else
		return (1 + count_ors(exp->u.bin_op.arg1) 
			+ count_ors(exp->u.bin_op.arg2));
}

// count the number of consective ands in expression
int count_ands(expression exp)
{
	if(exp->u.bin_op.op_->op != AND_)
		return 0;
	else
		return (1 + count_ands(exp->u.bin_op.arg1) 
			+ count_ands(exp->u.bin_op.arg2));
}

/* 
	Called before ir_exp() because needs to check for 3 special cases, AND, OR or NOT, 
	if none of these just calls ir_exp()

	i: 
 	  -	1 : assign 
 	  -	0 : default
	  - 2 : return (return in a seperate label for bool type 
	  				if contains ANDS or ORS( so the labels match with jumps and cjumps))
	  - 3 : actual args 

	for AND, OR and NOT , there will be another call to ir_bools() 
	because of the possible cenario of multiple ANDs and/or ORs and/or NOTs
	in the same expression. But will call again with default value ( i = 0 ).
*/

void ir_bool(expression exp, int i)
{
	if(exp->kind == binop)
	{	
		if(exp->u.bin_op.op_->op == AND_ || exp->u.bin_op.op_->op == OR_)
		{
			int bin_op;
			if(exp->u.bin_op.op_->op == AND_)
				bin_op = 1;
			else if(exp->u.bin_op.op_->op == OR_)
				bin_op = 0;

			ir_bool(exp->u.bin_op.arg1,0);	// call again but this time with default value
			int t = pop();
			int n;

			if(bin_op == 1)
				n = count_ands(exp);	// number of consecutive ands
			else 
				n = count_ors(exp);		// number of consecutive ors

			if(i == 1)// if its an assign, push the previous result register back in the stack and the label
			{ 			// so the correct register can be copied 
				push(t); // register
				push(label+n);  // label
			}
			else if(i == 3) 	// if it's an actual arg, just push the register
				push(t);

			// label+n  because it no longer needs to check the other conditions if it's false (it jumps +n being n the number of consecutive ANDS)
			// or it it's true ( +n being number of consecutive ORs)
			// (or label+n+1) -> so it jumps to the correct label (for matching purposes)
			if(exp->kind == binop && (exp->u.bin_op.op_->op == GE_ 
				|| exp->u.bin_op.op_->op == NE_ || exp->u.bin_op.op_->op == LE_))
			{
				if(bin_op == 1)
				{
					if(i == 0)
						printf("\tcjump t%d, l%d, l%d\n", t, label+n+1, label); // needs to jump down one more label (so it matches with other labels)
					else
						printf("\tcjump t%d, l%d, l%d\n", t, label+n, label);
				}
				else
					printf("\tcjump t%d, l%d, l%d\n", t, label, label+n);
			}
			else
			{	
				if(bin_op == 1)
				{
					if ( i == 0)
						printf("\tcjump t%d, l%d, l%d\n", t, label, label+n+1);
					else
						printf("\tcjump t%d, l%d, l%d\n", t, label, label+n);
				}
				else
					printf("\tcjump t%d, l%d, l%d\n", t, label+n, label);
			}

			printf("l%d:\n",label);	
			label++; 

			ir_bool(exp->u.bin_op.arg2,0); // call again but this time with default value

			if(i == 2) 		// if its a return, print another label (so the jumps and cjumps match with labels)
			{
				printf("l%d:\n",label); 
				label++;
			}
			else if( i == 3 )	// actual arg 
			{
				int t2 = pop(); 				// previous register that contained the original value of the cmp op
				printf("\tt%d <- i_copy t%d\n",t,t2);
				push(t);	
				printf("l%d:\n",label); 	// also print another label (so the jumps and cjumps match with labels) 
				label++;
			}
		}
		else
			ir_exp(exp);	// if none of the above	
	}
	else if(exp->kind == unop && exp->u.un_op.op_->op == NOT_)
	{
		ir_bool(exp->u.un_op.arg1,0);
		int t = pop();

		printf("l%d: \n",label);		// same reason as before. New label so the jumps and cjumps match with labels
		printf("\tt%d <- not t%d\n", temp, t);

		push(temp);
		label++;
		temp++;
		type_r = 0;
	}
	else
		ir_exp(exp); // if none of the above
}

void ir_loop(expression exp, stmt st)
{
	printf("l%d: \n", label);	// start

	push(label);	// save the label
	label++;

	ir_bool(exp,0); // generate IR for condition
	int t = pop(); 	// result

	push(label+1);	// store the label
	push(label);	// same here for safekeeping

	if(exp->kind == binop && (exp->u.bin_op.op_->op == GE_ 
		|| exp->u.bin_op.op_->op == NE_ || exp->u.bin_op.op_->op == LE_))
		printf("\tcjump t%d, l%d, l%d\n", t, label+1, label);	
	else	
		printf("\tcjump t%d, l%d, l%d\n", t, label, label+1);
	
	label+=2;

	t = pop();	// get it out of the stack
	
	printf("l%d: \n", t);
	
	if(st != NULL)	// there could be no stmt..
		ir_stmt(st);

	t = pop();		// label to follow after the jump
	int	t2 = pop();	// get original label (now it knows where to jump to) -> jumps to condition
	printf("\tjump l%d\n", t2);
	printf("l%d: \n",t);		
}

void ir_cond(conditional cd)
{
	expression exp = cd->arg1;
	ir_bool(exp,0);
	int t = pop();	// pop the value

	// save the labels
	push(label+1);
	push(label);

	if(exp->kind == binop && (exp->u.bin_op.op_->op == GE_ 
		|| exp->u.bin_op.op_->op == NE_ || exp->u.bin_op.op_->op == LE_))
		printf("\tcjump t%d, l%d, l%d\n", t, label+1, label);	
	else	
		printf("\tcjump t%d, l%d, l%d\n", t, label, label+1);

	label+=2;
	t = pop();	// pop the label
	printf("l%d: \n", t);

	if(cd->arg2 != NULL)		// if the first stmt is not empty
		ir_stmt(cd->arg2);

	t = pop();

	if(cd->arg3 != NULL)		// if the second stmt (= else stmts ) is  not empty 
		printf("\tjump l%d\n",t+1);	// know it knows where to jump (so it doesnt check the else stmt)

	printf("l%d: \n",t);	// label to follow

	if(cd->arg3 != NULL)
	{
		push(label);
		label++;
		ir_stmt(cd->arg3);
		t = pop();		// label to follow
		printf("l%d: \n", t);
	}
}

void ir_stmt(stmt st)
{
	if(st->kind == compound_stmts)
		ir_stmts(st->u.compound_stmts_.arg1);
	else if(st->kind == loop_) 
		ir_loop(st->u._loop.arg1, st->u._loop.arg2);
	else if(st->kind == conditional_) 
		ir_cond(st->u._conditional.arg1);
	else if(st->kind == assign)
		ir_assign(st->u.assigns_.arg1, st->u.assigns_.arg2);
	else if(st->kind == func_call)	
		ir_call(st->u._func_call.arg1,NULL,1);
	else // kind == print_
		ir_print(st->u._prints.arg1);
}


// return of functions, 
/*
	if it's a nil op it means it's a procedure return
	else it's a function return
*/
void ir_return(expression exp)
{	
	if(exp->kind == nil_op)		// procedure
		printf("\treturn\n\n");
	else		// function_call_
	{	
		ir_bool(exp,2);			
		int t = pop();

		if(type_r == 0)
			printf("\ti_return t%d\n\n", t);
		else // type == REAL_
			printf("\tr_return fp%d\n\n",t);
	}	
}

void ir_fun(fundef fun)
{
	char *name = substring(fun->id, 2,strlen(fun->id)-2);
	temp = 0;	// for every new function, reset the temp and fp counter
	fp = 0;
	printf("function @%s\n",name);
	more_vardecls vd = fun->arg2->arg1;

	while(vd != NULL) // var decls
	{ 
		ir_vars(vd->arg1);
		vd = vd->arg2;
	}

	if(fun->arg2->arg2 != NULL)
		ir_stmt(fun->arg2->arg2);	// stmts

	ir_return(fun->arg2->arg3); 	// return exp
}

/* 
	get all the args, 
*/
void ir_actual_args(actual_args args, char *str)
{
	char *buffer = malloc(3+1);		// assuming registers numbers only have max 3 digits (+1 for '\0')

	if(args != NULL && args->arg1 != NULL)  
	{
		expression exp = args->arg1;
		ir_bool(exp,3);
		int t = pop();	

		if(type_r == 0)	
		{
			strcpy(str,"[ t");
			snprintf(buffer, 10, "%d", t);	// convert register number to char array
			strcat(str,buffer);				// concat 
		}
		else	// same as before but for fp
		{
			strcpy(str,"[ fp");
			snprintf(buffer, 10, "%d", t);
			strcat(str,buffer);
		}

		more_actual_args ma = args->arg2;
		while(ma!= NULL)	// are there more args?
		{
			exp = ma->arg1;
			if(exp !=NULL)
			{
				ir_bool(exp,3);
				int t = pop();

				if(type_r == 0)	
				{
					strcat(str,", t");
					snprintf(buffer, 10, "%d", t);
					strcat(str,buffer);
				}
				else // TYPE == REAL_
				{	
					strcat(str, ", fp");
					snprintf(buffer, 10, "%d", t);
					strcat(str,buffer);
				}
			}
				ma = ma->arg2;	// repeat until there are no args left
		}
		strcat(str, " ]");
	}
}

/*
	i = 0 : func call
	i = 1 : proc call
*/
void ir_call(function_call fc, type tp, int i)
{
	char *str = strdup("[]");	
	ir_actual_args(fc->arg2,str);
	
	char *name = substring(fc->arg1, 2,strlen(fc->arg1)-2);

	if(i == 0)			// call funcs
	{
		if(tp->type == INT_ || tp->type == BOOL_)
		{
			printf("\tt%d <- i_call @%s, %s\n", temp, name,str);
			temp++;
		}
		else if(tp->type == REAL_)
		{
			printf("\tfp%d <- r_call @%s, %s\n", fp,name,str);
			fp++;	
		}
	}
	else	// i == 1		 call used for procs
		printf("\tcall @%s, %s \n",name, str);
}

void the_root(global_declarations root)
{

	ast tree = (ast) malloc(sizeof(*tree));
	printf("\n");
	tree->root = root;

	while(root != NULL)
	{
		if(root->un.single_global.arg1->kind == fun_def)
			ir_fun(root->un.single_global.arg1->un.fun.arg1);

		root = root->un.multiple_global.arg2; // global_decls -> global_decls -> ... -> NULL 	
	
	}

	if(root->un.single_global.arg1->kind == fun_def)
	{
		printf("nop");
	}
}

 global_declarations new_global_declarations(global_declaration arg1, global_declarations arg2)
{
	global_declarations ob = (global_declarations) malloc(sizeof(*ob));
	
	if(arg2 != NULL)			// more than one global decl
	{
		ob->kind = multiple;
		ob->un.multiple_global.arg1 = arg1;
		ob->un.multiple_global.arg2 = arg2;
	}
	else
	{
		ob->kind = single;	// only one global decl
		ob->un.single_global.arg1 = arg1;
	}

	return ob;
}

 global_declaration new_global_declaration_decl(vardecls arg1)
{
	global_declaration ob = (global_declaration) malloc(sizeof(*ob));
	ob->kind = var_decls;

	ob->un.vars.arg1 = arg1;

	return ob;
}

 global_declaration new_global_declaration_fun(fundef arg1)
{
	global_declaration ob = (global_declaration) malloc(sizeof(*ob));
	ob->kind = fun_def;

	ob->un.fun.arg1 = arg1;

	return ob;
}

 vardecls new_vardecls(id arg1, expression arg2)
{
	vardecls vd = (vardecls) malloc(sizeof(*vd));
	vd->arg1 = arg1;
	vd->arg2 = arg2;

	return vd;
}

 fundef new_fundef(char *arg1, formal_args arg2, body arg3)
{
		fundef fd = (fundef) malloc(sizeof(*fd));
		fd->id = strdup(arg1);
		fd->arg1 = arg2;
		fd->arg2 = arg3;

		return fd;
}

 formal_args new_formal_args(char *arg1, type arg2, more_formal_args arg3)
{
	formal_args fa = (formal_args) malloc(sizeof(*fa));
	fa->arg1 = strdup(arg1);
	fa->arg2 = arg2;
	fa->arg3 = arg3;

	return fa;

}

 more_formal_args new_more_formal_args(char *arg1, type arg2, more_formal_args arg3)
{
	more_formal_args fa = (more_formal_args) malloc(sizeof(*fa));
	fa->arg1 = strdup(arg1);
	fa->arg2 = arg2;
	fa->arg3 = arg3;

	return fa;
}

body new_body(more_vardecls arg1, stmt arg2, expression arg3)
{
	body bd = (body) malloc(sizeof(*bd));
	bd->arg1 = arg1;
	bd->arg2 = arg2;
	bd->arg3 = arg3;

	return bd;
}

more_vardecls new_more_vardecls(vardecls arg1, more_vardecls arg2)
{
	more_vardecls mv = (more_vardecls) malloc(sizeof(*mv));
	mv->arg1 = arg1;
	mv->arg2 = arg2;

	return mv;
}


// compound stmt
 stmt new_stmt(stmts arg1)
{
	stmt st = (stmt) malloc(sizeof(*st));
	st->kind = compound_stmts;
	st->u.compound_stmts_.arg1 = arg1;

	return st;
}

 stmt new_stmt_loop(expression arg1, stmt arg2)
{
	stmt st = (stmt) malloc(sizeof(*st));
	st->kind = loop_;
	st->u._loop.arg1 = arg1;
	st->u._loop.arg2 = arg2;

	return st;
}

 stmt new_stmt_cond(conditional arg1)
{
	stmt st = (stmt) malloc(sizeof(*st));
	st->kind = conditional_;
	st->u._conditional.arg1 = arg1;

	return st;
}

 stmt new_stmt_assign(id arg1, expression arg2)
{
	stmt st = (stmt) malloc(sizeof(*st));
	st->kind = assign;
	st->u.assigns_.arg1 = arg1;
	st->u.assigns_.arg2 = arg2;

	return st;
}

 stmt new_stmt_call(function_call arg1)
{
	stmt st = (stmt) malloc(sizeof(*st));
	st->kind = func_call;
	st->u._func_call.arg1 = arg1;

	return st;
}

 stmt new_stmt_print(expression arg1)
{
	stmt st = (stmt) malloc(sizeof(*st));
	st->kind = print_;
	st->u._prints.arg1 = arg1;

	return st;
}

 stmts new_stmts(stmt arg1, stmts arg2)
{
	stmts st = (stmts) malloc(sizeof(*st));

	st->arg1 = arg1;
	st->arg2 = arg2;

	return st;
}

 conditional new_conditional(expression arg1, stmt labeltrue, stmt labelfalse)
{
	conditional cd = (conditional) malloc(sizeof(*cd));

	cd->arg1 = arg1;
	cd->arg2 = labeltrue;
	cd->arg3 = labelfalse;

	return cd;
}

 function_call new_function_call(char *arg1, actual_args arg2)
{
	function_call cd = (function_call) malloc(sizeof(*cd));

	cd->arg1 = strdup(arg1);
	cd->arg2 = arg2;

	return cd;
}

 actual_args new_actual_args(expression arg1, more_actual_args arg2)
{
		actual_args cd = (actual_args) malloc(sizeof(*cd));

	cd->arg1 = arg1;
	cd->arg2 = arg2;

	return cd;
}

 more_actual_args new_more_actual_args(expression arg1, more_actual_args arg2)
{
		more_actual_args cd = (more_actual_args) malloc(sizeof(*cd));

	cd->arg1 = arg1;
	cd->arg2 = arg2;

	return cd;
}

 expression new_expression_op(operator arg1, expression arg2, expression arg3, type arg4)
{
	expression exp = (expression) malloc(sizeof(*exp));
	exp->kind = binop;

	exp->u.bin_op.op_ = arg1;
	exp->u.bin_op.arg1 = arg2;
	exp->u.bin_op.arg2 = arg3;
	exp->u.bin_op.arg3 = arg4;

	return exp;
}

 expression new_expression_atom(atomic_expression arg1, type arg2)
{
	expression exp = (expression) malloc(sizeof(*exp));
	exp->kind = atom_exp;

	exp->u.atomic_exp_.arg1 = arg1;
	exp->u.atomic_exp_.arg2 = arg2;

	return exp;
}

// toreal
 expression new_expression_unop(operator arg1, expression arg2, type arg3)
{
	expression exp = (expression) malloc(sizeof(*exp));
	exp->kind = unop;

	exp->u.un_op.op_ = arg1;
	exp->u.un_op.arg1 = arg2;
	exp->u.un_op.arg2 = arg3;

	return exp;
}

 expression new_expression_lit(bool arg1)
{
	expression exp = (expression) malloc(sizeof(*exp));
	
	exp->kind = bool_lit;
	literal lit = (literal) malloc(sizeof(*lit));

	exp->u.boollit.l = lit;
	exp->u.boollit.l->kind = BOOL_LIT;
	exp->u.boollit.l->u.bool_lit_v = arg1;


	return exp;
}

 expression no_exp(enum nil arg1){
	expression exp = (expression) malloc(sizeof(*exp));


	exp->kind = nil_op;
	exp->u.no_return.arg1 = arg1;


	return exp;
}

 atomic_expression new_atomic_expression_id(id arg1)
{
	atomic_expression atexp = (atomic_expression) malloc(sizeof(*atexp));

	atexp->kind = ID_;
	atexp->u.id_.arg1 = arg1;

	return atexp;
}

 atomic_expression new_atomic_expression_call(function_call arg1)
{
	atomic_expression atexp = (atomic_expression) malloc(sizeof(*atexp));

	atexp->kind = function_call_;
	atexp->u.func_call.arg1 = arg1;

	return atexp;
}

 atomic_expression new_atomic_expression_lit(literal arg1)
{
	atomic_expression atexp = (atomic_expression) malloc(sizeof(*atexp));

	atexp->kind = literals_;
	atexp->u.literal_.arg1 = arg1;

	return atexp;
}

 id new_id(char *arg1, kind arg2, type arg3)
{
	id ident = (id) malloc(sizeof(*ident));

	ident->arg1 = strdup(arg1);
	ident->arg2 = arg2;
	ident->arg3 = arg3;

	return ident;
}

 literal new_literal_int(int value)
{
	literal lit = (literal) malloc(sizeof(*lit));

	lit->kind = INT_LIT;
	lit->u.int_lit_v = value;


	return lit;
}

 literal new_literal_real(double value)
{
	literal lit = (literal) malloc(sizeof(*lit));

	lit->kind = REAL_LIT;
	lit->u.real_lit_v = value;

	return lit;
}

 literal new_literal_bool(bool value)
{
	literal lit = (literal) malloc(sizeof(*lit));

	lit->kind = BOOL_LIT;
	lit->u.bool_lit_v = value;
	

	return lit;
}

 kind new_kind(enum kind_ arg1){
	kind kd = (kind) malloc(sizeof(*kd));
	kd->kind = arg1;

	return kd;
}

 type new_type(enum type_ arg1){
	type kd = (type) malloc(sizeof(*kd));

	kd->type = arg1;

	return kd;
}

 operator new_operator(enum op_ arg1)
{
	operator kd = (operator) malloc(sizeof(*kd));

	kd->op = arg1;

	return kd;
}
