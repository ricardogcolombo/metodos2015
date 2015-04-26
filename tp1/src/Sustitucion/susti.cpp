#include "susti.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

using namespace std;

/**
 * Backward substitution
 *
 * @param {MatrizB*} A
 * @param {double*} b
 *
 * @return {double*} respuesta 
 */

double *backward_substitution(MatrizB *A, double *b)
{
   //Chequear que las dimensiones son correctas
   //Chequear que la matriz es diagonal superior

   double *respuesta = new double[A->getN()];

   for(int i = A->getN()-1 ; i >= 0; i--) {
      respuesta[i] = b[i];
      for(int j = i+A->getP(); j > i; j--)
         if(j < A->getN())
            respuesta[i] = respuesta[i] - A->getVal(i,j)*respuesta[j];
      respuesta[i] = respuesta[i]/A->getVal(i,i);
   }
   return respuesta;
}



// function y = backward_substitution(A,b)
//    if size(b,2)~=1 || size(A,1)~=numel(b),
//       error('las dimensiones no concuerdan') ;
//    end ;
   
//    if any( tril(A,-1) ),
//       error('A no es triangular superior') ;
//    end ;
   
//    n = size(A,2) ;
//    y = zeros(n,1) ;
   
//    for i=n:-1:1,
//       y(i) = b(i);
//       for j = ...;
//           y(i) = y(i) - A(i,j)*y(j);
//       end
//       y(i) = y(i)/A(i,i);
//    end
// end
