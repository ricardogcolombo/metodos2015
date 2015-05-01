#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#ifndef __vectorNum_H_INCLUDED__   
#define __vectorNum_H_INCLUDED__   

class vectorNum{
private:
	int *valores;
	int dim;
	double valorNorma2;
public:
	vectorNum(int dimencion);
	~vectorNum();

	//calcula la norma
	double norma2();
	//Realiza la resta entre este vector y otro
	vectorNum *resta(vectorNum *otroVector);

	int get(int pos);
	void set(int pos, int val);

	void print();
};

#endif