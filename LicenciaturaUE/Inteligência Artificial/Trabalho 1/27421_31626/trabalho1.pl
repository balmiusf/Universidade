:-dynamic(has_been_visited/1).  % salas que ja foram visitadas


has_been_visited((18,18)). %% esta sala ja foi visitada 

% Matrix 30x30

% ----- estado inicial -

estado_inicial((18,18)).

% ---------------------

% ----- estado final --

estado_final((26,26)).

% ---------------------
    

% --------- bloqueio --------- %

bloqueio((1,1),(1,2)).
bloqueio((1,2),(1,3)).
bloqueio((2,3),(2,2)).
bloqueio((3,4),(4,4)).
bloqueio((4,5),(3,5)).

% ---------------------------- % 

% ---------------------------- OPERACOES ------------------------------------- %
% verifica se esta entre os limites, se estiver, verifica se
% ja passou pela posicao, se sim verifica se nao ha um bloqueio pelo caminho

op((X,Y),sobe,(X,Z),1):- 
	Y<30, 
	Z is Y+1, 
	(not_been_here((X,Z)) -> \+verificar_bloqueio((X,Y),(X,Z))).
                              

op((X,Y),dir,(Z,Y),1):-  
	X<30, 
	Z is X+1, 
	(not_been_here((Z,Y)) -> \+verificar_bloqueio((X,Y),(Z,Y))).
	
op((X,Y),desce,(X,Z),1):- 
	Y>1, Z is Y-1, 
	(not_been_here((X,Z)) -> \+verificar_bloqueio((X,Y),(X,Z))).

op((X,Y),esq,(Z,Y),1):-  
	X>1, 
	Z is X-1, 
	(not_been_here((Z,Y)) -> \+verificar_bloqueio((X,Y),(Z,Y))).
                               
                              
% ---------------------------------------------------------------------------- %

% verifica se a casa ja foi visitada, caso contrario adiciona a base de dados
not_been_here(X):- 
	\+(has_been_visited(X)),
	asserta(has_been_visited(X)).

% verifica a existencia de bloqueios no caminho

verificar_bloqueio((X1,Y1),(X2,Y2)):- 
    bloqueio((X1,Y1),(X2,Y2)).


% HEURISTICA 1 - distancia euclidia

h1((X,Y),Val):- estado_final(PosFinal), euclid((X,Y),PosFinal,Val).

euclid((X,Y),(EndX,EndY),Val):- 
	CurrX is EndX - X,
	changeSignal(CurrX,CurrX2),
	
	CurrY is EndY - Y,
	changeSignal(CurrY,CurrY2),
	
	Val is sqrt(CurrX2*CurrX2 + CurrY2*CurrY2).
	
% % HEURISTICA 2 - distancia de manhattan
	
h2((X,Y),Val):- estado_final(PosFinal), manhattan((X,Y),PosFinal,Val).

manhattan((X,Y),(EndX,EndY),Val):- 
	CurrX is EndX - X,
	changeSignal(CurrX,CurrX2),
	
	CurrY is EndY - Y,
	changeSignal(CurrY,CurrY2),
	
	Val is CurrX2 + CurrY2.

% muda o sinal se for negativo, caso contraria nao altera
changeSignal(N,M):- ((N < 0) -> M is N*(-1); M is N ).	