CC = gcc
CFLAGS = -g
OUTFILE = YA.out
LIBS = -lm


all: parser.c lexer.c apt.o
	$(CC) $(CFLAGS) parser.c lexer.c apt.o -o $(OUTFILE) $(LIBS)

parser.c: YA.y
	bison -y -d YA.y -o parser.c

lexer.c: YA.lex
	flex -o lexer.c YA.lex

apt.o: apt.c apt.h
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -rf parser.c lexer.c parser.h
	rm -f *~
	rm -f *.o
	rm -f YA.out
