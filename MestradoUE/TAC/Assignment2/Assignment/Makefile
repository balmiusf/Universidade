CC = gcc -Wall
YACC = bison -d
LEX = flex

# - ll because of OS X

tacl : ir.tab.c lex.yy.c
	$(CC) $^ ir.c lists.c -o $@ -ll

ir.tab.c : ir.y 
	$(YACC) $^

lex.yy.c : ir.lex
	$(LEX) $^

run-1 : tacl
	@./tacl < exemplos-2/twice.ir2

run-2 : tacl
	@./tacl < exemplos-2/factorial.ir2

run-3 : tacl
	@./tacl < exemplos-2/fig-9.ir2

run-4 : tacl
	@./tacl < exemplos-2/ragbag.ir2

run-5 : tacl
	@./tacl < exemplos-2/triangular.ir2

clean :
	@$(RM) tacl
	@$(RM) ir.tab.c ir.tab.h
	@$(RM) lex.yy.c