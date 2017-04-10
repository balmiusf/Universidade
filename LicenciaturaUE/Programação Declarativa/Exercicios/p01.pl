my_last(X,[X]).
my_last(X,[_|L]):- my_last(X,L).

num(z).
num(s(X)) :- num(X).
mais1(X, s(X)) :- num(X).
soma(z, Y, Y).
soma(s(X), Y, s(Z)) :- soma(X, Y, Z).
subtr(X, Y, Z) :- soma(Z, Y, X).
dobro(X, Y) :- soma(X, X, Y).


mult(z, _, z).
mult(s(X), N, M) :-
   mult(X, N, K),
   soma(N, K, M).


div(A, B, C) :- mult(B, C, A).

le(z,_).
le(s(A),s(B)) :- le(A,B).

% less then 

lt(z,s(_)).
lt(s(A),s(B)) :- lt(A,B).

% more then

mt(s(_),z).
mt(s(A),s(B)) :- mt(A,B).

% factorial

fact(z,s(z)).
fact(s(z),s(z)).
fact(s(X),M):- fact(X,T), mult(s(X),T,M).


% check if is square root
%squareroot(X,Y) :-
%	X >= 0,
%	Y = 0,
%	Y1 = 0,
%	repeat,
%		Y * Y <= N,
%		(Y+1) * (Y+1) > N,!,
%		Y is Y1+1.


compare([],[],_).
compare([X|T1],[Y|T2],[X|H]):- X > Y, compare(T1,T2,H).
compare([X|T1],[Y|T2],[Y|H]):- Y > X, compare(T1,T2,H).

exp(_,0,1).
exp(A,1,A).
exp(A,B,C):- 
	C1 is A*A,
	B1 is B-1,
	exp(A,B1,C1,C).

exp(A,1,C,C):- !.
exp(A,B1,C1,C):-
	C2 is C1*A,
	B2 is B1-1,
	exp(A,B2,C2,C).