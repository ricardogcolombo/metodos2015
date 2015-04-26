function ret = CheckCondChol(A)

tic
ret = 0;
for i = 1:size(A) % Completar rango para i (help size)//// 1:size(A) 
    if A(i,i)>0, % Completar condicion de corte. Retorna false (0).  Primer elemento distinto de cero??
        return;
    end
end
ret = 1;
toc
