% leo el archivo con las urls
txt = textread('weblistmath.in', '%s', 'delimiter', '');

% leo el grafo generado con webparser.py
s = readGraphFile('graph.out');
% s = readGraphFile('graph.8297.out');
% s = readGraphFile('graph.281903.out');

% coeficiente de teletransportación
c = 0.85;

%% defino las matrices
s.vals = ones(s.m,1)./s.out(s.origin);
d = double(s.out == 0);
v = ones(s.n,1)/s.n;
P = sparse(s.origin,s.dest,s.vals,s.n,s.n);

%% sigo definiendo matrices
D = d*v';
P1= P + D;
E = v*ones(1,s.n);

P2= c*P1 + (1-c)*E;

%% método de la potencia básico
tic;
niter = 100;
eigpm1 = metodo_de_la_potencia(P2',v,niter);
toc

%%
% concateno con la url y muestro el resultado
A = horzcat(arrayfun(@num2str, eigpm1, 'Uniform', false), txt);
[Y,I] = sort(eigpm1,'descend');
A(I,:)

%% método de la potencia acelerado para PageRank
% no es necesario definir la matriz P2 explicitamente
tic;
niter = 100;
eigpm2 = metodo_de_la_potencia_mejorado(c*P',v,v,niter);
toc

    %%
A = horzcat(arrayfun(@num2str, eigpm2, 'Uniform', false), txt);
[Y,I] = sort(eigpm2,'descend');
A(I,:)

%% Error máximo
sprintf('Diferencia máxima: %f',max(abs(eigpm1-eigpm2)))