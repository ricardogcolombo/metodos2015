#include "susti.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
using namespace std;
double *backward_substitution(MatrizB *A, double *b)
{
   //Chequear que las dimensiones son correctas
   //Chequear que la matriz es diagonal superior
   double *respuesta = new double[A->getN()];
   for(int i = A->getN()-1 ; i >= 0; i--) {
      respuesta[i] = b[i];
  	  for(int j = i + 1; j <= i + A->getP(); j++){
		if(j > A->getN())
         	break;
         respuesta[i] = respuesta[i] - A->getVal(i,j)*respuesta[j];
	  	}
        respuesta[i] = respuesta[i]/A->getVal(i,i);
   }
   return respuesta;
}