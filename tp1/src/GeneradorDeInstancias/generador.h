#ifndef __Generador_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Generador_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "../EstructuraBanda/banda.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <fstream>

class sanguijuela {
  private:
  public:
	  double x,y,radio,temperatura;
	  int numeroSang;
	  bool procesar;
	  sanguijuela(double x, double y, double radio, double temperatura, int numero);
	  ~sanguijuela(){};
};


class instancia {
  public:
	  MatrizB *m;
	  double *b;	
	  double ancho, largo, intervalo;
	  std::vector<sanguijuela*> *sanguijuelas;
	  ~instancia();
	  int cantidadDeColumnas();
	  int cantidadDeFilas();
};

instancia* generarInst(std::ifstream &archivoDeEntrada);
instancia *generarInstMatriz(double ancho, double largo, double intervalo, std::vector<sanguijuela*> *sanguijuelas);

#endif
