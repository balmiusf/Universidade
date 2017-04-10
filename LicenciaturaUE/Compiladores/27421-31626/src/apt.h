#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct funcCall *funcCall;
typedef struct calc_exp *calc_t_exp;
typedef struct expBools *expBools; 
typedef struct ids *belos_ids;
typedef struct afects *afects;
typedef struct afect *afect;
typedef struct stmts *stmts;
typedef struct funcdeclar2 *more_args;
typedef struct funcdeclar *funcdeclar;
typedef struct literalExp *literalExp;
typedef struct decls *decls;
typedef struct decl *decl;
typedef struct decl1 *decl1;
typedef struct decl2 *decl2;
typedef struct ifs *ifs;
typedef struct type *type;
typedef struct whiles *whiles;
typedef struct corpo *corpo;
typedef struct corpo_cycle *corpo_cycle;
typedef struct op *op;
typedef struct cycle_kind cycle_kind;
typedef struct nl *nl;

enum cycle_kind_2 {BREAK_,NEXT_};

enum type_kind {INTEGER_,BOOLEAN_,VOID_,FLOATING_,STRING_,ARRAY_,ARRAY_EXP} ;

enum op_kind {EQUALS_,DIFFERENTTHAN_,LESSTHAN_,MORETHAN_,EQUALESSTHAN_,EQUALMORETHAN_,AND_,OR_} ;


struct cycle_kind{
 enum cycle_kind_2 kind;
};

struct type{
  enum type_kind kind;                      

};

struct op{
  enum op_kind kind;
};

struct nl{
  enum{NL_} kind;
  struct{
    nl nl;
  }new_ln;
};

struct funcCall{
  enum{WO_ARGS,W_ARGS,W_EXP,FUNC_CALL} kind;

  union{
    struct{
      char *id;
    }noargs;
    struct{
      char *id;
      belos_ids ids;
    }wargs;
    struct{
      char *id;
      calc_t_exp exps;
    }w_exp;
    struct{
      char *id;
      funcCall arg2;
    }funccalls;
  }u;
};

struct decls{
  enum{DECLS} kind;
  struct{
    decl args1;
    decls args2;
  }declarations;
};

struct decl2{
  enum{FUNC_DECL} kind;
  union{
    struct{
      funcdeclar args1;
      type args2;
      corpo args3;
    }func;
  }u;
};

struct decl1{
  enum{IDS,ASSIGN_,DEFINE_ID,ARRAY_NOARGS,ARRAY_ARGS} kind;
  union{
    struct{
      belos_ids args1;
      type args2;
    }many_ids;
    struct{
      belos_ids args1;
      type args2;
      calc_t_exp args3;
    }assign;
    struct{
      char *id;
      type type;
    }define;
    struct{
      char *id;
      calc_t_exp args1;
      type type;
    }array1;
    struct{
      char *id;
      type type;
    }array2;
  }u;
};

struct decl{
  enum{NORMAL,FUNC} kind;
  union{
    struct{
      decl1 args1;
    }normal;
    struct{
      decl2 args1;
    }func;
  }u;
};

struct whiles{
  enum{WHILE_} kind;
  union{
    struct{
      expBools args1;
      corpo_cycle args2;
    }cycle;
  }u;
};

struct ifs{
  enum{IF_ELSE, IF_ELSE_THEN} kind;
  union{
    struct{
      expBools args1;
      corpo args2;

    }if_else;
    struct{
      expBools args1;
      corpo args2;
      corpo args3;
    }if_else_then;
  }u;
};

struct corpo{
  enum{BODY_STMTS,BODY_NL} kind;
    struct{
      stmts arg1;
      corpo arg2;
    }BODY_STMTS;
};

struct corpo_cycle{
  enum{CYCLE_STMTS,BREAK_2,NEXT_2} kind;
  union{
    struct{
      stmts arg1;
    }stmt;
    struct{
      enum cycle_kind_2 args1;
    }stop;
    struct{
      enum cycle_kind_2 args1;
    }next;
  }u;
};



struct calc_exp {
  enum {EXP_NUM, EXP_BINOP, EXP_ID,EXP_ASSIGN, EXP_PAR,LITERAL} kind;
  
  union {
    struct {
      char *op;
      calc_t_exp arg1;
      calc_t_exp arg2;
    } binop;

    struct 
    {
	   calc_t_exp exp;
    }par;

    struct{
      literalExp lit;
    }literals;
  }u;
};

struct literalExp{
  enum{INT_LITERAL,STRING_LITERAL,BOOL_LITERAL,FLOAT_LITERAL} kind;

  union{
    struct{
      int val;
    }INT;
    
    struct{
      int val;
    }BOOL;

    struct{
      float valfloat;
    }FLOAT;

    struct{
      char *str;
    }STRING;
  }u;
};

struct expBools{
  enum{NEGATE_BOOL,EXP_BINOP_1,EXP_BINOP_2,ID_EXP_BOOL,ID_OP_ID,ID_OP_EXP} kind;

