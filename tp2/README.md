
# TP 2 - Métodos numéricos

## Como compilar

El programa se compila ejecutando el comando 

	$ python metnum.py

## Como ejecutar

El comando para correrlo es: 

	$ ./tp archivoEntrada archivoSalida metodo

Donde 

- archivoEntrada es el k-fold a correr
- archivoSalida es un archivo donde se guardarán los valores principales encontrados por pca
- metodo es un entero entre 0 y 1 donde 
	* 0 es KNN
	* 1 es PCA

El programa ademas devuelve un archivo llamado Resultados.csv donde se mostrará para cada imgagen cual es la prediccion hecha por el algoritmo.