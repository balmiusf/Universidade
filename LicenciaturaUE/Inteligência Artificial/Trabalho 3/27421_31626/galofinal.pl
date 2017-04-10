:-dynamic(quem_ganhou/1).

%(lista com posicoes do tabuleiro, ultima peca jogada)
estado_inicial(
				([(p(1,1), _),(p(1,2), _),(p(1,3), _),
            	(p(2,1), _),(p(2,2), _),(p(2,3), _),
	        	(p(3,1), _),(p(3,2), _),(p(3,3), _)],o)
	        ).

vencedor(quem_ganhou(Vencedor)):- 
	retractall(quem_ganhou(_)), 
	asserta(quem_ganhou(Vencedor)),!.

% O Jogador X comeca a jogar ( como o operador faz switch da jogada, entao comeca com 'o')

%  1 	-> ganhou pc
% -1 	-> ganhou jogador
%  0	-> empate

% ########################################################################################

% valor 
valor((EstadoActual, _), 1, P):-
	check_victoria(EstadoActual),
	quem_ganhou(o),!.

valor((EstadoActual, _), -1, P):-
	check_victoria(EstadoActual),
	quem_ganhou(x),!.

valor((EstadoActual, _), 0, P):- 
	empate(EstadoActual),!.

% ########################################################################################

% terminal
terminal((EstadoActual, _)):-
	check_victoria(EstadoActual);
	empate(EstadoActual).
 
% ########################################################################################

check_victoria(EstadoActual):-
	(victoria_linhas(EstadoActual);
		victoria_colunas(EstadoActual);
		victoria_diagonais(EstadoActual)).

victoria_linhas(EstadoActual):-
	(victoria_linha(EstadoActual,1);
		victoria_linha(EstadoActual,2);
		victoria_linha(EstadoActual,3)).

victoria_colunas(EstadoActual):-
	(victoria_coluna(EstadoActual,1);
		victoria_coluna(EstadoActual,2);
		victoria_coluna(EstadoActual,3)).

victoria_coluna(EstadoActual,Y):-
	findall(V, (member((p(_,Y),V),EstadoActual), atom(V)),L),
	verifica_victoria(L,_).

victoria_linha(EstadoActual,X):-
	findall(V, (member((p(X,_),V),EstadoActual), atom(V)),L),
	verifica_victoria(L,_).

victoria_diagonais(EstadoActual):-
	(victoria_diagonais1(EstadoActual,V) ;
		victoria_diagonais2(EstadoActual,V)).

victoria_diagonais1(EstadoActual,Victorious):-
	EstadoActual = 
	[(p(X1,X11), V1),(p(X2,X22), V2),(p(X3,X33), V3), 
	(p(X4,X44), V4),(p(X5,X55), V5),(p(X6,X66), V6), 
	(p(X7,X77), V7),(p(X8,X88), V8),(p(X9,X99), V9)],

	atom(V1), atom(V5),atom(V9),
	L = [V1,V5,V9],

	verifica_victoria(L,Victorious).

victoria_diagonais2(EstadoActual,Victorious):-
	EstadoActual = 
	[(p(X1,X11), V1),(p(X2,X22), V2),(p(X3,X33), V3), 
	(p(X4,X44), V4),(p(X5,X55), V5),(p(X6,X66), V6), 
	(p(X7,X77), V7),(p(X8,X88), V8),(p(X9,X99), V9)],
	
	atom(V3),atom(V5),atom(V7),
	L = [V3,V5,V7],

	verifica_victoria(L,Victorious).

empate(EstadoActual):-
	verifica_empate(EstadoActual), 
	asserta(quem_ganhou(empate)).

verifica_victoria([V1,V2,V3],Victorious):-
	atom(V1),atom(V2),atom(V3),
	V1 = V2,
	V2 = V3,
	Victorious = V1,
	vencedor(quem_ganhou(Victorious)),!.

% se tiver tudo preenchido com algo \= _ entao ha' um empate

verifica_empate([]).
verifica_empate([(p(_,_), V)|T]):-
	atom(V),
	verifica_empate(T).

% #######					 operadores 							#######

