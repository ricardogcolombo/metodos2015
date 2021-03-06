#include "salvacion.h"
#include <limits>
#include <cstddef>
using namespace std;
/**
 * Busca la mejor sanguijuela a eliminar para no romper el parabrisas
 * y la retorna si existe, sino retorna NULL
 *
 * @param {instancia*} instancia
 *
 * @ return {double*} mejor sanguijuela
 */
double *buscarSalvacion(instancia *ins) {
	sanguijuela* s;
	sanguijuela* a_eliminar = NULL;
	int sanguijuelaParaEliminar = -1;
	instancia *ins_aux = generarInstMatriz(ins->ancho, ins->largo, ins->intervalo, ins->sanguijuelas);
	//Queria ponerle el valor mas grande, pero c es caprichoso
	double punto_critico_global = 10000000000;
	double punto_critico_local = 0;
	double *respuesta;
	double *mejorRespuesta;
	//int posPuntoCritico = (ins->cantidadDeFilas() * ((ins->cantidadDeColumnas() / 2))) + ((ins->cantidadDeFilas() / 2)) + (ins->cantidadDeColumnas() / 2) + 1;
	int posPuntoCritico = (ins->cantidadDeFilas() * ((ins->cantidadDeColumnas() / 2))) + ((ins->cantidadDeFilas() / 2)) + 1;
	for (int i = 0; i < ins->sanguijuelas->size() ; i++) {
		s = ins_aux->sanguijuelas->front();
		if (s->procesar == false) {
			break;
		}
		ins_aux->sanguijuelas->erase(ins_aux->sanguijuelas->begin());
		instancia *ins_aux = generarInstMatriz(ins->ancho, ins->largo, ins->intervalo, ins->sanguijuelas);
		gauss(ins_aux->m, ins_aux->b);
		respuesta = backward_substitution(ins_aux->m, ins_aux->b);
		punto_critico_local = respuesta[posPuntoCritico];
		if (punto_critico_local < punto_critico_global) {
			if (punto_critico_global != 10000000000) {
				delete[] mejorRespuesta;
			}
			mejorRespuesta = respuesta;
			punto_critico_global = punto_critico_local;
			a_eliminar = s;
			sanguijuelaParaEliminar = s->numeroSang;
		}
		ins_aux->sanguijuelas->push_back(s);
	}
	if (sanguijuelaParaEliminar != -1) {
		cout << "Sanguijuela optima para sacar usando el metodo simple: " << sanguijuelaParaEliminar << endl;
		cout << "Temperatura del punto critico: " << punto_critico_global << endl;

		return mejorRespuesta;
	} else {
		return NULL;
	}
}
void sacarSang(instancia *b) {
	std::vector<sanguijuela*> *sang = new vector<sanguijuela*>();
	for (int i = 0; i < b->sanguijuelas->size(); i++) {
		sanguijuela *s = (*b->sanguijuelas)[i];
		int x_comienzo = round((s->x - 1 * (s->radio + 1)) / b->intervalo);
		int y_comienzo = round((s->y - 1 * (s->radio + 1)) / b->intervalo);
		int x_fin = round((s->x + 1 * (s->radio + 1)) / b->intervalo);
		int y_fin = round((s->y + 1 * (s->radio + 1)) / b->intervalo);
		int cont = 0 ;
		for (int j = x_comienzo ; j <= x_fin; j++) {
			for (int w = y_comienzo; w <= y_fin; w++) {
				if (pow(j * b->intervalo - s->x , 2.0) + pow(w * b->intervalo - s->y, 2.0) <= pow(s->radio, 2.0)) {
					cont++;
				}
			}
		}
		if (cont == 1) {
			sang->push_back(s);
		}
	}
	b->sanguijuelas = sang;
}
