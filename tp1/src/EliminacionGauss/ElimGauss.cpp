#include "ElimGauss.h"

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

/**
 * Chequea que 2 doubles difieran en menos que un delta
 *
 * @param {double} a
 * @param {double} b
 * @param {double} delta
 *
 * @return {bool} son iguales
 */

bool son_iguales(double a, double b, double delta = 1.0e-10) {
	return abs(a - b) < delta;
}

/**
 * Resta 2 filas para dejar un 0 en un elemento de la diagonal
 *
 * @param {MatrizB*} m
 * @param {int} fila minuendo
 * @param {int} fila sustraendo
 * @param {double*} b
 * @param {MatrizB*} L
 *
 * @return {bool} son iguales
 */

void restar_filas_diagonal(MatrizB *m, int fila_minuendo, int fila_sustraendo, double *b, MatrizB *L ) {
	int columna = fila_sustraendo;

  if(fila_minuendo >= m->getN())
    return;

  double coeficiente = m->getVal(fila_minuendo, fila_sustraendo) / m->getVal(fila_sustraendo,fila_sustraendo);

  L->setVal(fila_minuendo, columna, (coeficiente) );
  m->setVal(fila_minuendo,columna,0.0);

  columna++;

  if (! son_iguales(coeficiente,0,0) ) {
		b[fila_minuendo] = b[fila_minuendo] - b[fila_sustraendo]*coeficiente;
		while(columna <= m->getP() + fila_sustraendo) {
      if(columna > m->getN() -1) {
          break;
			}
		  m->setVal(fila_minuendo,columna,m->getVal(fila_minuendo,columna)-m->getVal(fila_sustraendo,columna)*coeficiente);
			columna++;
		}
	}
}

/**
 * Algoritmo de eliminacion gaussiana
 *
 * @param {MatrizB*} m
 * @param {double*} b
 */

void gauss(MatrizB *m, double *b) {
	MatrizB *L = new MatrizB(m->getN(), m->getP());

  //voy diagonalizando la matriz
  for(int indice=0;indice<m->getN();indice++) {
  	//si el valor de la diagonal es cero paso a la siguiente columna
    if(! son_iguales(m->getVal(indice, indice), 0)) {
    	for(int fila=indice+1 ; fila < m->getP() + indice + 1; fila++) {
      	restar_filas_diagonal(m, fila,indice, b,L);
			}
    }
  }
}

/**
 * Algoritmo de descomposicion LU
 *
 * @param {MatrizB*} m
 */

MatrizB* DescompLU(MatrizB *m) {
  double *b = new double[m->getN()];
  MatrizB *L = new MatrizB(m->getN(), m->getP());

  //voy diagonalizando la matriz
  for(int indice=0;indice<m->getN();indice++) {
    //si el valor de la diagonal es cero paso a la siguiente columna
    if(! son_iguales(m->getVal(indice, indice), 0)) {
      for(int fila=indice+1 ; fila < m->getP() + indice + 1; fila++) {
        restar_filas_diagonal(m, fila,indice, b,L);
      }
    }
  }
  delete b;
  return L;
}
