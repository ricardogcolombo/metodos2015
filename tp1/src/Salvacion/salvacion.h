#ifndef __Salvacion_H_INCLUDED__
#define __Salvacion_H_INCLUDED__

#include "../Sustitucion/susti.h"
#include "../EliminacionGauss/ElimGauss.h"
#include "../GeneradorDeInstancias/generador.h"

double *buscarSalvacion(instancia *ins);
void sacarSang(instancia *b);
#endif
