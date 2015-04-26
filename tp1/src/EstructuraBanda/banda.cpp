#include "banda.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Constructor de Matriz banda
 *
 * @param {int} dimension
 * @param {int} longitud de banda
 *
 * @return {MatrizB} nueva instancia de MatrizB
 */

MatrizB::MatrizB(int _n, int banda) {
	m = n = _n;
  kl = ku = banda;

	// Seteo el tamano del vector que representa la matriz
	// con tamano banda*2 + 1
  matrix.resize(2*banda+1);

	//inicializo la matriz de manera segura (evitando problemas de manejo de memoria)
	for(int i = 0; i < kl+ku+1; i++) {
    matrix[i].resize(n);
		for(int j= 0; j < n; j++) {
      matrix[i][j] = 0.0;
    }
  }
}

/**
 * matrix getter
 */

std::vector <std::vector< double > > MatrizB::getMatrix() {
	return matrix;
}

/**
 * p getter
 */

int MatrizB::getP() {
	return kl;
}

/**
 * q getter
 */

int MatrizB::getQ() {
	return ku;
}

/**
 * n getter
 */

int MatrizB::getN() {
	return n;
}

/**
 * m getter
 */

int MatrizB::getM() {
	return m;
}



/**
 * Obtener el valor de la matriz en un punto
 *
 * @param {int} x
 * @param {int} y
 *
 * @return {double} m(x, y)
 *
 * x1 	x2 	0  	0 	0
 * x3 	x4 	x5 	0 	0
 * 0 	  x6	x7 	x8 	0
 * 0 	  0 	x9 	x10 x11
 *
 * Para ahorrar los 0s lo transformo en =>
 * x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11
 */

double MatrizB::getVal(int x, int y) {
	if(posicionValida(x,y)) {
    return matrix[ku+x-y][y];
	} else {
    return 0.0;
	}
}

/**
 * Setear valor en un punto
 *
 * @param {int} x
 * @param {int} y
 * @param {double} valor a setear
 */

void MatrizB::setVal(int x, int y, double val) {
	if(posicionValida(x,y)) {
		matrix[ku+x-y][y] = val;
  } else {
		// Si x, y están fuera de rango tira una excepcion
		cout << "Intento de seteo en cordenadas: (" << x << "," << y << ")" << endl;
		throw 0;
	}
}

/**
 * Devuelve true si x e y forman una posicion valida en la matriz
 *
 * @param {int} x
 * @param {int} y
 *
 * @return {boo} true si es valida, false si no
 *
 * x1 	x2 	0 	0 	0 	0
 * 0 	  x5  x6  0 	0 	0
 * 0    0 	x9  x10 0 	0
 */

bool MatrizB::posicionValida(int x, int y) {
  // si alguna coordenada es negativa, es falso
	if(x < 0 || y < 0) return  false;

  // si alguna coordenada es mayor al rango, es falso 
	if(y >= m || x >= n) return false;

  // si alguna coordenada no cumple con las reglas propuestas
  // por el storage banda, es falso
	if(!(max(0, y-ku) <= x && x <= min(m -1, y+kl))) return false;

  // Si no cumple ninguna de las condiciones previas, es verdadero
	return true;
}

/**
 * Imprime la matriz de un modo conveniente
 */

void MatrizB::printM() {
  int l = 0;
  int i, j;
  int n = this->getN();
  int m = this->getM();
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      if(this->getVal(i, j) == 0) {
        cout <<  this->getVal(i, j);
      } else {
        cout <<  this->getVal(i, j);
        l++;
      }
      cout << "\t";
    }
    cout << endl;
  }
}
