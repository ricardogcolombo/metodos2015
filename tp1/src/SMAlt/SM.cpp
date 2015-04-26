#include "SM.h"

using namespace std;

MatrizB* encontrarMatrizInversa(MatrizB *m);
double* armarVectorU(int i, MatrizB *mat);
double* armarVectorVT(int j, MatrizB *mat);
double calcularConstanteLoca(double* VT, MatrizB* inv, double * U);
vector<sanguijuelaDiscretizada*> *discretizarSangs(vector<sanguijuela*>* sanguijuelas, double intervalo, int cantidadDeColumnas, int cantidadDeFilas);
std::vector <std::vector< double > > calcularMatrizDeShermanMorrison(double *vecU, double* vecVT, MatrizB* inversa);
double *copiarB(double *b, int tam);

double *salvacionSM(instancia *ins, double *b)
{


	sanguijuela* s;
	sanguijuela* a_eliminar = NULL;

	//Queria ponerle el valor mas grande, pero c es caprichoso
	double punto_critico_global = 10000000000;
	double punto_critico_local = 0;
	double *mejorRespuesta;
	int posPuntoCritico = ins->m->getP()/2 + (ins->m->getP())*(ins->m->getP()/2);

	//Asegurado por matlab que devuelve lo mismo
	MatrizB* inversa = encontrarMatrizInversa(ins->m);

	vector<sanguijuelaDiscretizada*> *sangDiscretizadas = discretizarSangs(ins->sanguijuelas, ins->intervalo, ins->m->getP(), ins->m->getP());
	for(int i =0; i < sangDiscretizadas->size() ; i++) 
	{
		double * vecU = armarVectorU((*sangDiscretizadas)[i]->x, ins->m);

cout << "vector u" << endl;
		double * vecVT = armarVectorVT((*sangDiscretizadas)[i]->y, ins->m);

cout << "vector vu" << endl;
		

		//Ahora hago la ecuacion horrible de sherman morrison
		std::vector <std::vector< double > > ShermanMorris = calcularMatrizDeShermanMorrison(vecU, vecVT, inversa);

		//Obtengo una copia de B y modifico solo la fila donde esta la sanguijuela
  		double *nuevoB = copiarB(b, inversa->getN());
  		nuevoB[(*sangDiscretizadas)[i]->x] = 0;
		cout << "antes de primer for"<< endl;

  		//hago x = A^(-1).b y obtengo la nueva respuesta 
  		double *respuesta = new double[inversa->getN()];
  		for(int w= 0; w < inversa->getN(); w++ )

  		{
  			respuesta[w] = 0;
  			for(int j=0; j< inversa->getN(); j++)
  			{
  				respuesta[w] = respuesta[w] + (nuevoB[j]*ShermanMorris[w][j]);
  			}
  		}

  		//Imprimo la respuesta por pantalla para ver que me esta dando

  		/*cout << "Matriz" << endl;
  		for(int i=0;i < inversa->getN();i++)
  		{
	  		for(int j=0;j < inversa->getN();j++)
	  			cout << ShermanMorris[i][j] << "\t";
  			cout << endl;
  		}


  		cout << "instancia:" << endl;
  		for(int i = 0; i < ins->m->getP(); i++)
			for(int w = 0; w < ins->m->getP(); w++)
				cout << i <<"\t" << w << "\t" << respuesta[w + (i * ins->m->getP())] << endl;

*/

		//Si es la mejor respuesta obtenida hasta el momento, la guardo.
		punto_critico_local = respuesta[posPuntoCritico];
		if(punto_critico_local < punto_critico_global) 
		{ 
			mejorRespuesta = respuesta;
			punto_critico_global = punto_critico_local;
			a_eliminar = s;
		}

	}
	return mejorRespuesta;
}


double *copiarB(double *b, int tam)
{
		double *nuevoB = new double[tam];
  		for(int w= 0; w < tam; w++ )
  		{
  			nuevoB[w] = b[w];
  		}
  		return nuevoB;
}

std::vector <std::vector< double > > calcularMatrizDeShermanMorrison(double *vecU, double* vecVT, MatrizB* inversa)
{
		double *AaLaMenosUnoPorU = new double[inversa->getN()];
		for(int j = 0; j < inversa->getN(); j++)
		{
			AaLaMenosUnoPorU[j] = 0;
			for(int w = 0; w < inversa->getN(); w++)
			{
				AaLaMenosUnoPorU[j] = AaLaMenosUnoPorU[j] + vecU[w]*inversa->getVal(j,w);
			}	
		}


		double *VTporAalaMenosUno = new double[inversa->getN()];
		for(int j = 0; j < inversa->getN(); j++)
		{
			VTporAalaMenosUno[j] = 0;
			for(int w = 0; w < inversa->getN(); w++)
			{
				VTporAalaMenosUno[j] += vecVT[w]*inversa->getVal(w,j);
			}
		}

		//Aca calculo la constante loca que va dividiendo
		double constanteLoca = calcularConstanteLoca(vecVT,inversa,vecU);


		//Aca termino de calcular sherman morrison
		std::vector <std::vector< double > > matrix;
		int n = inversa->getN();
  		matrix.resize(n);
  		for(int w = 0; w < n; w++) {
    		matrix[w].resize(n);
			for(int j= 0; j < n; j++) {
      			matrix[w][j] = inversa->getVal(w,j) - (AaLaMenosUnoPorU[w]*VTporAalaMenosUno[j])/constanteLoca;
    			}
  		}
  		return matrix;
}


