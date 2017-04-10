CC = gcc -Wall
YACC = bison -d
LEX = flex

# - ll because of OS X

tacl : ast.tab.c lex.yy.c
	$(CC) $^  stack.c tacl_ir.c -o $@ -ll

ast.tab.c : ast.y 
	$(YACC) $^

lex.yy.c : ast.lex
	$(LEX) $^

clean :
	@$(RM) tacl
	@$(RM) ast.tab.c ast.tab.h
	@$(RM) lex.yy.c