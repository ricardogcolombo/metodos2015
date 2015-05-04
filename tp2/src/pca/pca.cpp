
#include "pca.h"
#define CANTIDAD_ITERACIONES 10
#define CANTIDAD_AUTOVECTORES 10


void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos)
{
  // calculamos la matriz de covarianza
  matrizNum *covarianza = matrizDeCovarianza(etiquetados);
  
  std::vector<vectorNum*> autovectores;

  //Empiezo a conseguir autovectores
  for(int i = 0; i < CANTIDAD_AUTOVECTORES; i++) {
    vectorNum * autovector = metodoDeLasPotencias(covarianza);
    //guardo los actovectores en un vector
    autovectores.push_back(autovector);
    //falta mutliplicar el lamda
    covarianza->resta( autovector->multiplicacionVectTrans(autovector));
    }
    trasponerEntrada(etiquetados,autovectores);
    trasponerEntrada(sinEtiquetar,autovectores);
  }
  
void trasponerEntrada(vector<entrada> etiquetados, std::vector<vectorNum*> autovectores)
{
    for(int j = 0; j < etiquetados.size(); j++)
    {
      vectorNum* vectorAux = new vectorNum(CANTIDAD_AUTOVECTORES);
      for(int i= 0; i < autovectores.size();i++)
      {
        vectorAux->set(i, autovectores[i]->multiplicacionVect(etiquetados[j].vect));
      }
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
    int norma = nuevoVector->norma2();
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
  for(int i = 0; i < v.size(); i++){
    vectorNum* nuevoVector = new vectorNum(v.size());
    for(int j = 0; j < v.size(); j++){
      nuevoVector->set(j, v[j].vect->get(i) - medias->get(i));
    X.push_back(nuevoVector);
    }
  }
  //ahora Armamos la matriz Mx
  for(int i = 0 ; i < dimencion; i++) {
    for(int k = 0 ; k < dimencion; k++) {
      covarianza->set(i,k,X[i]->multiplicacionVect(X[k])/(double)(dimencion - 1 ));
    }
  }
  return covarianza;
}


matrizNum *matrizDeCovarianza(vector<entrada> &etiquetados)
{
  vectorNum *medias = calcularMedias(etiquetados);
  matrizNum *matrizCovarianza = matCovarianza(etiquetados, medias);
  return matrizCovarianza;
}

vectorNum *calcularMedias(vector<entrada> &v)
{
  vectorNum *medias = new vectorNum(v[0].vect->size());
  double aux = 0.0;
  for(int i = 0 ; i < v.size(); i++) {
    aux = 0.0;
    for(int j = 0; j < medias->size(); j++) {
      aux += v[i].vect->get(j);
    }
    medias->set(i, aux / v.size()); 
  }
  return medias;
}