double calcularConstanteLoca(double* VT, MatrizB* inv, double * U)
{
	double *aux = new double[inv->getN()];

	for(int i = 0; i < inv->getN(); i++)
	{
		aux[i]= 0;
		for(int j = 0; j < inv->getN(); j++)
			aux[i] += VT[j]*inv->getVal(i,j);
	}

	double resupesta = 0;
	for(int i = 0; i < inv->getN(); i++)
	{
		resupesta += aux[i]*U[i];
	}

	return resupesta;
}



sanguijuelaDiscretizada::sanguijuelaDiscretizada(int _x, int _y, double _temp)
{
	x= _x;
	y= _y;
	temp = _temp;
}



MatrizB* encontrarMatrizInversa(MatrizB *m)
{
	MatrizB *U = m;
	MatrizB *L = DescompLU(U);

	//parece que no es matriz bskkasd
	MatrizB *inversa = new MatrizB(m->getN(), m->getN());

	for(int i = 0; i < U->getN(); i++)
	{

		double *vectorCanonico = new double[U->getN()];
		for(int j = 0; j < U->getN(); j++)
			vectorCanonico[j] = 0;
		vectorCanonico[i] = 1;

		double *y = foward_substitution(L,vectorCanonico);
		double *respuesta = backward_substitution(U, y);
		for(int j = 0; j < U->getN(); j++)
		{
			if(respuesta[j] != 0)
				inversa->setVal(j,i,respuesta[j]);
		}
	}
	return inversa;
}



double* armarVectorU(int i, MatrizB *mat) {
	int tam = mat->getN();
	double* vectorU = new double[tam];
	for(int pos = 0; pos < tam; pos++) {
			vectorU[pos] = 0;

		}
cout << "pase for vec u" << endl;
		if(i % tam != 0 && i % tam != tam - 1 ) {
			vectorU[i] = -5;
			vectorU[i+1] = 1;
			vectorU[i-1] = 1;
			vectorU[i - mat->getM()] = 1;
			vectorU[i - mat->getM()] = 1;
		}

cout << "sali vec u" << endl;

	return vectorU;
}

double* armarVectorVT(int j, MatrizB *mat) {
	int tam = mat->getN();
	double* vectorVT = new double[tam];
	for(int pos = 0; pos < tam; pos++) {
			vectorVT[pos] = 0;
		}

	vectorVT[j] = 1;

	return vectorVT;
}

vector<sanguijuelaDiscretizada*> *discretizarSangs(vector<sanguijuela*>* sanguijuelas, double intervalo, int cantidadDeColumnas, int cantidadDeFilas)
{
	vector<sanguijuelaDiscretizada*> *sanguDisc = new vector<sanguijuelaDiscretizada*>(); 

	for(int i = 0; i < sanguijuelas->size(); i++) {

			sanguijuela *s = (*sanguijuelas)[i];

			int x_comienzo = round((s->x -1 * (s->radio + 1))/intervalo);
			int y_comienzo = round((s->y -1 * (s->radio + 1))/intervalo);

			int x_fin = round((s->x + 1 * (s->radio + 1))/intervalo);
			int y_fin = round((s->y + 1 * (s->radio + 1))/intervalo);
			if(s->radio<intervalo){
			for(int j = x_comienzo ; j <= x_fin; j++) {
				for(int w = y_comienzo; w <= y_fin; w++) {
					if(pow(j*intervalo - s->x ,2.0)+ pow(w*intervalo - s->y,2.0) <= pow(s->radio,2.0)) {
						int CoordenadaEnLaMatriz = (w + (j*cantidadDeColumnas));
						if(w > 0 && w < cantidadDeColumnas -1) {
							if(j > 0 && j < cantidadDeFilas -1) {
								if(CoordenadaEnLaMatriz % cantidadDeColumnas != 0 && CoordenadaEnLaMatriz % cantidadDeColumnas != cantidadDeColumnas - 1 ) {	
								  	
									sanguDisc->push_back(new sanguijuelaDiscretizada(CoordenadaEnLaMatriz,CoordenadaEnLaMatriz, (*sanguijuelas)[i]->temperatura));
							  }
							}
						}
					}
					}
				}
			}
		
	  }
	  return sanguDisc;
}
