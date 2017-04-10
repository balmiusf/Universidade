alfabeta_decidir(Ei,terminou):- terminal(Ei).

alfabeta_decidir(Ei,Opf):- 
	findall(Es-Op, op1(Ei,Op,Es),L),
	length(L, S),
	incrementaNos(S),
	resetNodes,
	findall(Vc-Op,(member(E-Op,L), alfabeta_valor(E,Vc)),L1),
	escolhe_max(L1,Opf).

alfabeta_valor(Ei,Val,_,_):- terminal(Ei), !, valor(Ei,Val,_).

% incompleto

alfabeta_valor(Ei,Val,Alfa,Beta):- 
	findall(Es,op1(Ei,_,Es),L),
	length(L, S),
	incrementaNos(S),
	resetNodes.
	% ...

maximo([A|R],Val):- maximo(R,A,Val).

maximo([],A,A).
maximo([A|R],X,Val):- A < X,!, maximo(R,X,Val).
maximo([A|R],_,Val):-  maximo(R,A,Val).


escolhe_max([A|R],Val):- escolhe_max(R,A,Val).
 
escolhe_max([],_-Op,Op). 
escolhe_max([A-_|R],X-Op,Val):- A < X,!, escolhe_max(R,X-Op,Val). 
escolhe_max([A|R],_,Val):-  escolhe_max(R,A,Val). 
 
minimo([A|R],Val):- minimo(R,A,Val). 

minimo([],A,A). 
minimo([A|R],X,Val):- A > X,!, minimo(R,X,Val). 
minimo([A|R],_,Val):-  minimo(R,A,Val).


% incompleto ...