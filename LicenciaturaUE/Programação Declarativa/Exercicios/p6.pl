% localization 
% N -> point
% X -> X coordinate
% Y -> Y coordinate

% l(N,X,Y)

l(a,1,2).
l(b,5,2).
l(c,3,3).
l(d,4,1).
l(e,4,4).
l(f,3,6).
l(g,6,6).
l(h,6,3).

p(a,b).
p(a,c).
p(b,e).
p(c,e).
p(c,d).
p(d,h).
p(e,f).
p(e,h).
p(f,g).
p(g,h).

c(a,3).
c(b,2).
c(c,8).
c(d,-2).
c(e,5).
c(f,7).
c(g,1).
c(h,4).

% caminho
% solution:
caminho(A,B,[A,B]) :- p(A,B).
caminho(A,B,[A|K]):- p(A,C), caminho(C,B,K).
	 
custo([],_).
custo([X],Y) :- c(X,Y).
custo([X|T],Z) :- c(X,Y), custo(T,Z1), Z is Z1 + Y.  


adjacente(A,L) :- 
			F =.. [p,A,Y],
			findall(Y,F,L).	


  printlist([]).
    
    printlist([X|List]) :-
        write(X),nl,
        printlist(List).			
			
% interpretador de movimento ( nao e o do exercicio)

agent :- repeat , read(X) ,
( X= stop -> true ; agent(X) , fail ).

agent(init):- l(a,X,Y), asserta(pos(X,Y)).
agent(init2) :- 
			read(TEMP), 
			l(TEMP,X,Y), 
			asserta(pos(X,Y)).

agent(jump(N)) :- 	
		l(N,X,Y),
		move(X,Y).

agent(go(N)) :- l(N,X,Y), move(X,Y).
		
agent(look):- 	
		retract(pos(X,Y)), 
		l(NODE,X,Y), 
		adjacente(NODE,L), 
		printlist(L), 
		asserta(pos(X,Y)).
		
agent( loc ) :- 
		pos(X ,Y ), 
		write( pos(X , Y )) , nl.

move(DX , DY ) :- 
		retract( pos(X , Y )) ,
		asserta( pos(DX , DY )).
