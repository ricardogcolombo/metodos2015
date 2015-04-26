function ret = CheckCondLU(A)

tic
ret = 0;
for i = 1:size(A) % Completar rango para i (help size) 1:size(A)
    if A(i,i)~= 0, % Completar condicion de corte. Si pasa, la funcion retorna false. A[i][j] != 0
        return;
    end
end
ret = 1;
toc
