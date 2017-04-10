% gera o estado inicial 
tamanho_linha(9).

estado_inicial(E):-
	estado_inicial2(E1),		% criar matriz com variaveis nao instanciaveis
	initializar(E1,E).			% preencher sudoku com posicoe

estado_inicial2(e(Vars, [])) :-
	gerarVars(Vars, 9),!.

	
gerarVars(Vars, SideSize) :-
	gerarVars(Vars, SideSize, 0,0).
	
gerarVars([], SideSize, M,_) :-
	M is SideSize * SideSize.
	
gerarVars([v(n(CordX, CordY,Q),D, V) | T], SideSize, Count,ValorPos) :-
	D = [1,2,3,4,5,6,7,8,9],
	
	CordX is Count mod SideSize,
	CordY is Count // SideSize,
	
	Count2 is Count + 1,
	
	qual_quadrante(ValorPos, Count2,Q), % verifica em qual quadrante corresponde a coordenada
	
	(ValorPos = 8 -> ValorPos2 is 0; ValorPos2 is ValorPos + 1),
	
	gerarVars(T, SideSize, Count2,ValorPos2).

% verifica em qual conjunto de linhas está
% por exemplo 
% < 28 -> entre as 3 primeiras linhas, isto é, está entre o quadrante 1, 2 e 3
	
qual_quadrante(ValorPos,Counter, Q):- 
   ((Counter < 28 	->  qual_quadrante2(ValorPos,Q));
	(Counter < 55 	-> 	qual_quadrante3(ValorPos,Q));
	(Counter < 82 	-> 	qual_quadrante4(ValorPos,Q) ; true)).
	
% verifica qual quadrante pertence a coordenada

qual_quadrante2(Valor,Q):- Valor < 3, Q = q1.	
qual_quadrante2(Valor,Q):- Valor < 6, Q = q2.
qual_quadrante2(Valor,Q):- Valor < 9, Q = q3.

qual_quadrante3(Valor,Q):- Valor < 3, Q = q4.	
qual_quadrante3(Valor,Q):- Valor < 6, Q = q5.
qual_quadrante3(Valor,Q):- Valor < 9, Q = q6.

qual_quadrante4(Valor,Q):- Valor < 3, Q = q7.	
qual_quadrante4(Valor,Q):- Valor < 6, Q = q8.
qual_quadrante4(Valor,Q):- Valor < 9, Q = q9.

% para preencher as posicoes a escolha

initializar(E,NE):-

	L1 = [v(n(7,7,q9),[1,2,3,4,5,6,7,8,9],7)],
	L2 = [v(n(1,7,q7),[1,2,3,4,5,6,7,8,9],5)],
	L3 = [v(n(1,0,q1),[1,2,3,4,5,6,7,8,9],7)],
	L4 = [v(n(7,4,q6),[1,2,3,4,5,6,7,8,9],1)],

	inserir(L1,E,E2),
	inserir(L2,E2,E3),
	inserir(L3,E3,E4),
	inserir(L4,E4,NE).

% cria um novo estado. 	
% para o primeiro preenchimento 
	
inserir(L,  e(NInst,[]), e(NInst2, Inst)):-
	inserir_1(NInst, L, NInst2, Inst).

% para preenchimentos posteriores
	
inserir(L, e(NInst,List),e(NInst2, Inst)):-
	length(List,N), N > 0,
	inserir_1(NInst, L, NInst2, Inst2),
	append(List,Inst2,Inst).
	
inserir_1([v(n(X,Y,Q),D, V)], L, [v(n(X,Y,Q),D, V)], []):-
    \+member(v(n(X,Y,Q),D, V), L).

inserir_1([v(n(X,Y,Q),D, V)], L, [], [v(n(X,Y,Q),D, V)]):-
    member(v(n(X,Y,Q),D, V), L).

inserir_1([v(n(X,Y,Q),D, V)|T], L, [v(n(X,Y,Q),D, V)|T2], R):-
	\+member(v(n(X,Y,Q),D, V), L),
	inserir_1(T, L, T2, R).

inserir_1([v(n(X,Y,Q),D, V)|T], L, T2, [v(n(X,Y,Q),D, V)|R]):-
	member(v(n(X,Y,Q),D, V), L),
	inserir_1(T, L, T2, R).	

	
ver_linhas(e(_,[v(n(X,Y,_),D, V)|R]))	:-
	findall(V1,member(v(n(X,_,_),_,V1),R),L), diff([V|L]).
	
