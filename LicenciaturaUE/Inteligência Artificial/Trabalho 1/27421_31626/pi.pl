% Predicados dinamicos
:-dynamic(visited_nodes/1).		% numero de nos visitados
:-dynamic(in_memory_nodes/1). 	% numero de nos em memoria

%Descricao do problema:

%estado_inicial(Estado)
%estado_final(Estado)

%representacao dos operadores
%op(Eact,OP,Eseg,Custo)

%representacao dos nos
%no(Estado,no_pai,Operador,Custo,H+C,Profundidade)

pesquisa(Problema,Alg):-
  consult(Problema),
  
  asserta(visited_nodes(0)),
  asserta(in_memory_nodes(0)),
  
  estado_inicial(S0),
  pesquisa(Alg,[no(S0,[],[],0,1,0)],Solucao),
  escreve_seq_solucao(Solucao),
  
  retract(visited_nodes(_)), 			
  retract(in_memory_nodes(_)),
  
  retractall(has_been_visited(_)).

	
pesquisa(a,E,S):- pesquisa_a(E,S).

pesquisa_a([no(E,Pai,Op,C,HC,P)|_],no(E,Pai,Op,C,HC,P)):- 

	retract(visited_nodes(Nodes)),
	MoreNodes is Nodes +1,
	asserta(visited_nodes(MoreNodes)),
	
	estado_final(E).

pesquisa_a([E|R],Sol):- 
	expande(E,Lseg), 
	esc(E), 
	insere_ord(Lseg,R,Resto),
	
	length(Resto,Size),
	retract(in_memory_nodes(Nodes)),
	
	max(Size,Nodes,Result),
	
	asserta(in_memory_nodes(Result)),
	
    pesquisa_a(Resto,Sol).

expande(no(E,Pai,Op,C,HC,P),L):- findall(no(En,
                                                            no(E,Pai,Op,C,HC,P),Opn,Cnn,HCnn,P1),
                                    (op(E,Opn,En,Cn),P1 is P+1, Cnn is Cn+C, h2(En,H), 
                                                                                          HCnn is Cnn+H), L).	


insere_ord([],L,L).
insere_ord([A|L],L1,L2):- 
	insereE_ord(A,L1,L3), 
	insere_ord(L,L3,L2).

insereE_ord(A,[],[A]).
insereE_ord(A,[A1|L],[A,A1|L]):- menor_no(A,A1),!.
insereE_ord(A,[A1|L], [A1|R]):- insereE_ord(A,L,R).

menor_no(no(_,_,_,_,N,_), no(_,_,_,_,N1,_)):- N < N1.

escreve_seq_solucao(no(E,Pai,Op,Custo,_HC,Prof)):- 
		write(custo(Custo)),nl,
		write(profundidade(Prof)),nl,
		escreve_seq_accoes(no(E,Pai,Op,_,_,_)),
		write('Nos visitados: '),
		visited_nodes(X),
		write(X),
		nl,
		write('Maximo de nos em memoria: '),
		in_memory_nodes(Y),
		write(Y).


	
escreve_seq_accoes([]).
escreve_seq_accoes(no(E,Pai,Op,_,_,_)):- 
	escreve_seq_accoes(Pai),
    write(e(Op,E)),nl.

esc(A):- write(A), nl.

% verifica o maximo 

max(X,X,Z):-
	Z = X.
	
max(X,Y,Z):-
	X > Y,
	Z = X.

max(X,Y,Z):-
	Y > X,
	Z = Y.