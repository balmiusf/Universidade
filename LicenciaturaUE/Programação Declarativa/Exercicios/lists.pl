% exercicio 1
% lista(L)

lista([]).
lista([_|C]) :- lista(C).

% exercicio 2
% nesimo(L,N,X)
% funciona so para a alinea a)

nesimo([X|_],1,X).
nesimo([_|T],N,X) :- N1 is N-1, nesimo(T,N1,X).

% alinea b) (funciona para a) b) e c) (nao e isto que o prof 

nesimob([X|_],1,X).
nesimob([_|T],N,X) :- nesimob(T,N1,X), N is N1+1.

% quantas vezes ocorre o elemento X na lista
% not nao funciona
occur(_,[],0).
occur(X,[X|L],N) :- occur(X,L,N1), N is N1+1.
% occur(X,[Y|L],N) :- X!=, occur(X,L,N).


% soma os elementos da lista

sumList([],0).
sumList([H|L],N):- sumList(L,M), N is M + H.

% add up list

add_up_list(L,K) :- add_up_list_aux(L,K,0).
add_up_list_aux([],[],_).
add_up_list_aux([X|T],[X1|T1],Z) :- X1 is X + Z, add_up_list(T,T1,X1).

% last element

mylast(X,[X]).
mylast(X,[_|L]) :- mylast(X,L).

% find the last but one element

notLast(X,[X,Y]).
notLast(X,[_|L]) :- notLast(X,L).

% number of elements in a list

lenght([],0).
lenght([X|T],N):- lenght(T,M), N is M + 1.


% duplicate

dup([],[]).
dup([X],[X,X]).
dup([X|L],[X,X|L1]) :- dup(L,L1).

% chop list

chop(L,0,[],L).
chop([X|T],N,[X|T1],L2) :- M is N-1, chop(T,M,T1,L2).

% insert element in list

insert(X,[],0,[X]).
insert(X,[X1|T],N,[X2|T]):- insert(X,T,M,T), M is N - 1. 

sel(M , [ M | Y ] , Y ).
sel(M , [ N | X ] , [ N | Y ]) :- sel(M , X , Y ).

% create list 

range(N,N,[N]).
range(N1,N2,[N1|T]) :- N1 < N2, M1 is N1 + 1, range(M1,N2,T). 

% mix

mix([],[],[]).
mix([X|T],[],[X|T]).
mix([],[Y|T1],[Y|T1]).
mix([X|T],[Y|T1],[X,Y|T2]):- mix(T,T1,T2). 

% troca X por Y em L1 e da L2
% stand by
subst(_,_,[],[]).
subst(X,Y,[X,Y],[Y,X]).
% subst():- (X,Y,T,

% sub listas

sublist([],L).
sublist([X|T],[X|T1]):- sublist(T,T1).
sublist(T,[_|T1]):- sublist(T,T1).

% replace
replace([],_,_,[]).
replace([X|T],X,Y,[Y|T2]):- replace(T,X,Y,T2).
replace([X1|T],X,Y,[X1|T2]) :- replace(T,X,Y,T2).

%insert in N=0 

insert_0(X,[],[X]).
insert_0(X,[H|T],[X,H|T]).

% insert at end

insert_end(X,[],[X]).
insert_end(X,[H|T],[H|T1]) :- insert_end(X,T,T1). 

% insert at N

insert_n(X,0,[],[X]).
insert_n(X,0,[H|T],[X,H|T]).
insert_n(X,N,[H|T],[H|T1]) :- M is N-1, insert_n(X,M,T,T1).

% remove one

sel(M , [ M | Y ] , Y ).
sel(M , [ N | X ] , [ N | Y ]) :- sel(M , X , Y ).

% remove all ocurrences

remove_all(_,[],[]).
remove_all(N,[N|T],T1):- remove_all(N,T,T1).
remove_all(N,[H|T],[H|T1]) :- remove_all(N,T,T1).

% se sao adjacentes

adj(X,Y,[X,Y]).
adj(X,Y,[X,Y|_]).
adj(X,Y,[X1|T1]):- adj(X,Y,T1).

% sem duplicados

member1(X,[H|_]).
member1(X,[_|T]) :- member1(X,T).
 
distinct([],[]).
distinct([H|T],C) :- member1(H,T), distinct(T,C).
distinct([H|T],[H|C]) :- distinct(T,C).

% pack

pack([],[]).
pack([X],[[X|Xs]]).
pack([X|T],[[X|Xs]|T1]) :- pack(T,T1).

% compress list ( eliminate duplicates )

compress([],[]).
compress([X],[X]).
compress([X,X|Xs],Zs) :- compress([X|Xs],Zs).
compress([X,Y|Ys],[X|Zs]) :- X \= Y, compress([Y|Ys],Zs).

compress2([],[]).
compress2([X],[X]).
compress2([X,X|T],[X|T1]) :- compress(T,T1).
compress2([X,Y|T],[X,Y|T1]) :- compress(T,T1).

% append2
append2(T,[],T).
append2([],T,T).
append2([X|XS],T,[X|ZS]):- append2(XS,T,ZS).

% union

union([],X,X).
union(X,[],X).
union([X1|T],X,[X|T1]):- append2(T,X,T1).

% member 
  member(X,[X|_]).
   member(X,[_|L]) :- member(X,L).

% intersection - o not member e para impedir que o programa termine logo quando encontra algo que nao pertence a Y

inter([],_,[]).
inter([X|L],Y,T1) :- not(member(X,Y)),inter(L,Y,T1).
inter([X|T],Y,[X|T1]):- member(X,Y), inter(T,Y,T1).

% diff

diff([],_,[]).
diff([X|T],Y,T1):- member(X,Y), diff(T,Y,T1).
diff([X|T],Y,[X|T1]):- not(member(X,Y)),diff(T,Y,T1).

% prefix

prefixo([] , _ ).
prefixo([ X | P ] , [ X | L ]) :- prefixo(P , L ).

% prefix 2

prefixo2([],_).
prefixo2([X|P],L) :- member(X,L), prefixo2(P,L).



