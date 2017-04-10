
% Predicados dinamicos
:-dynamic(visited_nodes/1).		% numero de nos visitados
:-dynamic(in_memory_nodes/1). 	% numero de nos em memoria

%Descricao do problema:

%estado_inicial(Estado)
%estado_final(Estado)

%representacao dos operadores
%op(Eact,OP,Eseg,Custo)

%representacao dos nos
%no(Estado,no_pai,OperadorCusto,Profundidade)

pesquisa(Problema,Alg):-
  consult(Problema),
  
  asserta(visited_nodes(0)),
  asserta(in_memory_nodes(0)),
  
  estado_inicial(S0),
  pesquisa(Alg,[no(S0,[],[],0,0)],Solucao),
  escreve_seq_solucao(Solucao),
  
  retract(visited_nodes(_)),
  retract(in_memory_nodes(_)),
  
  retractall(has_been_visited(_)).




pesquisa_it(Ln,Sol,P):- pesquisa_pLim(Ln,Sol,P).
pesquisa_it(Ln,Sol,P):- P1 is P+1, retractall(has_been_visited(_)),pesquisa_it(Ln,Sol,P1).
pesquisa(it,Ln,Sol):- pesquisa_it(Ln,Sol,1).
pesquisa(largura,Ln,Sol):- pesquisa_largura(Ln,Sol).
pesquisa(profundidade,Ln,Sol):- 
	pesquisa_profundidade(Ln,Sol).

	
pesquisa_profundidade([no(E, Pai, Op, C, P)|_], no(E, Pai, Op, C, P)):-
	retract(visited_nodes(X)),
	Y is X+1, 
	assertz(visited_nodes(Y)),	
	estado_final(E).

pesquisa_profundidade([E|R], Sol):-
	expande(E, Lseg), 
	esc(E),
	insert_at0(Lseg, R, Resto),
	
	length(Resto,Size),
	retract(in_memory_nodes(Nodes)),
	
	max(Size,Nodes,Max),
	assertz(in_memory_nodes(Max)),
	pesquisa_profundidade(Resto, Sol).	


pesquisa_largura([no(E,Pai,Op,C,P)|_],no(E,Pai,Op,C,P)):- 
	retract(visited_nodes(X)),
	Y is X + 1,
	asserta(visited_nodes(Y)),
	estado_final(E).

pesquisa_largura([E|R],Sol):- 
	expande(E,Lseg), 
	esc(E),
	insert_end(Lseg,R,Resto),
	
	length(Resto,ListSize),
	
	retract(in_memory_nodes(X)),
	max(ListSize,X,Result),
	
	asserta(in_memory_nodes(Result)),
	
	
	pesquisa_largura(Resto,Sol).

expande(no(E,Pai,Op,C,P),L):- 
	findall(no(En,no(E,Pai,Op,C,P),Opn,Cnn,P1),
                                    (op(E,Opn,En,Cn),P1 is P+1, Cnn is Cn+C),
                                    L).


expandePl(no(E,Pai,Op,C,P),[],Pl):- 
	Pl =< P, ! .
expandePl(no(E,Pai,Op,C,P),L,_):- 
	findall(no(En,no(E,Pai,Op,C,P),Opn,Cnn,P1),
                                    (op(E,Opn,En,Cn),P1 is P+1, Cnn is Cn+C),
                                    L).
insert_end([],L,L).
insert_end(L,[],L).
insert_end(R,[A|S],[A|L]):- insert_end(R,S,L).

pesquisa_pLim([no(E,Pai,Op,C,P)|_],no(E,Pai,Op,C,P),_):- 
	visited_nodes(X),
	Y is X+1, 
	retract(visited_nodes(X)), 
	assertz(visited_nodes(Y)),
	estado_final(E).

pesquisa_pLim([E|R],Sol,Pl):- 
	expandePl(E,Lseg,Pl), esc(E),
	insert_end(R,Lseg,Resto),
	length(Resto,X),
	in_memory_nodes(Y),
	max(X,Y,Z),
	retract(in_memory_nodes(Y)),
	assertz(in_memory_nodes(Z)), 							  
	pesquisa_pLim(Resto,Sol,Pl).


escreve_seq_solucao(no(E,Pai,Op,Custo,Prof)):- 
	write(custo(Custo)),nl,
	write(profundidade(Prof)),nl,
	escreve_seq_accoes(no(E,Pai,Op,_,_)),  
	write('Nos visitados: '),
	visited_nodes(X),
	write(X),
	nl,
	write('Maximo de nos em memoria: '),
	in_memory_nodes(Y),
	write(Y).


escreve_seq_accoes([]).
escreve_seq_accoes(no(E,Pai,Op,_,_)):- 
	escreve_seq_accoes(Pai),
    write(e(Op,E)),nl.

esc(A):- write(A), nl.



insert_at0([], L, L).
insert_at0(L, [], L).
insert_at0(R, T, L):- append(R,T,L).

% verifica o maximo 

max(X,X,Z):-
	Z = X.
max(X,Y,Z):-
	X > Y,
	Z = X.

max(X,Y,Z):-
	Y > X,
	Z = Y.