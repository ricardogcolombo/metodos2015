function [res] = metodo_de_la_potencia(A,x0,niter)

res=x0;
for i = 1:niter,
    res= A*res/norm(res,1);
end

end