op1((EstadoActual,V),jogar11,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((1,1),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar12,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((1,2),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar13,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((1,3),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar21,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((2,1),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar22,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((2,2),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar23,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((2,3),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar31,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((3,1),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar32,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((3,2),EstadoActual,V1,EstadoSeguinte).

op1((EstadoActual,V),jogar33,(EstadoSeguinte,V1)):-
	((V = o -> V1 = x); V1 = o),
	substitui((3,3),EstadoActual,V1,EstadoSeguinte).

substitui((X,Y), EstadoActual, SimboloActual, EstadoFinal):-
	member((p(X,Y), V), EstadoActual),
	\+ atom(V), 
	V = SimboloActual,
	EstadoFinal = EstadoActual.

cycle(_,(EstadoActual,Winner)):- (victoria_linhas(EstadoActual);
	victoria_colunas(EstadoActual);
	victoria_diagonais(EstadoActual)), 
	prints(EstadoActual),
	format('Vencedor: ~w\n',[Winner]),!.

cycle(_,(EstadoActual,_)):- 
	empate(EstadoActual), 
	prints(EstadoActual),
	write('Empate! lel'),nl,!.

cycle(0,(EstadoActual,V)):-
	
	prints(EstadoActual),
	statistics(real_time,[Ti,_]),
	minimax_decidir((EstadoActual,V),Op),
	statistics(real_time,[Tf,_]), T is Tf-Ti,	

	nodes(Nodes),
	format('\nTime: ~w\n',[T]),
	format('Number of nodes: ~w\n\n',[Nodes]),
	resetNodes,
	op1((EstadoActual,V),Op,EstadoActualSeguinte),
	cycle(1,EstadoActualSeguinte).

cycle(1,(EstadoActual,V)):-
	prints(EstadoActual),
	write('\nX: '),
	read(X),
	write('Y: '),
	read(Y),
	chooseOp(X,Y,Op),
	op1((EstadoActual,V),Op,EstadoActualSeguinte),
	cycle(0,EstadoActualSeguinte).
 
chooseOp(X,Y,Op):-
	(X = 1, Y = 1 -> Op = jogar11;
		X = 1, Y = 2 -> Op = jogar12;
		X = 1, Y = 3 -> Op = jogar13;
		X = 2, Y = 1 -> Op = jogar21;
		X = 2, Y = 2 -> Op = jogar22;
		X = 2, Y = 3 -> Op = jogar23;
		X = 3, Y = 1 -> Op = jogar31;
		X = 3, Y = 2 -> Op = jogar32;
		X = 3, Y = 3 -> Op = jogar33).

% PRINTS 

prints(EstadoActual):-
	printlns(EstadoActual).

printlns(EstadoActual):-
	write('\n '),
	println(EstadoActual, 1, 1),
	write(' '),
	writeln2(1, 3),
	write(' '),
	println(EstadoActual, 2, 1),
	write(' '),
	writeln2(1, 3),
	write(' '),
	println(EstadoActual, 3, 1),
	write('\n').

println(EstadoActual, X, Y):-
	member((p(X,Y), V), EstadoActual),
	Y = 3,
	writeln(V),write('\n').

println(EstadoActual, X, Y):-
	\+member((p(X,Y), V), EstadoActual),
	Y = 3,
	writeln(V).

println(EstadoActual, X, Y):-
	Y < 3, Y2 is Y+1,
	member((p(X,Y), V), EstadoActual),
	writeln3(V),
	println(EstadoActual, X, Y2).

println(EstadoActual, X, Y):-
	Y < 3, Y2 is Y+1,
	\+member((p(X,Y), V), EstadoActual),
	writeln3(V),
	println(EstadoActual, X, Y2).

writeln3(X):-
	atom(X),
	write(X),write(' | ').

writeln3(X):-
	\+ atom(X),
	write(' '),write(' | ').

writeln(X):-
	atom(X),
	write(X).

writeln(X):-
	\+ atom(X),
	write(' ').

writeln2( X, V):-
        X = V, write('- - -\n').

writeln2( X, V):-
        X < V, X2 is X+1,
        write('- '),
        writeln2(X2, V).