ver_colunas(e(_,[v(n(X,Y,_),D, V)|R]))	:-
	findall(V1,member(v(n(_,Y,_),_,V1),R),L), diff([V|L]).	
	
ver_q(LI,QualQ,ListQ):-
	findall(V1,member(v(n(X,Y,QualQ),_,V1),LI),ListQ).

	% verifica cada quadrante invidualmente
	
ver_quadrantes(e(_,LI)):-
	ver_q(LI,q1,Q1),
	diff(Q1),
	
	ver_q(LI,q2, Q2),
	diff(Q2),
	
	ver_q(LI,q3, Q3),
	diff(Q3),
	
	ver_q(LI,q4, Q4),
	diff(Q4),
	
	ver_q(LI,q5, Q5),
	diff(Q5),
	
	ver_q(LI,q6, Q6),
	diff(Q6),
	
	ver_q(LI,q7, Q7),
	diff(Q7),
	
	ver_q(LI,q8, Q8),
	diff(Q8),
	
	ver_q(LI,q9, Q9),
	diff(Q9).


ve_restricoes(E):-
 	ver_linhas(E),
	ver_colunas(E),
	ver_quadrantes(E).
	
% verifica se é tudo diferente
	
diff([]).
diff([H|T]):- \+member(H,T), diff(T).

% reduz o dominio de uma linha , coluna e quadrante

forward_checking(_,_,[],[]):- !.
forward_checking(n(X,Y,Q),V,OldR,NewR):-
	change_linha(X,Y,V,OldR,NewR2),			
	change_coluna(X,Y,V,NewR2,NewR3),
	change_quadrante(Q,V,NewR3,NewR).
	
change_quadrante(_,_,[],[]):- !.

change_quadrante(Q1,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),D,_)|NR]):-
	Q1 \= Q,
	change_quadrante(Q1,V,R,NR).
	
change_quadrante(Q1,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),NovoD,_)|NR]):-
	Q1 = Q,
	subtract(D,[V],NovoD),!,
	change_quadrante(Q1,V,R,NR).


% change_linha altera só a linha em questao
	
change_linha(X,Y,V,[H|R],[H|R]):-
	X = 8,!.	
	
change_linha(X,Y,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),NovoD,_)|R]):-
	\+(X=8),
	CX = 8,
	subtract(D,[V],NovoD),!.
		
change_linha(X,Y,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),NovoD,_)|NR]):-
	CX < 8,
	subtract(D,[V],NovoD),
	!,
	change_linha(X,Y,V,R,NR).
	
% change_coluna, percorre coluna X e altera o dominio 	
	
change_coluna(X,Y,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),D,_)|NR]):-
	\+(X = CX), % se nao tiver alinhado
	change_coluna(X,Y,V,R,NR).
	
change_coluna(X,Y,V,[H|R],[H|R]):-
	Y = 8,!.	% se ja ta no fim, termina

% se ta alinhado e ainda nao chegou ao fim
change_coluna(X,Y,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),NovoD,_)|NR]):-
	X = CX,	
	CY < 8, 
	subtract(D,[V],NovoD),!,
	change_coluna(X,Y,V,R,NR).

% se ta alinhado e ja chegou ao fim	
change_coluna(X,Y,V,[v(n(CX,CY,Q),D,_)|R],[v(n(CX,CY,Q),NovoD,_)|R]):-
	\+(Y=8),
	X = CX,
	CY = 8,
	subtract(D,[V],NovoD),!.
	
 	

	
esc(L):-sort(L, L1), write(L1),nl, esc_a(L1),nl.
esc_a(L):- nl, esc_l(L, 1, 9).

esc_l([H], S, S):-
	H = v(_,_,X), write(X), nl.

esc_l([H|T], S, S):-
	H = v(P, _, V), write(V),
	P = n(X, _,_),
	esc_line(X, 9),
	esc_l(T, 1, S).

esc_l([H|T], I, S):- 
	I<S, I2 is I+1,
	H = v(_,_,X), write(X),esc_aux(I),
	esc_l(T, I2, S).

esc_aux(X):-
	R is X mod 3,
	R=0, 
	write(' | ').
esc_aux(X):-
	R is X mod 3,
	R \= 0,
	write(' ').

esc_line(P, _):-
	R is P mod 3,
	R \= 0, nl.
esc_line(P, S):-
	R is P mod 3,
	R = 0,
	nl.