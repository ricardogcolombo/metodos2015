#ifndef __Banda_H_INCLUDED__   //   #define this so the compiler knows it has been included
#define __Banda_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include <vector>

class MatrizB {
private:
	int ku;
	int kl;
	int m;
	int n;
	double** matrix;
	bool posicionValida(int x, int y);

public:
	MatrizB(int a, int b);
	~MatrizB();
	int getQ();
	int getP();
	int getM();
	int getN();
	double** getMatrix();
	void setVal(int x, int y, double val);
	double getVal(int x, int y);
	void printM();
};

#endif
