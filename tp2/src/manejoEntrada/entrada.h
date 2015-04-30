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

struct entrada {
	int label;
	vectorNum *vect;
};

void imprimirLinea(vector<entrada> &entradas,int linea);
vector<entrada> procesarEntrada(string archivo);