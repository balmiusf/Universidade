

p:- tamanho_linha(Linha), estado_inicial(E0,Linha), back(E0,A), esc(A).

back(e([],A,D),A).
back(E,Sol):- sucessor(E,E1), ve_restricoes(E1),
                          back(E1,Sol).

sucessor(e([v(N,V)|R],E,D),e(R,[v(N,V)|E],D)):- member(V,D).

% com forwarding que implica alterar o dominio.
% assim que o valor é usado, este é removido do dominio

p2:- tamanho_linha(Linha),	estado_inicial(E0,Linha), fowarding(E0,A), esc(A).

fowarding(e([],A,D),A).
fowarding(E,Sol):- sucessor2(E,E1), ve_restricoes(E1),
                          fowarding(E1,Sol).

sucessor2(e([v(n(CoordX,CoordY),V)|R],E,D),e(R,[v(n(CoordX,CoordY),V)|E],NewDom)):- member(V,D), subtract(D,[V],NewDom).




