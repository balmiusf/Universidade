

p:- estado_inicial(E0), back(E0,A), esc(A).

back(e([],A),A).
back(E,Sol):- sucessor(E,E1), ve_restricoes(E1),
                          back(E1,Sol).

sucessor(e([v(N,D,V)|R],E),e(R,[v(N,D,V)|E])):- member(V,D).


% com forwarding que implica alterar o dominio.
% assim que o valor é usado, este é removido do dominio

p2:- tamanho_linha(Linha),	estado_inicial(E0), fowarding(E0,A), esc(A).

fowarding(e([],A),A).
fowarding(E,Sol):- sucessor2(E,E1), ve_restricoes(E1),
                          fowarding(E1,Sol).

sucessor2(e([v(N,D,V)|R],E),e(NovoR,[v(N,D,V)|E])):-
 member(V,D), forward_checking(N,V,R,NovoR).



