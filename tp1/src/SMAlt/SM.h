#ifndef __Sherman_H_INCLUDED__   // if x.h hasn't been included yet...
#define __Sherman_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "../EstructuraBanda/banda.h"
#include "../GeneradorDeInstancias/generador.h"
#include "../EliminacionGauss/ElimGauss.h"
#include "../FowardSub/Fowardsub.h"
#include "../Sustitucion/susti.h"

#include <iostream>
#include <stdio.h>
#include <cmath>

double *salvacionSM(instancia *ins, double *b);

class sanguijuelaDiscretizada{
public:
	int x;
	int y;
	double temp;
	sanguijuelaDiscretizada(int x, int y, double temp);
};

#endif
