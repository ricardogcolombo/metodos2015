#include "knn.h"

void calcularknn(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos)
{
	int *etiqueta = new int[sinEtiquetar.size()];
	for(int i = 0; i < sinEtiquetar.size(); i++)
	{
		etiqueta[i] = encontrarEtiqueta(etiquetados, sinEtiquetar[i], cantidadDeVecinosMasCercanos);
		cout << etiqueta[i] << endl;
	}
}

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (resultado lhs,resultado rhs) const
  {
  	//comprobar que es asi y no con el signo al reves
    return lhs.norma > rhs.norma;
  }
};


int encontrarEtiqueta(vector<entrada> &etiquetados, entrada &instancia,int cantidadDeVecinosMasCercanos){

	priority_queue<resultado, vector<resultado>,mycomparison> resultados;

	for(int i= 0; i < etiquetados.size(); i++)
	{
		vectorNum* restaVectores = etiquetados[i].vect->resta(instancia.vect);
		resultado result;
		result.norma  = restaVectores->norma2();
		result.clase = etiquetados[i].label;
		resultados.push(result);
	}

	int *numeros = new int[10];

	for(int i = 0; i < cantidadDeVecinosMasCercanos; i++)
	{
		resultado result = resultados.top();
		numeros[result.clase]++;
		resultados.pop();
	}

	int max = 0;
	int claseMax = -1;
	for(int i = 0; i < 10; i++)
	{
		if(max < numeros[i])
		{
			max = numeros[i];
			claseMax = i;
		}
	}
	return claseMax;
}

