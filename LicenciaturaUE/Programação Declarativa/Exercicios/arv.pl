%-*-Prolog-*-
abp(X) :- var(X),!. %Define que abp é uma variavel
abp(n(L,_,R)) :- apb(L),abp(R).% Arvore binaria composta por um nó.

% ins(A,V) -> det (non backtracking)
% inserção na arvore A de um valor V

ins(X,V) :- var(X),!,X =n(_,V,_).

ins(n(L,X,_R), V) :-
    V<X,!,ins(L, V).% inserir no caso de ser menor que X

ins(n(_L,X,R),V) :-
    V>X,!,ins(R, V). %inserir no caso de ser maior que X 

%look(A,V) -> det (non backtracking)
% lookup de V na arvore A

look(A,V) :- var(A),!, A =n(_,A,_).

look(n(L,X,_R), V) :-
    V<X,!, look(L,V).

look(n(_L,X,R),V) :-
    V>X,!, look(R,V).

look(n(_,X,_), X):-!. % no caso de ser igual

%ver todos os casos possiveis
all(A,V) :- var(A),!,fail.

all(n(_,X,_), X). % no caso de ser igual

all(n(L,X,_R), V) :-
     all(L,V),V<X.

all(n(_L,X,R),V) :-
    all(R,V),V>X.

% descobrir o pai do no

father(n(_,F,n(_,C,_)),C,F).
father(n(n(_,C,_),F,_),C,F).
father(n(L,V,R),C,F) :- V > C,!, father(L,C,F).
father(n(L,V,R),C,F) :- V < C,!, father(R,C,F).

% count leaves

% no idea why this works
%count_leaves(n(L,V,R),1):- var(L), var(R).	 
count_leaves(n(L,V,R),1):- var(L).	  
count_leaves(n(L,V,R),1):- var(R).	
count_leaves(n(L,V,R),N) :- 
			count_leaves(L,CL), 
			count_leaves(R,CR), 
			N is CL + CR. 

% sub tree numa list
% S - start
% L - list
subtreelist(n(L,V,R),S,L) :- V > S,!, subtreelist(L,S,L).
subtreelist(n(L,V,R),S,L) :- V < S,!, subtreelist(R,S,L).




% subtree check

subtree(A,A).
subtree(A,n(L,V,R)) :- subtree(A,L).
subtree(A,n(L,V,R)) :- subtree(A,R).

% preorder
preorder(A,[]):- var(A).
preorder(n(L,V,R),LIST):- 		
						preorder(L,LS),
						preorder(R,RS),
						append([V|LS],RS,LIST).

inorder(A,[]) :- var(A).						
inorder(n(L,V,R),LIST):-
			inorder(L,LS),
			inorder(R,RS),
			append(LS,[V|RS],LIST).
			
postorder(A,[]) :- var(A).			
postorder(n(L,V,R),LIST):-
			postorder(L,LS),
			postorder(R,RS),
			append(LS,RS,TEMP),
			append(TEMP,[V],LIST).
			

