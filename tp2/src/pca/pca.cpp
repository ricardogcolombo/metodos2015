
#include "pca.h"

/*void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, string &salida, int cantidadDeVecinosMasCercanos)
{
  
}*/

void matrizDeCovarianza(vector<entrada> &etiquetados)
{
  vector<double> media = vector<double>(etiquetados[0].vect->dim, 0);
  media(etiquetados, media);
}

void media(vector<entrada> &v, vector<double> &media)
{
  double aux = 0.0;

  for(int i = 0 ; i < v.size(); i++) {
    aux = 0.0;
    for(int j = 0; j < media.size(); j++) {
      aux += v[i].vect->get(j);
    }
    media[i] = aux / v.size(); 
    cout << "media " << i << " " << media[i] << endl;
  }
}
