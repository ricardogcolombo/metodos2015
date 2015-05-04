
#include "pca.h"
#define CANTIDAD_ITERACIONES 10
#define CANTIDAD_AUTOVECTORES 10


void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos)
{

  // calculamos la matriz de covarianza
  cout << "1" << endl;
  matrizNum *covarianza = matrizDeCovarianza(etiquetados);

  //Empiezo a conseguir autovectores

  cout << "2" << endl;

  for(int i = 0; i < CANTIDAD_AUTOVECTORES; i++) {
    cout << "3" << endl;

    vectorNum * autovector = metodoDeLasPotencias(covarianza);
    cout << "4" << endl;

    //falta agregar el lamda
    autovector->print();
    covarianza->resta( autovector->multiplicacionVectTrans(autovector));

    cout << "5" << endl;

    }
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
  vectorNum *vectorInicial = new vectorNum(dimencion);
  for(int i = 0; i < dimencion;i++)
  {
    int random = rand() % 100 + 1;
    vectorInicial->set(i, random);
  }

  // int h;
  // covarianza->print();
  // cin >> h;

  for(int i = 0; i < CANTIDAD_ITERACIONES; i++)
  {
    covarianza->print();
    int p;
    cin >> p;
    vectorNum *nuevoVector = covarianza->producto(vectorInicial);
    int norma = nuevoVector->norma2();
    nuevoVector->multiplicacionEscalar((1/(double)norma));
    delete vectorInicial;
    vectorInicial = nuevoVector;
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