
% blocos
bloco_grande(a).
bloco_grande(d).
bloco_pequeno(c).
bloco_pequeno(b).

estado_inicial([dir([]),esq([]),no_chao(a),no_chao(b),livre(d),livre(c),em_cima(c,b),em_cima(d,a)]).

estado_final([dir([]),esq([]),livre(a),em_cima(a,b),em_cima(a,c), em_cima(b,d),em_cima(c,d),no_chao(d)]). % estado final original
%estado_final([dir([]),esq([]),livre(a), em_cima(b,d),em_cima(c,d),no_chao(d),livre(b),livre(c),no_chao(a)]). % estado final sem o ultimo passo

% tira pequeno de cima de pequeno usando braco direito
accao(tirarPequeno(D),[dir([]),livre(D),em_cima(D,D1)],
	[dir(D),livre(D1)],[dir([]),em_cima(D,D1),livre(D)]):-
	bloco_pequeno(D), bloco_pequeno(D1), member(D,[c,b]),
	member(D1,[c,b]), D1 \= D.

% tira pequeno de cima de pequeno usando braco esquerdo 
accao(tirarPequeno(D),[esq([]),livre(D),em_cima(D,D1)],
	[esq(D),livre(D1)],[esq([]),em_cima(D,D1),livre(D)]):-
	bloco_pequeno(D), bloco_pequeno(D1), member(D,[c,b]),
	member(D1,[c,b]), D1 \= D.

% tirar pequeno do chao usando braco direito 
accao(tirarPequeno(D),[dir([]),livre(D),no_chao(D)],
	[dir(D)],[dir([]),no_chao(D),livre(D)]):-
	bloco_pequeno(D),member(D,[c,b]).

% tirar pequeno do chao usando braco esquerdo
accao(tirarPequeno(D),[esq([]),livre(D),no_chao(D)],
	[esq(D)],[esq([]),no_chao(D),livre(D)]):-
	bloco_pequeno(D), member(D,[c,b]).


% meter dois em cima de grande
accao(porDoisPequenos(D,D1,D2),[esq(D),dir(D1),livre(D2)],
	[livre(D),livre(D1),em_cima(D,D2),em_cima(D1,D2),
	dir([]),esq([])],
	[esq(D),dir(D1),livre(D2)]):- bloco_pequeno(D),bloco_pequeno(D1), bloco_grande(D2),
	member(D1,[c,b]),member(D,[c,b]), member(D2,[a,d]), D \= D1.

% usar dois bracos para tirar um grande em cima de outro
accao(tirarGrande(D),[esq([]),dir([]),livre(D),em_cima(D,D1)],
	[esq(D),dir(D),livre(D1)],[esq([]),dir([]),livre(D),em_cima(D,D1)]):-
	bloco_grande(D), bloco_grande(D1), member(D,[a,d]),member(D1,[a,d]),
	D \= D1.

% por um bloco grande no chao
accao(porGrandeChao(D),[esq(D),dir(D)],
	[esq([]),dir([]),no_chao(D),livre(D)],[esq(D),dir(D)]):- bloco_grande(D),member(D,[d,a]).

% tirar um bloco grande no chao
accao(tirarGrandeChao(D),[esq([]),dir([]),livre(D),no_chao(D)],
	[esq(D),dir(D)],[livre(D),no_chao(D),esq([]),dir([])]):- bloco_grande(D), member(D,[d,a]).

% por um bloco grande em cima de dois pequenos
accao(porGrandeEm2pequenos(D,D1,D2),[livre(D1),livre(D2),esq(D),dir(D)],
	[esq([]),dir([]),em_cima(D,D1),em_cima(D,D2),livre(D)],
	[livre(D1),livre(D2),esq(D),dir(D)]):- bloco_pequeno(D1),bloco_pequeno(D2), bloco_grande(D),
	member(D2,[c,b]),member(D1,[c,b]), member(D,[a,d]), D1 \= D2.

