#include "entrada.h"

vector<entrada> procesarEntrada(string archivo, bool entrenamiento){
	vector<entrada> instancias;

	ifstream file (archivo.c_str());
	string value;
	string delimiter = ",";
	
	//nline numera los instancias	
	int nline = 0;
	

	//Leo el encabezado
	getline(file, value);

	while(getline(file, value)) {
		entrada instancia;
		instancia.vect = new vectorNum(784);
		//pos numera la entrada, 0 = label, [1..784] = valores
		int pos = 0;
		
		size_t i = 0;
		string token;
		while ((i = value.find(delimiter)) != string::npos) {
			token = value.substr(0, pos);
			if(entrenamiento)
				instancia.vect->set(pos, atoi(value.c_str()));
			else
				if(pos == 0) {
					instancia.label = atoi(value.c_str());
				} else {
					instancia.vect->set(pos-1, atoi(value.c_str()));
				}
			value.erase(0, i + delimiter.length());
			pos++;
		}
		//Leo la posicion 784 que no tiene delimitador
		if(entrenamiento)
		{
			instancia.vect->set(pos, atoi(value.c_str()));
			instancia.label = -1;
		}
		else{
			instancia.vect->set(pos-1, atoi(value.c_str()));
		}
		//instancia.vect->print();
		//int hola;
		//cin >> hola;	
		//Guardo el vector
		instancias.push_back(instancia);
		nline++;
	}
	return instancias;
}

void imprimirLinea(vector<entrada> &entradas,int linea)
{
	cout << "Numero:" << entradas[linea].label << endl;
	entradas[linea].vect->print();
}
