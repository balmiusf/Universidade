%1. map(PRED, IN, OUT)
mais1(X, Y):- Y is X+1.
map(_, [],[]).

map(PRED, [A|As], [B|Bs]):-
    X =.. [PRED, A, B],
    X,
    map(PRED, As, Bs).

%3
:-dynamic(calc/0).
process(A):- format("-> ~w~n", [A]).

process(A):-
    integer(A),
    asserta(i(A)).

process(add):-
    retract(i(A)),
    retract(i(B)),
    !,
    C is A+B,
    asserta(i(C)),
    !.

process(sub):-
    retract(i(A)),
    retract(i(B)),
    !,
    C is A-B,
    asserta(i(C)),
    !.
	
process(mult) :-
	retract(i(A)),
	retract(i(B)),
	!,
	C is A*B,
	asserta(i(C)),
	!.

process(div) :-
	retract(i(A)),
	retract(i(B)),
	!,
	C is A/B,
	asserta(i(C)),
	!.

process(dump):-
	retract(i(A)),
	format("-> ~w~n", [A]),
	assertz(i(A)).
	
process(print) :-
	retract(i(A)),!,
	format("-> ~w~n", [A]),
	asserta(i(A)),!.

% esvazia a pilha 	
process(clear) :-
	retractall(i(A)).

calc:-
    repeat, read(A), process(A), fail.
	

	
% 5

p(a, 1). 
p(a, 2). 
p(b, 3). 
p(c, 4). 
p(c, 5). 

todos(A,_) :- var(A),!.
todos(EXPRESSAO, LISTA) :- 
		functor(EXPRESSAO,PRED,_),
		arg(1,EXPRESSAO,ARG),
		X =.. [PRED,ARG,Y],
		findall(Y,X,LISTA).