resetNodes:-
	retractall(nodes(_)),
	asserta(nodes(0)),!.

incrementaNos(N):-
	retract(nodes(M)),
	M1 is N+M,
	asserta(nodes(M1)),!.

limitarProfundidade(N):-
	retractall(profundidade(_)),
	asserta(profundidade(N)),!.

main:-
	write('\n 		MENU    	\n'),
	write('1 - Jogar jogo do galo \n\n'),
	write('2 - Jogar quatro em linha \n\n'),
	write('3 - Sair do Programa \n\n'),
	write('Input: '),
	read(Input),
	mainInput(Input).


mainInput(1):-
	[minmax],	
	[galofinal],
	
	resetNodes,  
	limitarProfundidade(20),
	estado_inicial(Ei),
	cycle(1,Ei),
	write('\n\nSair ou voltar a jogar? \n\n Para sair escreva "sair", para volar a jogar escreva "jogar"  \n'),
	read(X),
	input(X).

mainInput(2):-
	[minmax],
	[fourow],
	resetNodes,
	limitarProfundidade(20),
	estado_inicial(Ei),
	cycle(1,Ei),
	write('\n\nSair ou voltar a jogar? \n\n Para sair escreva "sair", para volar a jogar escreva "jogar"  \n'),
	read(X),
	input(X).
	
mainInput(3).

input('sair'):- mainInput(3).
input('jogar'):- main.


