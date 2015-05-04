#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>


#ifndef __matrizNum_H_INCLUDED__   
#define __matrizNum_H_INCLUDED__  
#include "../vector/vectorNum.h"
using namespace std;

class vectorNum;

class matrizNum{
private:
	double **valores;
	int dim;
public:
	matrizNum(int dimencion);
	~matrizNum();
	void resta(matrizNum* otraMat);
	double get(int x, int y);
	void set(int x, int y, double val);
	void print();
	int size();
	vectorNum *producto(vectorNum *vector);
};

#endif