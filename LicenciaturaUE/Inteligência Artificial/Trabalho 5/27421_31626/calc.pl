:-dynamic(h/2).



% blocos

bloco_grande(a).
bloco_grande(d).
bloco_pequeno(c).
bloco_pequeno(b).

% estado inicial

h(dir([]),S0).
h(esq([]),S0).
h(em_cima(d,a),S0).
h(em_cima(c,b),S0).
h(livre(c),S0).
h(livre(d),S0).
h(no_chao(a),S0).
h(no_chao(b),S0).

% consequencias

pgc(D):- no_chao(D),livre(D),esq([]),dir([]).
ppc(D,D1) :- esq([]),dir([]),no_chao(D1),livre(D),
	em_cima(D,D1),bloco_pequeno(D),bloco_pequeno(D1),
	D \= D1.

pgg(D,D1):- esq([]), dir([]), em_cima(D,D1), livre(D).

tgc(D):- esq(D),dir(D).

tgg(D):- esq(D),dir(D),livre(D1).


% tirar pequeno do chao braço dir
h(dir(D),r(tirarPequeno(D),S)):-
	h(dir([]),S),
	h(no_chao(D),S),
	h(livre(D),S),
	bloco_pequeno(D).


% tirar pequeno do chao usando braço esq
h(esq(D),r(tirarPequeno(D),S)):-
	h(esq([]),S),
	h(no_chao(D),S),
	h(livre(D),S),
	bloco_pequeno(D).

% tirar pequeno de outro pequeno usando braço dir
h(dir(D),r(tirarPequeno(D),S)):-
	h(dir([]),S),
	h(em_cima(D,D1),S),
	h(livre(D),S),
	bloco_pequeno(D),bloco_pequeno(D1),D \= D1.

% tirar pequeno de outro pequeno usando braço esq
h(esq(D),r(tirarPequeno(D),S)):-
	h(esq([]),S),
	h(em_cima(D,D1),S),
	h(livre(D),S),
	bloco_pequeno(D),bloco_pequeno(D1), D1 \= D.


% tirar grande do chao usando os dois braços
h(tgc(D),r(tirarGrandeChao(D),S)):-
	h(esq([]),S),
	h(dir([]),S),
	h(no_chao(D),S),
	h(livre(D),S),
	bloco_grande(D).


% tirar grande cima de outro grande usando os dois braços
h(tgg(D),r(tirarGrande(D),S)):-
	h(esq([]),S),
	h(dir([]),S),
	h(em_cima(D,D1),S),
	h(livre(D),S),
	bloco_grande(D),
	bloco_grande(D1),
	D \= D1.


% por grande no chao usando os dois braços
h(pgc(D),r(porGrandeChao(D),S)):-
	h(esq(D),S),
	h(dir(D),S),
	bloco_grande(D).


% por um pequeno no chao e outro em cima do outro pequeno
% usando os blocos que estao nos braços
h(ppc(D,D1),r(porPequenosChao(D,D1),S)):-
	h(esq(D),S),
	h(dir(D1),S)
	bloco_pequeno(D),
	bloco_pequeno(D1),
	D \= D1.

% por grande em cima de outro grande
h(pgg(D,D1),r(porGrandeEmGrande(D,D1),S)):-
	h(esq(D),S),
	h(dir(D),S),
	h(livre(D1),S),
	bloco_grande(D),
	bloco_grande(D1),
	D \= D1.


% inercia

h(esq(D),r(D1,S)):-
	h(esq(D),S),
	D1 \= tirarPequeno(D).

h(dir(D),r(D1,S)):-
	h(dir(D),S),
	D1 \= tirarPequeno(D).

h(dir(D),esq(D),r(D1,S)):-
	h(esq(D),dir(D),S),
	D1 \= tirarGrandeChao(D),
	D1 \= tirarGrande(D).


h(esq([]), dir([]), r(D1, S)) :-
	h(esq([]), S),
	h(dir([]), S),
	X \= porGrandeEmGrande(D,A),
	X \= porGrandeChao(D).

h(esq(D),dir(D1),r(D2,S)):-
	h(esq(D),S),
	h(dir(D1),S),
	X \= porPequenosChao(D,D1).

% estado final

:-h(bracoEsq([]),S),
	h(bracoDir([]),S),
	h(no_chao(d),S),
	h(no_chao(c),S),
	h(em_cima(a,d),S),
	h(em_cima(b,c),S),
	h(livre(a),S),
	h(livre(b),S).


S =
	r(porPequenosChao(c,b),
	r(tirarPequeno(c),
	r(tirarPequeno(c),
	r(porGrandeEmGrande(a,d),
	r(tirarGrandeChao(a), 
	r(porGrandeChao(d),
	r(tirarGrande(d),S0))))))).

