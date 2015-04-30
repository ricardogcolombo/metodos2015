#include "knn.h"

void calcularknn(vector<entrada> &etiquetados, vector<entrada> sinEtiquetar, string salida, int cantidadDeVecinosMasCercanos)
{
	for(int i = 0; i < sinEtiquetar.size(); i++)
	{
		int etiqueta = encontrarEtiqueta(etiquetados, sinEtiquetar[i], cantidadDeVecinosMasCercanos);
	}
}


bool comp(const resultado& s1, const resultado& s2)
{
   return s1.norma < s2.norma;
}



int encontrarEtiqueta(vector<entrada> &etiquetados, entrada &instancia,int cantidadDeVecinosMasCercanos){

	std::vector<resultado> resultados;
	for(int i= 0; i < etiquetados.size(); i++)
	{
		vectorNum* restaVectores = etiquetados[i].vect->resta(instancia.vect);
		resultado result;
		result.norma  = restaVectores->norma2();
		result.clase = etiquetados[i].label;
		resultados.push_back(result);
	}

	//No se que mierda le pasa acá

	make_heap(resultados.begin(), resultados.end(), comp);
	
	int *numeros = new int[10];

	for(int i = 0; i < cantidadDeVecinosMasCercanos; i++)
	{
		resultado result = resultados.front();
		numeros[result.clase]++;
		pop_heap(resultados.begin(),resultados.end()); resultados.pop_back();
	}

	int max = 0;
	int claseMax = -1;
	for(int i = 0; i < 0; i++)
	{
		if(max < numeros[i])
		{
			max = numeros[i];
			claseMax = i;
		}
	}

	return claseMax;
}

