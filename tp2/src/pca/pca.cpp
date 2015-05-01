
#include "pca.h"

vector<double> calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos)
{
  vector< vector<double> > covarianza = vector< vector<double> >(etiquetados[0].vect->dim, vector<double>(etiquetados[0].vect->dim, 0));
  vector<double> lambdas = vector<double>(etiquetados[0].vect->dim, 0);
  vector<double> potencias = vector<double>(etiquetados[0].vect->dim, 1);

  // calculamos la matriz de covarianza
  matrizDeCovarianza(etiquetados, covarianza);

  for(int i = 0; i < covarianza.size(); i++) {

    lambdas[i] = metodoDeLasPotencias(covarianza, potencias);

    for(int j = 0; j < covarianza.size(); j++) {
      for(int k = 0; k < covarianza.size(); k++) {
        covarianza[j][k] -= lambdas[i]*potencias[j]*potencias[k];
      }
    }
  }

  return lambdas;
}

double metodoDeLasPotencias(vector< vector<double> > &covarianza, vector<double> &potencias)
{
  vector<double> aux = vector<double>(potencias.size(), 0);
  double norma = 0;
  
  // iteraciones del metodo de potencias
  for(int i = 0; i < 10; i++) {
    norma = 0;  

    for(int j = 0; j < covarianza.size(); j++) {
      aux[j] = 0;
      for(int k = 0; k < covarianza[j].size(); k++) {
        aux[j] += covarianza[j][k] * potencias[k];
      }
      norma += aux[j] * aux[j];
    }
    
    norma = sqrt(norma);
    
    for(int k = 0; k < potencias.size(); k++) {
      potencias[k] = aux[k] / norma;
    }
  }

  // ya tenemos xk
  double lambda = .0;
  for(int i = 0; i < covarianza[0].size(); i++) {
    lambda += covarianza[0][i] * potencias[i];
  }
  
  // lambda TODO chequear que potencias[0] != 0
  return lambda / potencias[0];
}

void matrizDeCovarianza(vector<entrada> &etiquetados, vector< vector<double> > &covarianza)
{
  vector<double> media = vector<double>(etiquetados[0].vect->dim, 0);
  matMedia(etiquetados, media);
  matCovarianza(etiquetados, media, covarianza);
}

void matMedia(vector<entrada> &v, vector<double> &media)
{
  double aux = 0.0;

  for(int i = 0 ; i < v.size(); i++) {
    aux = 0.0;
    for(int j = 0; j < media.size(); j++) {
      aux += v[i].vect->get(j);
    }
    media[i] = aux / v.size(); 
  }
}


void matCovarianza(vector<entrada> &v, vector<double> &media, vector< vector<double> > &covar)
{
  for(int j = 0 ; j < v[0].vect->dim; j++) {
    for(int k = 0 ; k < v[0].vect->dim; k++) {
      double aux = .0;
      for(int i = 0 ; i < v.size(); i++) {
        aux += (v[i].vect->get(j) - media[j])*(v[i].vect->get(k) - media[k]);
      }
      covar[j][k] = aux / (v.size() - 1);
    }
  }
}
