
#include "pca.h"
#define CANTIDAD_ITERACIONES 100


void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadAutovectores)
{
  // calculamos la matriz de covarianza
  matrizNum *covarianza = matrizDeCovarianza(etiquetados);
  
  std::vector<vectorNum*> autovectores;

  //Empiezo a conseguir autovectores
  for(int i = 0; i < cantidadAutovectores; i++) {
    vectorNum * autovector = metodoDeLasPotencias(covarianza);
    //guardo los actovectores en un vector
    autovectores.push_back(autovector);
    double lamda = encontrarAutovalor(autovector,covarianza);
    vectorNum *autovectorAux = autovector->copy();
    autovector->multiplicacionEscalar(lamda);
    covarianza->resta(autovector->multiplicacionVectTrans(autovectorAux));
    }
    trasponerEntrada(etiquetados,autovectores,cantidadAutovectores);
    trasponerEntrada(sinEtiquetar,autovectores,cantidadAutovectores);
  }
  
void trasponerEntrada(vector<entrada> &etiquetados, std::vector<vectorNum*> &autovectores, int cantidadAutovectores)
{
    for(int j = 0; j < etiquetados.size(); j++)
    {
      vectorNum* vectorAux = new vectorNum(cantidadAutovectores);
      for(int i= 0; i < autovectores.size();i++)
      {
        vectorAux->set(i, autovectores[i]->multiplicacionVect(etiquetados[j].vect));
      }
      //Borro el vector viejo y le pongo el de las nuevas dimenciones
      delete etiquetados[j].vect;
      etiquetados[j].vect = vectorAux;
    }
}

//devuelve el mayor autovalor
vectorNum *metodoDeLasPotencias(matrizNum *covarianza)
{
  int dimencion = covarianza->size();
  vectorNum *vectorInicial = crearVectorInicial(dimencion);

  for(int i = 0; i < CANTIDAD_ITERACIONES; i++)
  {
    vectorNum *nuevoVector = covarianza->producto(vectorInicial);
    double norma = nuevoVector->norma2();
    nuevoVector->multiplicacionEscalar((1/(double)norma));
    delete vectorInicial;
    vectorInicial = nuevoVector;
  }
  return vectorInicial;
}


vectorNum *crearVectorInicial(int dim)
{
  vectorNum *vectorInicial = new vectorNum(dim);
  for(int w = 0; w < dim;w++)
  {
    int random = rand() % 100 + 1;
    vectorInicial->set(w,(double)random);
  }
  return vectorInicial;
}

matrizNum *matCovarianza(vector<entrada> &v, vectorNum *medias)
{
  int dimencion = medias->size();
  matrizNum *covarianza = new matrizNum(dimencion);

  //Aca nos creamos el X del slide
  vector<vectorNum*> X;
  for(int i = 0; i < dimencion; i++){
    vectorNum* nuevoVector = new vectorNum(v.size());
    for(int j = 0; j < v.size(); j++){
      nuevoVector->set(j, (double) v[j].vect->get(i) - medias->get(i));
    }
    //nuevoVector->print();
    X.push_back(nuevoVector);
  }
  //ahora Armamos la matriz Mx
  for(int i = 0 ; i < dimencion; i++) {
    for(int k = 0 ; k < dimencion; k++) {
      covarianza->set(i,k,X[i]->multiplicacionVect(X[k])/(double)(v.size() - 1 ));
    }
  }
  return covarianza;
}


matrizNum *matrizDeCovarianza(vector<entrada> &etiquetados)
{
  vectorNum *medias = calcularMedias(etiquetados);
  matrizNum *matrizCovarianza = matCovarianza(etiquetados, medias);
  delete medias;
  return matrizCovarianza;
}

vectorNum *calcularMedias(vector<entrada> &v)
{
  vectorNum *medias = new vectorNum(v[0].vect->size());
  for(int j = 0; j < v[0].vect->size(); j++){
	  double media = 0.0;
	  for(int i = 0; i < v.size(); i++){
		media += v[i].vect->get(j);
	  }
	  medias->set(j, (double)media / (double)v.size());
  }
  return medias;
}

double encontrarAutovalor(vectorNum *autovector, matrizNum *covarianza)
{
  vectorNum * aux = covarianza->producto(autovector);
  for(int i = 0; i < autovector->size(); i++)
  {
    if(aux->get(i) != 0){

        double lamda = aux->get(i)/autovector->get(i);
        return lamda;
    }
  }
  //si llegue acá es que el autovector es 0 lo que es absurdo.
  throw -1;
}
