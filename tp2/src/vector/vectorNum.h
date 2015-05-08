#ifndef __vectorNum_H_INCLUDED__   
#define __vectorNum_H_INCLUDED__   

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include "../matriz/matriz.h"
using namespace std;

class matrizNum;

class vectorNum{
private:
	double *valores;
	double valorNorma2;
	int dim;
public:
	vectorNum(int dimencion);
	~vectorNum();

	//calcula la norma
	double norma2();
	//Realiza la resta entre este vector y otro
	vectorNum *resta(vectorNum *otroVector);

	int size();

	double get(int pos);
	void set(int pos, double val);

	void suma(vectorNum *otroVector);
	void print();
	double multiplicacionVect(vectorNum *otroVector);
	void multiplicacionEscalar(double escalar);
	matrizNum* multiplicacionVectTrans(vectorNum *otroVector);
	vectorNum *copy();
	double normaInfinito();
};

#endif
