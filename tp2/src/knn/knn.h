#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "../manejoEntrada/entrada.h"
#include "../vector/vectorNum.h"
#include <queue>

using namespace std;

void calcularknn(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos);

int encontrarEtiqueta(vector<entrada> &etiquetados, entrada &instancia,int cantidadDeVecinosMasCercanos);

struct resultado
{
	double norma;
 	int clase;
};

