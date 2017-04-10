:-dynamic(winner/1).
:- dynamic(count/1).

estado_inicial((
	   [(p(1,1), b),(p(2,1), b),(p(3,1), b),(p(4,1),b),
		(p(1,2), x),(p(2,2), x),(p(3,2), b),(p(4,2),b),
		(p(1,3), x),(p(2,3), x),(p(3,3), o),(p(4,3),o),
		(p(1,4), o),(p(2,4), x),(p(3,4), o),(p(4,4),o)], o)).

				   			   
%verifys if game ends in lines row or diagonals, or if it draws.						   
terminal((B,_)):-
	draw(B);rows(B);lines(B).

valor((EstadoActual, _), 1, _):-(lines(EstadoActual);rows(EstadoActual)),winner(o),!.
valor((EstadoActual, _), -1, _):-(lines(EstadoActual);rows(EstadoActual)),winner(x),!.
valor((EstadoActual, _), 0, _):- draw(EstadoActual),!.

op1((EstadoActual,O),jogar1, (EstadoSeguinte,P)):-
	(O = x -> P = o; P = x),
	insere(1, P, EstadoActual,EstadoSeguinte).

op1((EstadoActual,O),jogar2, (EstadoSeguinte,P)):-
	(O = x -> P = o; P = x),
	insere(2, P, EstadoActual,EstadoSeguinte).

op1((EstadoActual,O),jogar3, (EstadoSeguinte,P)):-
	(O = x -> P = o; P = x),
	insere(3, P, EstadoActual,EstadoSeguinte).	

op1((EstadoActual,O),jogar4, (EstadoSeguinte,P)):-
	(O = x -> P = o; P = x),
	insere(4, P, EstadoActual,EstadoSeguinte).	

chooseOp(X,Op):-
	   (X = 1 -> Op = jogar1;
		X = 2 -> Op = jogar2;
		X = 3 -> Op = jogar3;
		X = 4 -> Op = jogar4).

insere(Coluna, J, EstadoActual,EstadoSeguinte):-
	member((p(COLUNA,_),b),EstadoActual),
	get_free(Coluna,EstadoActual,Pos),
	insere_aux(Coluna,Pos,J,EstadoActual,EstadoSeguinte).
	
insere_aux(X,Y,J,[H|T],[HS|T]):-
	H = (p(X,Y),b), 		
	HS = (p(X,Y),J),!.

insere_aux(X,Y,J,[H|T],[H|TS]):-
	H=(p(PX,PY),_),
	(PX\=X;PY\=Y),
	insere_aux(X,Y,J,T,TS),!.

get_free(COLUNA,EstadoActual,VALUE):-
	findall(X,(member((p(COLUNA,_),b),EstadoActual),X=b),L),
	length(L,V), VALUE is V, VALUE >0.
	
	
makeWin(winner(P)):- retractall(winner(_)), asserta(winner(P)),!.	


		
%verifys number of x's or o's in a line, diagonal or row. If both below 4, it fails.		
%List of cases:
%End of line 0 houses left, 4x, win.
%End of line,0 houses left; 4o, win.
%in line. house is X. increment x
%in line, house is o, increment o
%in line, house is empty, increment none

verify( [], 4, 0,0):-makeWin(winner(x)),!.
verify( [], 0, 4,0):-makeWin(winner(o)),!.

verify([(p(_,_),x)|T], NumberOfX, NumberOfO,HousesLeft):-
		NumberOfXTemp is NumberOfX + 1,
		HousesLeftTemp is HousesLeft -1,
		verify(T,NumberOfXTemp,NumberOfO,HousesLeftTemp),!.

verify([(p(_,_),o)|T], NumberOfX, NumberOfO,HousesLeft):-
		NumberOfOTemp is NumberOfO + 1,
		HousesLeftTemp is HousesLeft -1,
		verify(T,NumberOfX,NumberOfOTemp,HousesLeftTemp),!.		

verify([(p(_,_),b)|T], NumberOfX, NumberOfO,HousesLeft):-
		HousesLeftTemp is HousesLeft -1,
		verify(T,NumberOfX,NumberOfO,HousesLeftTemp),!.		

lines(B):-
	(findall(X1,(member(X1,B),X1 = (p(1,_),_)),L1)),verify(L1, 0, 0,4);
	(findall(X2,(member(X2,B),X2 = (p(2,_),_)),L2)),verify(L2, 0, 0,4);
	(findall(X3,(member(X3,B),X3 = (p(3,_),_)),L3)),verify(L3, 0, 0,4);
	(findall(X4,(member(X4,B),X4 = (p(4,_),_)),L4)),verify(L4, 0, 0,4).
	
rows(B):-
	(findall(X1,(member(X1,B),X1 = (p(_,1),_)),L1)),verify(L1, 0, 0,4);
	(findall(X2,(member(X2,B),X2 = (p(_,2),_)),L2)),verify(L2, 0, 0,4);
	(findall(X3,(member(X3,B),X3 = (p(_,3),_)),L3)),verify(L3, 0, 0,4);
	(findall(X4,(member(X4,B),X4 = (p(_,4),_)),L4)),verify(L4, 0, 0,4).
	
	
diagonal(B):-
		(findall(X1,(member(X1,B),X1 = (p(X,X),_)),L1)),verify(L1, 0, 0,4).

draw([]).
draw([(p(_,_),C)|T]):-
	(C = x; C = o),
	draw(T).
	
cycle(_,(EstadoActual,Winner)):- (lines(EstadoActual);
	rows(EstadoActual)),
	tprint(EstadoActual),
	format('Vencedor: ~w\n',[Winner]),!.

cycle(_,(EstadoActual,_)):- 
	draw(EstadoActual), 
	tprint(EstadoActual),
	write('Empate! lel'),nl,!.

cycle(0,(EstadoActual,V)):-
	
	tprint(EstadoActual),
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
	write('\n'),
	tprint(EstadoActual),
	write('\nX: '),
	read(X),
	write('\n'),
	chooseOp(X,Op),
	op1((EstadoActual,V),Op,EstadoActualSeguinte),
	cycle(0,EstadoActualSeguinte).
 
tprint([]).
tprint([(p(X,Y),V)|T]) :-
		write(V), write(' | '),
		X=4-> nl, tprint(T); tprint(T).
	
		
		
		