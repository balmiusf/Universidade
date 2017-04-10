:-dynamic(diag/1).
:-dynamic(diag2/1).

tamanho_quadrado(16).
tamanho_linha(4).

estado_inicial(e(Vars, [], Domain),SideSize) :-
	gerarVars(Vars, SideSize),
	MaxD is SideSize*SideSize,
	findall(D, between(1, MaxD, D), Domain),!.

gerarVars(Vars, SideSize) :-
	gerarVars(Vars, SideSize, 0).
	
gerarVars([], SideSize, M) :-
	M is SideSize * SideSize.
	
gerarVars([v(n(CordX, CordY), _) | T], SideSize, Count) :-
	CordX is Count mod SideSize,
	CordY is Count // SideSize,
	Count2 is Count + 1,
	gerarVars(T, SideSize, Count2).
	
ve_restricoes(E):- 
	tamanho_linha(Linha),
	soma(Soma),
	ver_quadrado(E),
	ver_linhas(E,T,M),
	ver_colunas(E,T2,M2),
	ver_Diag1(E,T3,M3),
	ver_Diag2(E,T4,M4),
	
	( T = Linha -> M = Soma; true),
	( T2 = Linha -> M2 = Soma; true),
	( T3 = Linha -> M3 = Soma; true),        
	( T4 = Linha -> M4 = Soma; true).
	
soma(Soma):- tamanho_linha(Linha), Linha = 3, Soma is 15.		% 3x3
soma(Soma):- tamanho_linha(Linha), Linha = 4, Soma is 34.		% 4x4
soma(Soma):- tamanho_linha(Linha), Linha = 5, Soma is 65.		% 5x5
soma(Soma):- tamanho_linha(Linha), Linha = 6, Soma is 111.	% 6x6	


ver_Diag2(e(_,[v(n(X,Y), V)|R],_),T,M)	:-
		findall((X1,Y1,V1),member(v(n(X1,Y1),V1),R),L), 
		tamanho_quadrado(SquareSize), length([(X, Y, V)|L], SquareSize_2),
		( SquareSize = SquareSize_2  -> run_diag2([(X, Y, V)|L], Result),diag2(Ls), diff(Ls), length(Ls,T), sum_list(Ls, M); true).
	
ver_Diag1(e(_,[v(n(X,Y), V)|R],_),T,M)	:-
		findall((X1,Y1,V1),member(v(n(X1,Y1),V1),R),L), 
		tamanho_quadrado(SquareSize), length([(X, Y, V)|L], SquareSize_2),
		( SquareSize = SquareSize_2 -> run_diag([(X, Y, V)|L], Result),diag(Ls), diff(Ls), length(Ls,T), sum_list(Ls, M); true).
	
ver_quadrado(e(_,[v(n(X,Y), V)|R],_))	:-
	findall(V1,member(v(n(_,_),V1),R),L), diff([V|L]).
	
ver_linhas(e(_,[v(n(X,Y), V)|R],_),T,M)	:-
	findall(V1,member(v(n(X,_),V1),R),L), diff([V|L]),
	length([V|L],T), sumList([V|L],M).
	
ver_colunas(e(_,[v(n(X,Y), V)|R],_),T,M)	:-
	findall(V1,member(v(n(_,Y),V1),R),L), diff([V|L]),
	length([V|L],T), sumList([V|L],M).

	%3*3. adicionar mais valores a lista para 4*4 5*5
	
run_diag([], [V1, V2, V3,V4]) :- retractall(diag(_)), assertz(diag([V1, V2, V3,V4])).

run_diag([(X, Y, V)|L], []):-
	( X = Y -> run_diag(L, [V]); run_diag(L, [])).

run_diag([(X, Y, V)|L], D) :-
	( X = Y -> merge([V], D, N), run_diag(L, N); run_diag(L, D)).	
	
run_diag2([], [V1, V2, V3,V4]) :- retractall(diag2(_)), assertz(diag2([V1, V2, V3,V4])).

run_diag2([(X, Y, V)|L], []):-
	 tamanho_linha(C),
	 F is C-1,
	 Z is X+Y,
	( Z = F -> run_diag2(L, [V]) ; run_diag2(L, [])).

run_diag2([(X, Y, V)|L], D) :-
		tamanho_linha(C),
		F is C-1,
		Z is X+Y,
	( Z = F -> merge([V], D, N), run_diag2(L, N) ; run_diag2(L, D)).		
	
merge([], L, L).
merge([H|T], L, [H|M]) :-
	merge(T, L, M).
	
sumList([],0).
sumList([H|L],N):- sumList(L,M), N is M + H.	

diff([]).
diff([H|T]):- \+member(H,T), diff(T).

esc(L):- sort(L,L1), write(L1), nl, esc1(L1),nl.

esc1(L):- tamanho_quadrado(Size),nl, esc_q(L,1,Size).

esc_q([v(n(CoordX,CoordY),X)],S,S):- write(X),nl.

esc_q([H|T],CurrSize,Size):- 
	CurrSize < Size, 
	CurrSize2 is CurrSize +1,
	H = v(n(CoordX,CoordY),X), 
	write(X),write(' '),
	change_line(CurrSize,Size),
	esc_q(T,CurrSize2,Size).

change_line(CurrSize,Size):-
	tamanho_linha(Linha),
	X is abs(CurrSize-Size),
	R is X mod Linha,
	(R = 0 -> nl; write('')).