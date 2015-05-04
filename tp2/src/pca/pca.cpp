
#include "pca.h"
#define CANTIDAD_ITERACIONES 10
#define CANTIDAD_AUTOVECTORES 10


void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos)
{
  // calculamos la matriz de covarianza
  matrizNum *covarianza = matrizDeCovarianza(etiquetados);
  //Empiezo a conseguir autovectores
  for(int i = 0; i < CANTIDAD_AUTOVECTORES; i++) {
    vectorNum * autovector = metodoDeLasPotencias(covarianza);
    //falta agregar el lamda
    autovector->print();
    covarianza->resta( autovector->multiplicacionVectTrans(autovector));
    }
    exit(0);
  }
  
  // TODO COPIAR ETIQUETADOS A ETIQUETADOS2 PARA NO PISAR LOS VALORES DE ETIQUETADOS

  
  // double aux = .0;
  // for(int i = 0; i < etiquetados.size(); i++) {
  //   // le hago un cambio de `coordenadas`
  //   for(int j = 0; j < etiquetados[i].vect->dim; j++) {
  //     aux = .0;
  //     for(int k = 0; k < etiquetados[i].vect->dim; k++) {
  //       aux += etiquetados[i].vect->get(k) * potencias[k][j];
  //     }
  //     etiquetados[i].vect->set(j, (int) round(aux));
  //   }
  // }

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
  for(int j = 0 ; j < 3; j++) {
    for(int k = 0 ; k < 3; k++) {
      vectorNum *resta1 = v[k].vect->resta(medias);
      vectorNum *resta2 = v[j].vect->resta(medias);
      int mult = resta1->multiplicacionVect(resta2);
      mult = mult* (1 / (resta1->size() - 1));
      covarianza->set(k,j, mult);
      delete resta1;
      delete resta2;
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