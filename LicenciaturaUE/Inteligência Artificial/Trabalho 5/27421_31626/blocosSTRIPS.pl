
% blocos
bloco_grande(a).
bloco_grande(d).
bloco_pequeno(c).
bloco_pequeno(b).

%estado_inicial([dir([]),esq([]),no_chao(a),no_chao(b),livre(d),livre(c),em_cima(c,b),em_cima(d,a)]).

estado_inicial([dir([]),esq([]),livre(d), em_cima(d,a),em_cima(c,b),no_chao(b),livre(c),no_chao(a)]). % estado final sem o ultimo passo
estado_final([dir([]),esq([]),no_chao(d),no_chao(c),em_cima(a,d),em_cima(b,c), livre(b),livre(a)]). % estado final original

% tira pequeno de cima de pequeno usando braco direito
accao(tirarPequeno(D),[dir([]),livre(D),em_cima(D,D1)],
	[dir(D),livre(D1)],[dir([]),em_cima(D,D1),livre(D)]):-
	bloco_pequeno(D), bloco_pequeno(D1), member(D,[c,b]),
	member(D1,[c,b]), D1 \= D.

% tirar pequeno do chao usando braco esquerdo
accao(tirarPequeno(D),[esq([]),livre(D),no_chao(D)],
	[esq(D)],[esq([]),no_chao(D),livre(D)]):-
	bloco_pequeno(D), member(D,[c,b]).

% usar dois bracos para tirar um grande em cima de outro
accao(tirarGrande(D),[esq([]),dir([]),livre(D),em_cima(D,D1)],
	[esq(D),dir(D),livre(D1)],[esq([]),dir([]),livre(D),em_cima(D,D1)]):-
	bloco_grande(D), bloco_grande(D1), member(D,[a,d]),member(D1,[a,d]),
	D \= D1.

% por um bloco grande no no_chao
accao(porGrandeChao(D),[esq(D),dir(D)],
	[esq([]),dir([]),no_chao(D),livre(D)],[esq(D),dir(D)]):- bloco_grande(D),member(D,[d,a]).

% tirar um bloco grande no chao
accao(tirarGrandeChao(D),[esq([]),dir([]),livre(D),no_chao(D)],
	[esq(D),dir(D)],[livre(D),no_chao(D),esq([]),dir([])]):- bloco_grande(D), member(D,[d,a]).

% metes os dois pequenos no chao
accao(porPequenosChao(D,D1),
	[esq(D),dir(D1)],
	[esq([]),dir([]),livre(D1),em_cima(D1,D),no_chao(D)],[esq(D),dir(D1)]):-
	bloco_pequeno(D1), D1 = b, bloco_pequeno(D), D = c.

accao(porGrandeEmGrande(D,D1),[esq(D),dir(D),livre(D1)],[em_cima(D,D1),esq([]),dir([]),livre(D)],[livre(D1),esq(D),dir(D)]):- 
bloco_grande(D),D = a, bloco_grande(D1) , D1 = d.

% tira pequeno de cima de pequeno usando braco esquerdo 
accao(tirarPequeno(D),[esq([]),livre(D),em_cima(D,D1)],
	[esq(D),livre(D1)],[esq([]),em_cima(D,D1),livre(D)]):-
	bloco_pequeno(D), bloco_pequeno(D1), member(D,[c,b]),
	member(D1,[c,b]), D1 \= D.

% tirar pequeno do chao usando braco direito 
accao(tirarPequeno(D),[dir([]),livre(D),no_chao(D)],
	[dir(D)],[dir([]),no_chao(D),livre(D)]):-
	bloco_pequeno(D),member(D,[c,b]).
