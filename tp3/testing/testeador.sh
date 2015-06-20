rm *.txt
g++ corrector.cpp -o corrector -O2 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
for i in `seq 1 $2`; do
	echo $i
    ./../src/tp k$1/$i.res.png 1 $1 2>> tiempos1.txt 
    ./corrector k$1/$i.png res.jpg >> metodo1.txt

    ./../src/tp k$1/$i.res.png 2 $1 2>> tiempos2.txt 
    ./corrector k$1/$i.png res.jpg >> metodo2.txt

    ./../src/tp k$1/$i.res.png 3 $1 2>> tiempos3.txt 
    ./corrector k$1/$i.png res.jpg >> metodo3.txt
done