  union{
    struct{
      op op;
      calc_t_exp arg1;
      calc_t_exp arg2;
    }binop;
    struct{
      calc_t_exp arg1;
     op op;
      expBools arg2;
    }binop2;
    struct{
      expBools arg1;
    }negation;
    struct{
      expBools arg1;
    }par;
    struct{
      char *arg1;
    }id;
    struct{
      char *arg1;
      op op;
      calc_t_exp arg3;
    }id_op_exp;
    struct{
      char *arg1;
      op op;
      char *arg2;
    }id_op_id;
  }u;
};

struct ids{
  enum{ID_SOLO,MULTIPLE_IDS} kind;
  union{
    char *id;
    
    struct{
      char *id;
      belos_ids more_ids;
    }many_ids;
  }u;
};

struct afects{
  enum{AFECT_1,AFECT_2} kind;
  union{
    struct{
      char *id;
      afects afects;
    }afects;
    struct{
      calc_t_exp arg1;
    }end_afect;
  }u;
};

struct afect{
  enum{AFECT} kind;
  union{
    struct{
      char *id;
      afects afect;
    }afect;
  }u;
};

struct funcdeclar2{
  enum{MORE_ARGS} kind;
  union{
    struct{
      char *id;
       type type;
       more_args args3;
    }mais_args;
  }u;
};

struct funcdeclar{
  enum{WITH_ARGS,NO_ARGS} kind;
  union{
    char *id;
    struct{
      char *id;
      char *first_arg;
      type type;
      more_args args;
    }has_args;
  }u;
};

struct stmts{
  enum{stmts_AFECT,stmts_DECL,stmts_IF,stmts_CYCLE,stmts_RETURN,FUNCCALL} kind;

  union{
    struct{
        decl1 arg1;
    }decl;
    struct{
        ifs arg1;
    }ifs;
    struct{
      whiles arg1;
    }cycle;
    struct{
      calc_t_exp arg1;
    }returns;
    struct{
      afect arg1;
    }afects;
    struct{
      funcCall args1;
    }call;
  }u;
};

// Functions for expression
struct calc_exp *calc_exp_new_literal(literalExp literalExp);
struct calc_exp *calc_exp_new_par(calc_t_exp exp);
struct calc_exp *calc_exp_new_binop(char *op, calc_t_exp arg1, calc_t_exp arg2);

struct expBools *new_exp_bools_1(calc_t_exp arg1, op operador, calc_t_exp arg2);
struct expBools *new_exp_bools_2(calc_t_exp arg1, op operador, expBools arg2);
struct expBools *new_exp_bools_not(expBools arg1);
struct expBools *new_exp_bools_par(expBools arg1);
struct expBools *new_exp_bools_id(char *arg1);
struct expBools *new_exp_bools_id_exp(char *id, op operador, calc_t_exp args2);
struct expBools *new_exp_bools_id_exp_2(char *id, op operador, char *id2);

struct ids *new_ids_solo(char *id);
struct ids *new_ids_more(char *id, belos_ids ids);
struct afects *new_afects(char *id, afects afects);

struct afects *new_afects_end(calc_t_exp arg1);
struct afect *new_afect(char *id, afects afects);
struct funcdeclar *new_func_args(char *id, char *id2,  type type, more_args funcdeclar2);
struct funcdeclar *new_func_no_args(char *id);
struct funcdeclar2 *new_func_args_2(char *id,  type type, more_args funcdeclar2);
struct stmts *new_stmts(stmts stmts);
struct decl *new_decl_normal(decl1 args1);
struct decl *new_decl_func(decl2 args1);
struct decls *new_decls(decl args1, decls args2);
struct ifs *new_ifs(expBools args1, corpo args2, corpo args3);
struct whiles *new_whiles(expBools args1, corpo_cycle args2);
struct corpo *new_corpo(stmts args1, corpo args2); 
struct corpo_cycle *new_corpo_cycle(stmts args1);
struct corpo_cycle *new_corpo_cycle_break(enum cycle_kind_2 kind);
struct corpo_cycle *new_corpo_cycle_next(enum cycle_kind_2 kind);
struct decl1 *new_decl1_wo_type(belos_ids ids,  type type);
struct decl1 *new_decl1_type(belos_ids ids,  type type, calc_t_exp exp);
struct decl1 *new_decl1_define(char *id, type type);
struct decl1 *new_decl1_array(char *id, calc_t_exp exp,type type);

struct decl2 *new_decl2(funcdeclar args1, type type, corpo corpo);

struct literalExp *new_literal_int(int n);
struct literalExp *new_literal_string(char *id);
struct literalExp *new_literal_float(float n);
struct literalExp *new_literal_bool(int n);

struct stmts *new_stmts_decl(decl1 args1);
struct stmts *new_stmts_cond(ifs ifs);
struct stmts *new_stmts_cycle(whiles whiles);
struct stmts *new_stmts_return(calc_t_exp arsg1);
struct stmts *new_stmts_afect(afect args1);
struct stmts *new_stmts_funcCalls(funcCall args1);

struct type *new_type(enum type_kind type);
struct op *new_op(enum op_kind op);

struct funcCall *new_function_calls_no_args(char *id);
struct funcCall *new_function_calls_args(char *id, belos_ids ids);
struct funcCall *new_function_calls_exp(char *id,calc_t_exp exp);
struct funcCall *new_function_calls_func(char *id, funcCall arg2);

struct nl *new_line(nl nl);

