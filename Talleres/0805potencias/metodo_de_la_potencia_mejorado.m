function [res] = metodo_de_la_potencia_mejorado(A,x0,v,niter)
% Implementación especial del método de la potencia para
% la matriz de PageRank. A es la matriz de transición P,
% multiplicada por el coeficiente 'c'.

res = x0;
for i = 1:niter,
    % Computar x^(k)
    aux = A*res;
    w = norm(res,1) - norm(aux,1);
    aux = aux + w*v;
    
    % Computar el residuo L1
    l1norm = norm(aux-res,1);

    % Agrego un criterio de corte
    if l1norm <= 0.001
        break;
    end
    res = aux;
end

end