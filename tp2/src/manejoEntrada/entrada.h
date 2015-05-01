#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include "../vector/vectorNum.h"


using namespace std;

#ifndef __entrada_H_INCLUDED__   
#define __entrada_H_INCLUDED__   

struct entrada {
	int label;
	vectorNum *vect;
};

#endif

void imprimirLinea(vector<entrada> &entradas,int linea);
vector<entrada> procesarEntrada(string archivo, bool entrenamiento);