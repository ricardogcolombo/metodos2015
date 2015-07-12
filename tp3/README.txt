Para compilar y ejecutar:
USAR MAKEFILE
make clean
make
./main
o manual
g++ main.cpp bilineal.cpp splines.cpp ventanas.cpp -o main -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect && ./main teo.jpg 2 0


para compilar en mac (al menos) y ejecutar:
g++ $(pkg-config --cflags --libs opencv) main.cpp bilineal.cpp -o Test  &&  ./Test teo.jpg 2 0

