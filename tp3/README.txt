Para compilar:
g++ main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

para compilar en mac (al menos)
g++ $(pkg-config --cflags --libs opencv) main.cpp bilineal.cpp -o Test  &&  ./Test teo.jpg 2 0

Para ejecutar:
./a.out teo.jpg


Hay que poner cada algoritmo en un archivo separado y que tome como variable el k 
para que se pueda ingresar desde la terminal cuando se ejecuta el metodo. 
